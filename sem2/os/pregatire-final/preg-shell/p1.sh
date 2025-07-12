#!/bin/bash

#Display a report showing the full name of all the users currently connected, and the number of processes belonging to each of them.

names=$(awk -F" " '{print $1}' ./who.fake)

for name in $names; do
	eval=$(awk -F" " '{print $1}' ps.fake | grep -E "$name" | wc -l)
	echo "$name $eval"
done
