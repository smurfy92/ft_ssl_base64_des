#!/bin/bash

if [ ! -f ft_ssl ]; then
	make
fi

TEST[0]=$(echo toto | ./ft_ssl base64 -e)

RET[0]='dG90bwo='

I=0
while [ $I -lt ${#TEST[@]} ]; do
	if [ "${TEST[$I]}" = "${RET[$I]}" ]; then
		printf "\033[92m Ok \n\033[0m"
	else
		printf "\033[91m Error on test number %d \n\033[0m" $I
		printf "got :\n%s\n" "${TEST[$I]}"
		echo "${TEST[$I]}" > "test_${I}_diff1"
		echo "${RET[$I]}" > "test_${I}_diff2"
		printf "expected:\n%s\n" "${RET[$I]}"
	fi
	((I++))
done