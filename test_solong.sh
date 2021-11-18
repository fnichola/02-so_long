#!/bin/bash

for file in maps/*; do
	echo "------------------------------------------------"
	echo "$file"
	cat $file
	./so_long $file
	echo "------------------------------------------------"
done
