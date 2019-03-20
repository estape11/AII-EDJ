#************************************************************
#	Instituto Tecnológico de Costa Rica
#	Ingeniería en Computadores
#
#	Programador: Esteban Agüero Pérez (estape11)
#
#	Última Modificación: 19/03/2019
#
#	Arquitectura de Computadores II
#	Prof. Jeferson González Gómez
#
#************************************************************

SHELL=/bin/bash
APP=denoise
CC=gcc
INCLUDE=../include
AR=ar

all: lib$(APP).a

$(APP).o:$(APP).c
		$(CC) -c $(APP).c -o $(APP).o -I$(INCLUDE)

lib$(APP).a:$(APP).o
		$(AR) rcs lib$(APP).a $(APP).o

clean:
		rm -f *.o 
		rm -f *.so
		rm -f *.a
		
.PHONY:clean