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

/**
    This function uses a median filter on a gray scale image to remove noise.
    Input:
          M, N, the number of rows and columns of pixels.
          data[M*N], the noisy grayscale data.
          i and j initial.
          j and j final.
*/

void medianFilter(int m, int n, int* data, int initialI, int initialJ, int finalI, int finalJ ){
	//int *gray;
	int i;
	int j;
	int p[5];

	//gray = ( int * ) malloc ( m * n * sizeof ( int ) );
	// Process the main part of the image:
	for ( i = 1+initialI; i < finalI; i++ ) {
		for ( j = 1+initialJ; j < finalJ; j++ ) {
			p[0] = data[i-1+ j   *m];
			p[1] = data[i+1+ j   *m];
			p[2] = data[i  +(j+1)*m];
			p[3] = data[i  +(j-1)*m];
			p[4] = data[i  + j   *m];

			data[i+j*m] = i4vecMedian ( 5, p );
		}
	}
}

/**
    This function uses a median filter on a gray scale image to remove noise of the border.
    Input:
          M, N, the number of rows and columns of pixels.
          gray[M*N], the noisy grayscale data.

 */
void medianFilterBorders(int m, int n, int* data){
	int i;
	int j;
	int p[5];
	// Process the four borders.
	// Get an odd number of data points,
	for ( i = 1; i < m - 1; i++ ) {
		j = 0;
		p[0] = data[i-1+ j   *m];
		p[1] = data[i+1+ j   *m];
		p[2] = data[i  + j   *m];
		p[3] = data[i  +(j+1)*m];
		p[4] = data[i  +(j+2)*m];
		data[i+j*m] = i4vecMedian ( 5, p );

		j = n - 1;
		p[0] = data[i-1+ j   *m];
		p[1] = data[i+1+ j   *m];
		p[2] = data[i  +(j-2)*m];
		p[3] = data[i  +(j-1)*m];
		p[4] = data[i  + j   *m];
		data[i+j*m] = i4vecMedian ( 5, p );
	}

	for ( j = 1; j < n - 1; j++ ) {
		i = 0;
		p[0] = data[i  + j   *m];
		p[1] = data[i+1+ j   *m];
		p[2] = data[i+2+ j   *m];
		p[3] = data[i  +(j-1)*m];
		p[4] = data[i  +(j+1)*m];
		data[i+j*m] = i4vecMedian ( 5, p );

		i = m - 1;
		p[0] = data[i-2+ j   *m];
		p[1] = data[i-1+ j   *m];
		p[2] = data[i  + j   *m];
		p[3] = data[i  +(j-1)*m];
		p[4] = data[i  +(j+1)*m];
		data[i+j*m] = i4vecMedian ( 5, p );
	}

	// Process the four corners.
	i = 0;
	j = 0;
	p[0] = data[i+1+ j   *m];
	p[1] = data[i  + j   *m];
	p[2] = data[i  +(j+1)*m];
	data[i+j*m] = i4vecMedian ( 3, p );

	i = 0;
	j = n - 1;
	p[0] = data[i+1+ j   *m];
	p[1] = data[i  + j   *m];
	p[2] = data[i  +(j-1)*m];
	data[i+j*m] = i4vecMedian ( 3, p );

	i = m - 1;
	j = 0;
	p[0] = data[i-1+ j   *m];
	p[1] = data[i  + j   *m];
	p[2] = data[i  +(j+1)*m];
	data[i+j*m] = i4vecMedian ( 3, p );

	i = m - 1;
	j = n - 1;
	p[0] = data[i-1+ j   *m];
	p[1] = data[i  + j   *m];
	p[2] = data[i  +(j-1)*m];
	data[i+j*m] = i4vecMedian ( 3, p );
}

/**
    This function search for the K-th smallest entry in an I4VEC.
    Input:
          N, the number of elements of A.
          K, the fractile to be sought.

    Input/output
          A[N]  On input, A is the array to search.
                On output, the elements of A have been somewhat rearranged.
    Output:
          the value of the K-th fractile of A.
 */
