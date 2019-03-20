#!/bin/bash

# Created by estape11 19/03/2019

if [ $# -eq 1 ]
then
	echo ">> Converting "$1 to $1.pgm
	convert $1 -compress None $1.pgm
	echo '>> Complete'
else
	echo 'Error'
fi
