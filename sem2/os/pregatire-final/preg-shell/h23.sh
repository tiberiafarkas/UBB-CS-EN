#!/bin/bash

#23. Create a bash script that finds all the text files in a specified folder (the current folder if there is no specified folder). For all such files, the script will report the filesize, permissions, and number of unique lines. 

if [ $# -lt 1 ]; then
	dir=$(pwd)
else
	dir=$1
fi

for f in $(find $dir -type f); do
	size=$(du -b $f | awk '{print $1}')
	lines=$(cat $f | sort | uniq | wc -l)
	perm=$(ls -l $f | awk '{print $1}')
	echo "$size, $lines, $perm"
done



