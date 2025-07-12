#!/bin/bash

#Write a script that receives dangerous program names as command line arguments. The script will monitor all the processes in the system, and whenever a program known to be dangerous is run, the script will kill it and display a message.

if [ $# -lt 1 ]; then
	echo "no names received"
	exit 1
fi

while true; do
	for name in $@; do
		if $(ps -ef | grep -E -q $name | wc -l) -gt 0; then
			kill $(ps -ef | grep -E -q $name | awk '{print $2}')
		fi
	done
done 
