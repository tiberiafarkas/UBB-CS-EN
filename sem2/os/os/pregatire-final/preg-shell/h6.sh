#!/bin/bash

#6. Write a bash script that sorts the file given as command line arguments in ascending order according to their file size in bytes.

if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

for a in $@; do
	if [ -f "$a" ]; then
		du -b $a
	fi
done | sort -n

