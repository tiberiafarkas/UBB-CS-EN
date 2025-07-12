#!/bin/bash

#8. Write a script that reads filenames until the word "stop" is entered. For each filename, check if it is a text file and if it is, print the number of words on the first line.(Hint: test command to check if regular file; file command to check if text file)

while true; do
	f=""
	read -p "Enter file: " f
	if [ -f "$f" ]; then
		if file $f | grep -E -q "text"; then
			echo "$f has $(head -1 $f | wc -w)"
		fi
	elif [ "$f" = "stop" ]; then
		break
	fi
done 


