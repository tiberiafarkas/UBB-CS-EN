#!/bin/bash

#Find recursively in a directory, all the files that have write permissions for everyone. Display their names, and the permissions before and after removing the write permission for everybody. You will need to use chmod's symbolic permissions mode, instead of the octal mode we have used in class. The the chmod manual for details.

if [ $# -lt 1 ]; then
	echo "no directory provided"
	exit 1
fi

for f in $(find $1 -type f -perm -o=w); do
	ls -l $f | awk '{print $1 " " $9}' 
	chmod o-w $f
	ls -l $f | awk '{print $1 " " $9}'
done 
