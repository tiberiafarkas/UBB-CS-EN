#!/bin/bash

#5. Write a bash script that keeps reading strings from the keyboard until the name of a readable regular file is given.

f=""
while ! [ -f "$f" ]; do
	read -p "Enter string: " f
done
