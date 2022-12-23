#!/bin/bash
rc=100
if [[ $# -eq 2 ]] || [[ $# -eq 3 ]];
then
	args=""
	if [[ $# -eq 3 ]]; then
		args=$(cat "$3")
	fi
	s=""
	for i in $args; do
		if [ -f "../../${i}" ] || [ "../../${i}" == "../../func_tests/data/out.txt" ]; then
			s="${s} ../../${i}"
		else
			s="${s} ${i}"
		fi;
	done;
	if [[ -v $USE_VALGRIND ]]; then
		num=$(echo "$1" | grep -oE "[0-9]{1,2}")
		a="valgrind -q --log-file=../data/pos_${num}_valgrind.log ../../app.exe $s < $1 > ../data/pr_out.txt"
		rc=1
	else
		a="../../app.exe $s < $1 > ../data/pr_out.txt"
		rc=5
	fi
	if eval "$a"; then
		if [[ -v $USE_VALGRIND ]]; then
			if [[ -s ../data/pos_${num}_valgrind.log ]]; then
				rc=$((rc+1))
			fi;
		fi;
		if ./comparator.sh ../data/out.txt "$2"; then
			rc=$((rc+2))
		fi
	else
		rc=10
	fi
fi
if [[ $rc -eq 3 ]]; then
	rc=0
fi
exit $rc;
