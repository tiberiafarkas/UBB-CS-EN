#!/bin/bash

#13. Find recursively in a given directory all the symbolic links, and report those that point to files/directories that no longer exist. Use option -L to test if a path is a symbolic link, and option -e to test if it exists (will return false if the target to which the link points does not exist) 

if [ $# -lt 1 ]; then
	echo "invalid arguments"
	exit 1
fi

for f in $(find $1); do
	if [ -L $f ]; then
		if ! [ -e "$f" ]; then
			echo "invalid link $f"
		fi
	fi
done