int i4vecFrac ( int n, int a[], int k ) {
	int frac;
	int i;
	int iryt;
	int j;
	int left;
	int temp;
	int x;

	if ( n <= 0 ) {
		fprintf ( stderr, "\n" );
		fprintf ( stderr, "i4vecFrac - Fatal error!\n" );
		fprintf ( stderr, "  Illegal nonpositive value of N = %d\n", n );
		exit ( 1 );

	}

	if ( k <= 0 ) {
		fprintf ( stderr, "\n" );
		fprintf ( stderr, "i4vecFrac - Fatal error!\n" );
		fprintf ( stderr, "  Illegal nonpositive value of K = %d\n", k );
		exit ( 1 );

	}

	if ( n < k ) {
		fprintf ( stderr, "\n" );
		fprintf ( stderr, "i4vecFrac - Fatal error!\n" );
		fprintf ( stderr, "  Illegal N < K, K = %d\n", k );
		exit ( 1 );

	}

	left = 1;
	iryt = n;

	for ( ; ; ) {
		if ( iryt <= left )
		{
			frac = a[k-1];
			break;
		}

		x = a[k-1];
		i = left;
		j = iryt;

		for ( ; ; ) {
			if ( j < i ) {
				if ( j < k ) {
					left = i;

				}
				if ( k < i ) {
					iryt = j;

				}
				break;
			}

			// Find I so that X <= A(I).
			while ( a[i-1] < x ) {
				i = i + 1;

			}

			// Find J so that A(J) <= X.
			while ( x < a[j-1] ) {
				j = j - 1;

			}

			if ( i <= j ) {
				temp   = a[i-1];
				a[i-1] = a[j-1];
				a[j-1] = temp;
				i = i + 1;
				j = j - 1;

			}
		}
	}

	return frac;
}

/**
    This function returns the median of an unsorted I4VEC.
    Input:
          N, the number of elements of A.
    Input/output
          A[N], the array to search.
            On output, the order of the elements of A has been somewhat changed.

    Output:
          the value of the median of A.
 */
int i4vecMedian ( int n, int a[] ){
	int k;
	int median;

	k = ( n + 1 ) / 2;

	median = i4vecFrac ( n, a, k );

	return median;
}


/**
    This function reads the data in an ASCII PGM file.
    Input:
          file_in, a pointer to the file containing the data.
          xsize, ysize, the number of rows and columns of data.
    Output:
          G, the array of xsize by ysize data values.
 */
void pgmaReadData ( FILE *file_in, int xsize, int ysize, int *g ){
	int i;
	int j;
	int n;

	for ( j = 0; j < ysize; j++ ) {
		for ( i = 0; i < xsize; i++ ) {
			n = fscanf ( file_in, "%d", g );

			if ( n != 1 ) {
				fprintf ( stderr, "\n" );
				fprintf ( stderr, "pgmaReadData - Fatal error!\n" );
				fprintf ( stderr, "  Unable to read data.\n" );
				exit ( 1 );

			}
			g = g + 1;
		}
	}
	return;
}


/**
    This function reads the header of an ASCII PGM file.
    Input:
          file_in, a pointer to the file.

    Output:
          xsize, ysize, the number of rows and columns of data.
          maxg, the maximum gray value.
 */
