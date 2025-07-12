#!/bin/bash

#10. Write a bash script that sorts all files given as command line arguments descending by size. (first check if an argument is a file) 

if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

for f in $@; do
	if [ -f $f ]; then
		du -b $f
	fi
done | sort -r

