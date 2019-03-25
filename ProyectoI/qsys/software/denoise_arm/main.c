/*
*******************************************************************

				Instituto Tecnológico de Costa Rica
					Ingeniería en Computadores

		Programador: Esteban Agüero Pérez (estape11)
		Lenguaje: C
		Versión: 1.0
		Última Modificación: 25/03/2019

				Arquitectura de Computadores II
				Prof. Jeferson González Gómez

*******************************************************************
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define SDRAM_BASE 0xC4000000
#define LW_BASE 0xFF200000
#define LW_SPAN 0x00200000
#define SDRAM_SPAN 0x04000000
#define LW_MASK (LW_SPAN-1)
#define LED_BASE 0x10000

int main(){
	printf("> Iniciado desde ARM\n");
	int fd;
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	void* virtualBase=mmap(NULL,LW_SPAN,(PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BASE);

	if(virtualBase==MAP_FAILED){
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

	volatile int *ledAddr=(int*) (virtualBase+ ((LED_BASE)&(LW_MASK)));

	printf("> Exito al cargar las direcciones\n");

	sdramBase[0]=8080;
	*ledAddr = 0xFF;

	if( munmap( virtualBase, LW_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );
	}
	return 0;
}
