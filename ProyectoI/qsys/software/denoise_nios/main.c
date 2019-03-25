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
#include <system.h>

int main()
{
	printf("> Iniciado NIOS II\n");
	volatile int* leds = (int*) 0x10000; // Direccion de los leds
	volatile int* sdram = (int*) 0x04000000; // Direccion de la SDRAM
	*leds=0x0;
	while(*leds!=0xFF){

	}
	printf("** Lectura de sdram[0] = %d **\n", sdram[0]);
	*leds=0xAA;
	return 0;
}
