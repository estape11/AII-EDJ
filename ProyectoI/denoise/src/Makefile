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

APP=main
CC=gcc
LIBS=../lib
INCLUDE=../include
AR=ar
LINKERFLAGS=-ldenoise -lm
OUT=../bin

all: $(APP)

$(APP).o:$(APP).c
		$(CC) -c $(APP).c -o $(APP).o -I$(INCLUDE)

$(APP):$(APP).o
		$(CC) -o $(OUT)/$(APP) $(APP).o -L$(LIBS) $(LINKERFLAGS) -static

clean:
		rm -f  $(OUT)/$(APP)*
		rm -f *.o 
		rm -f *.so
		rm -f *.a

.PHONY:clean
