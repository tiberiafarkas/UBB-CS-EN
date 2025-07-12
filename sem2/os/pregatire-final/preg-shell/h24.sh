#!/bin/bash

#24. Write a bash script that receives as command line arguments pairs of arguments A and B. For each pair, if argument A contains argument B, display a message.

if [ $# -lt 2 ]; then
	echo "insufficient arguments"
	exit 1
fi

if [ $(($# % 2)) -eq 1 ]; then
	echo "you must provide a even number of arguments"
	exit 1
fi

while [ $# -ge 2 ]; do
	a=$1
	b=$2
	if echo $a | grep -E -q "$b"; then
		echo "$b appears in $a"
	fi
	shift 2
done


