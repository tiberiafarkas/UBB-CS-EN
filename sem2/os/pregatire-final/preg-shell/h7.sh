#!/bin/bash

#7. Write a bash script that calculates the sum of the sizes (in bytes) of all regular files in a folder given as a parameter.(use test to check if the folder exists and if a given file is a regular file) 


if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

if test -d $1; then
	sum=0
	for f in $(ls $1); do
		if test -f $f; then
			size=$(du -b $f | awk '{print $1}')
			echo "$f size $size"
			sum=$((sum+size))
		fi
	done
fi

echo "$sum"
