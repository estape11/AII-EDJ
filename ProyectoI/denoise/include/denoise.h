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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int *grayMedianNews ( int, int, int[] );
int i4vecFrac ( int, int [], int  );
int i4vecMedian ( int, int [] );
void pgmaReadData ( FILE* , int, int, int* );
void pgmaReadHeader ( FILE*, int*, int*, int* );
void pgmaWrite ( char* ,int , int, int* );
void pgmaWriteData ( FILE* , int, int, int* );
void pgmaWriteHeader ( FILE*, char*, int, int, int );
