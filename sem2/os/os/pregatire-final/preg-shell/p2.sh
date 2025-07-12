#!/bin/bash

#Find recursively in a directory all ".c" files having more than 500 lines. Stop after finding 2 such files.

if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

c=2
for f in $(find $1); do
	if [ -f $f ]; then
		#we look for "C source" output of file
		if file $f | grep -E -q "C source"; then
			if [ $(wc -l $f | awk '{print $1}') -gt 500 ]; then
				echo "$f"
				c=$((c-1))
				if [ $c -eq 0 ]; then
					break
				fi
			fi
		fi
	fi
done
