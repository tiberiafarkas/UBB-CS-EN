#!/bin/bash

#11. Write a script that extracts from all the C source files given as command line arguments the included libraries and saves them in a file. (use the file command to check if a file is a C source file) 

if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

if ! [ -f "libraries.txt" ]; then
	touch libraries.txt
fi

file="libraries.txt"

for f in $@; do
	if $(file $f | grep -E -q "C source"); then
		args=$(cat $f | grep -E "^#include.+$")
		echo "$args" > "$file"
	fi
done
