#!/bin/bash

#18. Write a script that finds recursively in the current folder and displays all the regular files that have write permissions for everybody (owner, group, other). Then the script removes the write permissions from everybody. Hint: use chmod's symbolic permissions mode (see the manual). 

curr_dir=$(pwd)

for f in $(find $curr_dir -type f -perm -a=w); do
	ls -l $f | awk '{print $1 " " $9}'
	chmod a-w $f
	ls -l $f | awk '{print $1 " " $9}'
done 