void pgmaReadHeader ( FILE *file_in, int *xsize, int *ysize, int *maxg ) {
# define LINE_MAX 255
	int count;
	char *error;
	char line[LINE_MAX];
	char *next;
	int step;
	int width;
	char word[LINE_MAX];

	step = 0;

	while ( 1 ) {
		error = fgets ( line, LINE_MAX, file_in );

		if ( !error ) {
			fprintf ( stderr, "\n" );
			fprintf ( stderr, "pgmaReadHeader - Fatal error!\n" );
			fprintf ( stderr, "  End of file.\n" );
			exit ( 1 );

		}

		next = line;

		if ( line[0] == '#' ) {
			continue;

		}

		if ( step == 0 ) {
			count = sscanf ( next, "%s%n", word, &width );
			if ( count == EOF ) {
				continue;

			}
			next = next + width;
			if ( strcmp ( word, "P2" ) != 0 && strcmp ( word, "p2" ) != 0 ) { // compresed image
				fprintf ( stderr, "\n" );
				fprintf ( stderr, "pgmaReadHeader - Fatal error.\n" );
				fprintf ( stderr, "  Bad magic number = \"%s\".\n", word );
				exit ( 1 );

			}
			step = 1;
		}

		if ( step == 1 ) {

			count = sscanf ( next, "%d%n", xsize, &width );
			next = next + width;
			if ( count == EOF ) {
				continue;

			}
			step = 2;
		}

		if ( step == 2 ) {
			count = sscanf ( next, "%d%n", ysize, &width );
			next = next + width;
			if ( count == EOF ) {
				continue;

			}
			step = 3;
		}

		if ( step == 3 ) {
			count = sscanf ( next, "%d%n", maxg, &width );
			next = next + width;
			if ( count == EOF ) {
				continue;

			}
			break;
		}

	}
	return;
# undef LINE_MAX
}

/**
    This funtion writes the header and data for an ASCII PGM file.
    Input:
          file_out_name, the name of the file.
          xsize, ysize, the number of rows and columns of data.
          G, the array of xsize by ysize data values.
 */
void pgmaWrite ( char *file_out_name, int xsize, int ysize, int *g ) {
	FILE *file_out;
	int i;
	int *indexg;
	int j;
	int maxg;

	// Open the output file.
	file_out = fopen ( file_out_name, "wt" );

	if ( !file_out ) {
		fprintf ( stderr, "\n" );
		fprintf ( stderr, "pgmaWrite - Fatal error!\n" );
		fprintf ( stderr, "  Cannot open the output file \"%s\".\n", file_out_name );
		exit ( 1 );

	}

	// Compute the maximum.
	maxg = 0;
	indexg = g;

	for ( j = 0; j < ysize; j++ ) {
		for ( i = 0; i < xsize; i++ ) {
			if ( maxg < *indexg ) {
				maxg = *indexg;

			}
			indexg = indexg + 1;

		}
	}

	// Write the header.
	pgmaWriteHeader ( file_out, file_out_name, xsize, ysize, maxg );

	// Write the data.
	pgmaWriteData ( file_out, xsize, ysize, g );

	// Close the file.
	fclose ( file_out );

	return;
}

/**
    This function writes the data for an ASCII PGM file.
    Input
 *file_out, a pointer to the file.
          xsize, ysize, the number of rows and columns of data.
          g, the array of xsize by ysize data.
 */
void pgmaWriteData ( FILE *file_out, int xsize, int ysize, int *g ) {
	int i;
	int *indexg;
	int j;
	int numval;

	indexg = g;
	numval = 0;

	for ( j = 0; j < ysize; j++ ) {
		for ( i = 0; i < xsize; i++ ) {
			fprintf ( file_out, "%d", *indexg );
			numval = numval + 1;
			indexg = indexg + 1;

			if ( numval % 12 == 0 || i == xsize - 1 || numval == xsize * ysize ) {
				fprintf ( file_out, "\n" );

			}
			else {
				fprintf ( file_out, " " );

			}

		}
	}
	return;
}

/**
    This function writes the header of an ASCII PGM file.
    Input:
          file_out, a pointer to the file.
          file_out_name, the name of the file.
          xsize, ysize, the number of rows and columns of data.
          maxg, the maximum gray value.
 */
void pgmaWriteHeader ( FILE *file_out, char *file_out_name, int xsize, int ysize, int maxg ) {
	fprintf ( file_out, "P2\n" );
	fprintf ( file_out, "# %s created by PGMA_IO::PGMA_WRITE.\n",
			file_out_name );
	fprintf ( file_out, "%d %d\n", xsize, ysize );
	fprintf ( file_out, "%d\n", maxg );

	return;
}
