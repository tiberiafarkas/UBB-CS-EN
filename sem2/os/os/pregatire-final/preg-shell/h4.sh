#!/bin/bash

#Write a bash script that receives any number of command line arguments and prints on the screen, for each argument, if it is a file, a directory, a number or something else.

if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

for a in $@; do
	if [ -f $a ]; then
		echo "$a is a regular file"
	elif [ -d $a ]; then
		echo "$a is a directory"
	elif $(echo $a | grep -E -q "^[0-9]+$"); then
		echo "$a is a number"
	else
		echo "$a is something else"
	fi
done

