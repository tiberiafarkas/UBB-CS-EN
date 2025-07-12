#!/bin/bash

while read src dest; do
	if [ -f "$src" ]; then
		cp "$src" "$dest"
	fi
done < a.txt	
