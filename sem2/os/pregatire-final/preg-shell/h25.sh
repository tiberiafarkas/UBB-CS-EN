#!/bin/bash

#25. Write a bash script that receives as command line arguments the names of either files or directories.  - If the argument is a regular file, then display the first 10 lines from that file. - If the argument is a directory, create a file in that directory with the same name as the directory + ".info", and store the output of the ls -l in that file. - If the argument is neither a regular file or a directory, display a message. 

if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

for f in $@; do
	if [ -f $f ]; then
		cat $f | head -10
	elif [ -d $f ]; then
		touch "$f.info"
		ls -l $f > "$f/$f.info"
	else
		echo "$f is neither a file or a directory"
	fi
done

