#!/bin/bash

if [[ $# -ne 2 ]]; then
	exit 1
fi
file_out=$(grep "[-+]?[0-9]*[.]?[0-9]+" -Po "$1")
correct_out=$(grep "[-+]?[0-9]*[.]?[0-9]+" -Po "$2")
if [ "$file_out" = "$correct_out" ]; then
	exit 0
fi
exit 1
