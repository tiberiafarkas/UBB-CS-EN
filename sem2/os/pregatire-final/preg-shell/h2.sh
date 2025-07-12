#!/bin/bash

#2. Write a bash script that counts all the lines of code in the C files from the directory given as command-line argument, excluding lines that are empty or contain only spaces.

if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

c=0
for f in $(find $1); do
	if $(file $f | grep -E -q "C source"); then
		nr=$(grep -E -c -v "^ *$" $f)
		echo "$f: $nr lines"
		c=$((c+nr))
	fi
done

echo $c
