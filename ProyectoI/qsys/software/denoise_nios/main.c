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
#include <stdlib.h>

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

	if ( n <= 0 || n < k || k <= 0) {
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
    This function uses a median filter on a gray scale image to remove noise.
    Input:
          M, N, the number of rows and columns of pixels.
          data[M*N], the noisy grayscale data.
          i and j initial.
          j and j final.
*/

void medianFilter(int m, int n, int* data, int initialI, int initialJ, int finalI, int finalJ ){
	//int *gray;
	int i, j;
	int p[5];

	//gray = ( int * ) malloc ( m * n * sizeof ( int ) );
	// Process the main part of the image:
	for ( i = initialI; i < finalI - 1; i++ ) {
		for ( j = initialJ; j < finalJ - 1; j++ ) {
			p[0] = data[i-1+ j   *m];
			p[1] = data[i+1+ j   *m];
			p[2] = data[i  +(j+1)*m];
			p[3] = data[i  +(j-1)*m];
			p[4] = data[i  + j   *m];

			data[i+j*m] = i4vecMedian ( 5, p );
		}
	}
}

int main() {
	printf("> NIOS II Started\n");
	volatile int* leds = (int*) 0x10000; // leds address
	volatile int* sdram = (int*) 0x04100000; // SDRAM address
	*leds=0x0;

	int m, n, iInitialNIOS, jInitialNIOS;
	//float fracNIOS;

	volatile int* imageSDRAM = (sdram + 5); // to not rewrite the commutication data

	while(1){
		while(*leds!=0xFF){} // wait until ARM send a signal to start
		//fracNIOS = sdram[0]/100;

		m = sdram[1];
		n = sdram[2];
		iInitialNIOS = sdram[3];
		jInitialNIOS = sdram[4];
		//printf("> Received parameters: \n\t fraction: %f\n\t m: %d\n\t n: %d\n\t i: %d\n\t j: %d", fracNIOS, m, n,iInitialNIOS,jInitialNIOS);

		// NIOS processing
		medianFilter(m, n, imageSDRAM, iInitialNIOS, jInitialNIOS, m, n );
		printf("+ Executed\n");
		*leds=0x1; // To send the termination code to ARM
	}
	return 0;
}
