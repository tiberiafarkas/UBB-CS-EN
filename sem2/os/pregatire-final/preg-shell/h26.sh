#!/bin/bash

#26.  Write a bash script that receives any number of command-line arguments. For each argument that is a directory, find in it recursively and display: - all the subdirectories that are empty or contain only hidden files. - all the files that are empty or contain only whitespaces (in their content, not in their name). Note: hidden files always have a name that starts with "."

if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

for f in $@; do
	if [ -d $f ]; then
		for s in $(find $f); do
			if [ -d $s ]; then
				if [ "$(du -b "$s" | awk '{print $1}')" == "0" ]; then
					echo "$s empty directory"
				else
					all=$(ls -l $s | wc -l)
					hidden=$(ls -a $s | grep -E -o "^\..*" | wc -l)
					if [ $all -eq $hidden ]; then
						echo "$s contains only hidden files"
					fi   
				fi
			elif [ -f $s ]; then
				if [ $(du -b $s | awk '{print $1}') -eq 0 ]; then
					echo "$s empty file"
				elif ! $(cat $s | grep -E -q "^[^ ]+$"); then
					echo "$s contains only whitespaces"
				fi
			fi
		done
	fi
done

