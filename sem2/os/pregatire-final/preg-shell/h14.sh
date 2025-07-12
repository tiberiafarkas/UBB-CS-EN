#!/bin/bash

#14. Write a bash script that receives a folder name as an argument. Find recursively in the folder the number of times each file name is repeated. 

if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

for f in $(find $1); do
	if [ -f $f ]; then
		echo $f | awk -F/ '{print $NF}'
	fi
done | sort | uniq -c
