#!/bin/bash

#9. Write a script that receives as command line arguments pairs consisting of a filename and a word. For each pair, check if the given word appears at least 3 times in the file and print a corresponding message.

if [ $# -lt 2 ]; then
	echo "insufficient arguments"
	exit 1;
fi

if [ $(($# % 2)) -eq 1 ]; then
	echo "wrong number of arguments provided"
	exit 1
fi

args=("$@")

for ((i=0; i<$#; i+=2)); do
	f="${args[$i]}"
	w="${args[$i+1]}"
	echo "$f $w"
	if [ -f "$f" ]; then
		c=$(grep -E -o "\b$w\b" $f | wc -l)
		if [ $c -gt 3 ]; then
			echo "$w appears at least 3 times in $f"
		fi
	else
		echo "not e regular file"
	fi
done

