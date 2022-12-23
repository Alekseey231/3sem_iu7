#!/bin/bash
rc=10
if [[ $# -eq 1 ]] || [[ $# -eq 2 ]];
then
	args=""
	if [[ $# -eq 2 ]]; then
		args=$(cat "$2")
	fi
	if [[ -v $USE_VALGRIND ]]; then
		num=$(echo "$1" | grep -oE "[0-9]{1,2}")
		a="valgrind -q --log-file=../data/neg_${num}_valgrind.log ../../app.exe $args < $1 > ../data/out.txt"
		rc=1
	else
		a="../../app.exe $args < $1 > ../data/out.txt"
		rc=5
	fi
	if eval "$a"; then
		if [[ -v $USE_VALGRIND ]]; then
			if [[ -s ../data/neg_${num}_valgrind.log ]]; then
				rc=$((rc+2))
			else
				rc=$((rc+1))
			fi
		else
			rc=$((rc+1))
		fi
	else
		if [[ -v $USE_VALGRIND ]]; then
			if [[ -s ../data/neg_${num}_valgrind.log ]]; then
				rc=$((rc+3))
			fi
		fi;
	fi
fi
if [[ $rc -eq 1 ]]; then
	rc=0
fi
exit $rc
