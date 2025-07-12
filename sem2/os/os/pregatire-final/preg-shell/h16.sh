#!/bin/bash

#16. Write a script that receives program/process names as command line arguments. The script will monitor all the processes in the system, and whenever a program with one of those names is run, the script will kill it and display a message. (see commands ps, kill, killall).

if [ $# -lt 1 ]; then
	echo "insufficients arguments"
	exit 1
fi

while true; do
	for name in $@; do
		 if [ $(ps -ef | grep -E -q $name | wc -l) -gt 0 ]; then
              kill $(ps -ef | grep -E -q $name | awk '{print $2}')
         fi
	done
done

