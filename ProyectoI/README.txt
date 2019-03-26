************************************************************

	Instituto Tecnológico de Costa Rica
	Ingeniería en Computadores

	Programador: Esteban Agüero Pérez (estape11)

	Última Modificación: 24/03/2019

	Arquitectura de Computadores II
	Prof. Jeferson González Gómez

************************************************************
> Para la correcta asignacion de pines, se empleo el TCL script pin_assignment_DE1_SoC para esta funcion y el pin assigment para la SDRAM de Intel
	Tools -> TCL Scripts -> File -> Run

> Para el procesador ARM, se uso la imagen DE1_SoC_SD.img, del siguiente link:
	http://www.terasic.com/downloads/cd-rom/de1-soc/linux_BSP/DE1_SoC_SD.zip

> Compilar todo el proyecto antes de flashear la FPGA (10 minutos aprox)

> El mapa de direcciones se define de la siguiente manera:
	leds -> 0x00010000 - 0x0001000F
	OnChip (NIOS) -> 0x00000000 - 0x0000FFFF
	SDRAM -> 0x04000000 - 0x07FFFFFF
	Axis LW -> 0xFF200000 / 0x00200000
	Axis -> 0xC000000 / 

> Los archivos fuente de los programas para ARM y NIOS se encuentran en ..qsys/software
	* denoise_nios
	* denoise_arm

> Para abrir Eclipse para Nios II
	$ ./intelFPGA_lite/18.1/nios2eds/bin/eclipse-nios2

> Para abrir Eclipse DS-5
	$ ./intelFPGA/18.1/embedded/ds-5/bin/eclipse

> Para copiar un archivo al ARM
	$ scp file root@ip:/home/root/path

> Para copiar un archivo del ARM
	$ scp root@ip:/home/root/path/file /path2paste