#!/bin/bash

#Consider a file containing a username on each line. Generate a comma-separated string with email addresses of the users that exist. The email address will be obtained by appending "@scs.ubbcluj.ro" at the end of each username. Make sure the generated string does NOT end in a comma.

if [ $# -lt 1 ]; then
	echo "you must provide a file"
	exit 1
fi

res=""
for name in $(cat $1); do
	new="$name@scs.ubbcluj.ro"
	res="$res,$new"
done

echo $res | sed "s/^,//"
