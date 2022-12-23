#!/bin/bash

count_pass=0
memory_pass=0
memory_all=0
count_all=0
num_test=0
f=$(find ../data/ | grep -P  'pos_[0-9]{1,2}_in.txt' | sort)
for i in $f
do
o=${i/'in'/'out'}
a=${i/'in'/'args'}
if [[ -e $o ]]; then
	count_all=$((count_all+1))
	if [[ -e $a ]]; then
		./pos_case.sh "$i" "$o" "$a"
	else
		./pos_case.sh "$i" "$o"
	fi
	result=$?
	num_test=$(echo "$i" | grep -Po '[0-9]{1,2}')
	case $result in
	
		1)
			echo -e "\033[31m pos_test_${num_test}: TEST FAILED \033[37m"
			echo -e "\033[32m pos_test_${num_test}: MEMORY PASS \033[37m"
			memory_pass=$((memory_pass+1))
			memory_all=$((memory_all+1))
			;;
		2)
			echo -e "\033[31m pos_test_${num_test}: TEST FAILED \033[37m"
			echo -e "\033[31m pos_test_${num_test}: MEMORY FAILED \033[37m"
			memory_all=$((memory_all+1))
			;;
		0)
			echo -e "\033[32m pos_test_${num_test}: TEST PASS \033[37m"
			echo -e "\033[32m pos_test_${num_test}: MEMORY PASS \033[37m"
			memory_pass=$((memory_pass+1))
			count_pass=$((count_pass+1))
			memory_all=$((memory_all+1))
			;;
		4)
			echo -e "\033[32m pos_test_${num_test}: TEST PASS \033[37m"
			echo -e "\033[31m pos_test_${num_test}: MEMORY FAILED \033[37m"
			count_pass=$((count_pass+1))
			memory_all=$((memory_all+1))
			;;
		5)
			echo -e "\033[31m pos_test_${num_test}: TEST FAILED \033[37m"
			;;
		7)
			echo -e "\033[32m pos_test_${num_test}: TEST PASS \033[37m"
			count_pass=$((count_pass+1))
			;;
		10)
			echo -e "\033[31m pos_test_${num_test}: TEST FAILED: Application exited with a non-zero return code;\033[37m"
			;;
		100)
			echo -e "\033[31m pos_test_${num_test}: TEST FAILED: Invalid count args passed for pos_case;\033[37m"
			;;
	esac
fi
done
if [[ $memory_all -eq 0 ]]; then
	echo -e "\033[35m Positive tests: correct ${count_pass} of ${count_all};\033[37m"
else 
	echo -e "\033[35m Positive tests: correct ${count_pass} of ${count_all}; memory passed ${memory_pass} of ${memory_all};\033[37m"
fi
count_not_pass_all=$((count_all-count_pass+memory_all-memory_pass))
count_pass=0
count_all=0
num_test=0
memory_pass=0
memory_all=0
f=$(find ../data/ | grep -P  'neg_[0-9]{1,2}_in.txt' | sort)
for i in $f
do
a=${i/'in'/'args'}
count_all=$((count_all+1))
if [[ -e $a ]]; then
	./neg_case.sh "$i" "$a"
else
	./neg_case.sh "$i"
fi
result=$?
num_test=$(echo "$i" | grep -Po '[0-9]{1,2}')
case $result in
	
		2)
			echo -e "\033[31m neg_test_${num_test}: TEST FAILED \033[37m"
			echo -e "\033[32m neg_test_${num_test}: MEMORY PASS \033[37m"
			memory_pass=$((memory_pass+1))
			memory_all=$((memory_all+1))
			;;
		3)
			echo -e "\033[31m neg_test_${num_test}: TEST FAILED \033[37m"
			echo -e "\033[31m neg_test_${num_test}: MEMORY FAILED \033[37m"
			memory_all=$((memory_all+1))
			;;
		0)
			echo -e "\033[32m neg_test_${num_test}: TEST PASS \033[37m"
			echo -e "\033[32m neg_test_${num_test}: MEMORY PASS \033[37m"
			memory_pass=$((memory_pass+1))
			count_pass=$((count_pass+1))
			memory_all=$((memory_all+1))
			;;
		4)
			echo -e "\033[32m neg_test_${num_test}: TEST PASS \033[37m"
			echo -e "\033[31m neg_test_${num_test}: MEMORY FAILED \033[37m"
			count_pass=$((count_pass+1))
			memory_all=$((memory_all+1))
			;;
		6)
			echo -e "\033[31m neg_test_${num_test}: TEST FAILED \033[37m"
			;;
		5)
			echo -e "\033[32m neg_test_${num_test}: TEST PASS \033[37m"
			count_pass=$((count_pass+1))
			;;
	esac
done
if [[ $memory_all -eq 0 ]]; then
	echo -e "\033[35m Negative tests: correct ${count_pass} of ${count_all} \033[37m"
else 
	echo -e "\033[35m Negative tests: correct ${count_pass} of ${count_all}; memory passed ${memory_pass} of ${memory_all};\033[37m"
fi


count_not_pass_all=$((count_not_pass_all+count_all-count_pass+memory_all-memory_pass))
exit $count_not_pass_all
