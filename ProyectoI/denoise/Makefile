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

all: src

lib:
		$(MAKE) -C lib
src: lib	
		$(MAKE) -C src

clean:
		$(MAKE) -C lib clean
		$(MAKE) -C src clean
		clear

.PHONY: all lib src clean