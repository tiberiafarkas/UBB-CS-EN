#!/bin/bash
#6. RO: Scrieţi un script Shell UNIX care afişează toate argumentele din linia de comandă fără a folosi FOR.


c=0
while (($c<=$#)); do
    echo "${!c}"
    ((c++))
done

#while test $# -gt 0; do
#	echo "$1"
#	shift
#done
