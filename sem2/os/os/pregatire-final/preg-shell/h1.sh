#!/bin/bash

#1. Write a bash script that counts all the C files from a given directory and all of its subdirectories.

if [ $# -lt 1 ]; then
	echo "Insufficient arguments"
	exit 1
fi

c=0
for f in $(find $1); do
	if $(file $f | grep -E -q "C source"); then
		c=$((c+1))
	fi
done

echo $c
