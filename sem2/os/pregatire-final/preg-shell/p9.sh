#!/bin/bash

#Write a script that finds in a given directory hierarchy, all duplicate files and displays their paths. Hint: use checksums to detect whether two files are identical.

if [ $# -lt 1 ]; then
	echo "no directory provided"
	exit 1
fi

for f in $(find $1 -type f -exec md5sum {} \; | awk '{print $1}' | sort | uniq); do
	echo $f
	for g in $(find $1 -type f -exec md5sum {} \; | grep -E $f | awk '{print $2}'); do
		echo $g
	done
done 
