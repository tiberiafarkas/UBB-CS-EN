#!/bin/bash

#20. Write a shell script that receives any number of words as command line arguments, and continuously reads from the keyboard one file name at a time. The program ends when all words received as parameters have been found at least once across the given files. 
#Example: Assume that 
#file1.txt contains word1 and word2 
#file2.txt does not contain any of the 3 words 
#file3.txt contains word2 and word 3 
#./script.sh word1 word2 word3 
#We input the following: 
#file1.txt 
#file2.txt 
#file3.txt 
#The program stops after reading file3.txt because 
#word1 has been found in file1.txt 
#word2 has been found in file1.txt and file3.txt 
#word3 has been found in file3.txt

if [ $# -lt 1 ]; then
	echo "insufficient arguments"
	exit 1
fi

found=""
f=""
c=$#
while true; do
	echo "$found"
	read -p "introduce file: " f
	if [ -f "$f" ]; then
		for a in $@; do
			if [ $(echo $found | grep -E "$a" | wc -l) -eq 0 ]; then
				if grep -E -q "$a" $f; then
					c=$((c-1))
					found="$found $a"
				fi
			fi
		done
		if [ $c -eq 0 ]; then
			break
		fi
	else
		echo "please introduce a regular file"	
	fi
done


