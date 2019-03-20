/*
*******************************************************************

        Instituto Tecnológico de Costa Rica
          Ingeniería en Computadores

    Programador: Esteban Agüero Pérez (estape11)
    Lenguaje: C
    Versión: 1.0
    Última Modificación: 19/03/2019

        Arquitectura de Computadores II
        Prof. Jeferson González Gómez

*******************************************************************
*/

#include <denoise.h>

int main ( int argc, char *argv[] );

int main ( int argc, char *argv[] ){

  int *g;
  int g_max;
  int *g2;
  char* input_filename = "photo.pgm";
  FILE *input_unit;
  int m;
  int n;
  char* output_filename = "photoOut.pgm";

  if(argc>1 && argc<4){
    input_filename=argv[1];
    output_filename=argv[2];
  } else{
    printf("** Using defaul in/out files **\n");
  }

  printf("> Applying the median filter to: \n\t+ %s\n", input_filename);

  // Open the input file and read the data.

  input_unit = fopen ( input_filename, "r" );

  if ( !input_unit ) {
    fprintf ( stderr, "\n" );
    fprintf ( stderr, "MedianFilter - Fatal error!\n" );
    fprintf ( stderr, "  Could not open the file  \n\t+%s\n", input_filename );
    exit ( 1 );

  }

  pgmaReadHeader ( input_unit, &m, &n, &g_max );

  printf ( "\n> Image Info\n" );
  printf ( "\tNumber of rows =          %d\n", m );
  printf ( "\tNumber of columns =       %d\n", n );
  printf ( "\tMaximum pixel intensity = %d\n\n", g_max );

  g = ( int * ) malloc ( m * n * sizeof ( int ) );

  pgmaReadData ( input_unit, m, n, g );

  fclose ( input_unit );

  g2 = grayMedianNews ( m, n, g );
/*
  Write the denoised images.
*/
  pgmaWrite ( output_filename, m, n, g2 );

  printf("> Filter applied correctly to \n\t+ %s\n", output_filename);

  free ( g );
  free ( g2 );

  return 0;
}