#!/bin/bash

#15. Calculate the average of all process ids in the system per user.

prev=""
count=0
sum=0
for user in $(ps -ef | awk 'NR > 1{print $1","$2}' | sort); do
	curr=$(echo $user | awk -F, '{print $1}')
	pid=$(echo $user | awk -F, '{print $2}')
	if [[ "$curr" != "$prev" && "$prev" != "" ]]; then
		if [ $count -ne 0 ]; then
			echo "Average for $prev: $((sum/count))"
		fi
		sum=0
		count=0
	fi
	prev=$curr
	sum=$((sum+pid))
	count=$((count+1))
done

echo "Average for $prev: $((sum/count))"
