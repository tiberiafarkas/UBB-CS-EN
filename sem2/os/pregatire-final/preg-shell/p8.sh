#!/bin/bash

#Display all the mounted file systems who are either smaller than than 1GB or have less than 20% free space.

df -BM | cat | awk '{print $2 $5 $6 }' | sed -E "s/([0-9]*)(M)/\1 /" | sed -E "s/([0-9]*)(%)/\1 /" | awk '{ if ( $1 > 1000 || $2 < 20 ) {print $3} }' 
