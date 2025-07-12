#!/bin/bash

#22. Create a bash script that displays every second the process count per user sorted descending by process count for all users specified as command line arguments. If no arguments are given, the script will display the process count per user for all users. 

if [ $# -lt 1 ]; then
	ps -ef | awk 'NR > 1 {print $1}' | sort | uniq -c
	exit 0
fi

while true; do
	for u in $@; do
		ps -ef | grep -E "$u" | awk 'NR > 1 {print $1}' | sort | uniq -c
	done | sort -r
	sleep 1
done

