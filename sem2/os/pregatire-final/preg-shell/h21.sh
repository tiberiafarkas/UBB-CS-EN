#!/bin/bash

#21. Write a shell script that, for all the users in /etc/passwd, creates a file with the same name as the username and writes in it all the ip addresses from which that user has logged in. (hint: use the last command to find the ip addresses) 

dir="21"
if [ ! -d "$dir" ]; then
	mkdir $dir
fi

users=$(cat /etc/passwd | awk -F: '{print $1}')
for u in $users; do
	if [ ! -f $dir/$u ]; then
		touch $dir/$u
	fi
	for ip in $(last | grep -E "$u" | awk '{print $4}'); do 
		echo "$u $ip"
		echo "$ip" > $dir/$u
	done
done 

