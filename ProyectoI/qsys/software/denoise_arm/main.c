/*
*******************************************************************

				Instituto Tecnológico de Costa Rica
					Ingeniería en Computadores

		Programador: Esteban Agüero Pérez (estape11)
		Lenguaje: C
		Versión: 1.0
		Última Modificación: 26/03/2019

				Arquitectura de Computadores II
				Prof. Jeferson González Gómez

*******************************************************************
*/

#include "denoise.h"
#include <time.h>
#include <sys/mman.h>
#include <sys/types.h>

#define SDRAM_BASE 0xC4100000
#define LW_BASE 0xFF200000
#define LW_SPAN 0x00200000
#define SDRAM_SPAN 0x04000000
#define LW_MASK (LW_SPAN-1)
#define LED_BASE 0x10000
#define MEM_OFFSET 5

int main ( int argc, char *argv[] ){
	printf("> Started from ARM\n");

	int fd; // file descriptor for the memory
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	void* lwBase=mmap(NULL,LW_SPAN,(PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BASE);

	if(lwBase==MAP_FAILED){
		printf("ERROR: ERROR: mmap() failed...\n\n");
		close(fd);
		return 1;
	}

	int* sdramBase = mmap(NULL, SDRAM_SPAN, PROT_WRITE, MAP_SHARED, fd, SDRAM_BASE);

	if(sdramBase==MAP_FAILED){
		printf("ERROR: ERROR: mmap() failed...\n\n");
		close(fd);
		return 1;
	}

	volatile int *leds=(int*) (lwBase+ ((LED_BASE)&(LW_MASK)));

	printf("> Addresses loaded successfully\n");

	// Declaration of used variables
	int grayMax;
	int m, n;
	FILE *imageFile;
	char* inputFileName = "photo.pgm";
	char* outputFileName = "photoOut.pgm";
	int iFinalARM, jFinalARM, iInitialNIOS, jInitialNIOS;
	float fracARM, fracNIOS;
	clock_t start, endARM, endNIOS;
	double totalTime;

	fracARM = 1; // Default value for ARM

	// Get the arguments
	if(argc>1 && argc<5){
		inputFileName=argv[1];
		outputFileName=argv[2];
	} else{
		printf("** Using default in/out files **\n");
	}
	if(argc==4){
		fracARM = atof(argv[3]);
	}

	fracNIOS = 1-fracARM; // Sets the fraction of NIOS

	printf("> ARM processing fraction= %f \n", fracARM);
	printf("> NIOS processing fraction= %f \n", fracNIOS);

	printf("> Applying the median filter to: \n\t+ %s\n", inputFileName);

	// Open the input file and read the data.
	imageFile = fopen ( inputFileName, "r" );

	if ( !imageFile ) {
		fprintf ( stderr, "\n" );
		fprintf ( stderr, "MedianFilter - Fatal error!\n" );
		fprintf ( stderr, "  Could not open the file  \n\t+%s\n", inputFileName );
		exit ( 1 );

	}

	// Load the image header to get the information
	pgmaReadHeader ( imageFile, &m, &n, &grayMax );

	printf ( "\n> Image Info\n" );
	printf ( "\tNumber of rows =          %d\n", m );
	printf ( "\tNumber of columns =       %d\n", n );
	printf ( "\tMaximum pixel intensity = %d\n\n", grayMax );

	// Sets the bounds of i and j of the image
	iFinalARM = fracARM*m;
	jFinalARM = n;
	iInitialNIOS = fracARM*m ;
	jInitialNIOS = 0;

	// Data to communicate the NIOS
	sdramBase[0] = fracNIOS*100;
	sdramBase[1] = m;
	sdramBase[2] = n;
	sdramBase[3] = iInitialNIOS;
	sdramBase[4] = jInitialNIOS;

	int* imagenSDRAM = (int*)(sdramBase+MEM_OFFSET); // To avoid rewrite of communication data

	pgmaReadData ( imageFile, m, n, imagenSDRAM ); // Saves the image in the SDRAM
	medianFilterBorders(m, n, imagenSDRAM); // Processes the 4 borders

	start = clock();

	// NIOS processing
	*leds = 0xFF; // Starts the processing in NIOS

	// ARM processing
	medianFilter(m, n, imagenSDRAM, 0, 0, iFinalARM, jFinalARM ); // ARM
	endARM = clock();

	totalTime = (double) (endARM-start)/ CLOCKS_PER_SEC;
	printf("> Total time ARM: %f s\n", totalTime);

	while(*leds==0xFF){} // until NIOS stops the processing
	endNIOS = clock();

	if(fracNIOS==0){endNIOS = start;} // case no NIOS processing

	totalTime = (double) (endNIOS-start)/ CLOCKS_PER_SEC;
	printf("> Total time NIOS: %f s\n", totalTime);

	//medianFilter(m, n, imagenSDRAM, iInicialNIOS, jInicialNIOS, m, n ); //NIOS

	pgmaWrite ( outputFileName, m, n, imagenSDRAM ); // Saves the image in a file

	fclose ( imageFile );

	printf("\n> Filter applied correctly to \n\t+ %s\n\n", outputFileName);

	return 0;
}
