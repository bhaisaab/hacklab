#!/bin/bash
while read line
do
	if [[ $line -eq 42 ]]; then
		exit 0
	fi
	echo $line
done
