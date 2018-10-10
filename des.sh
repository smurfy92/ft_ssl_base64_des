#!/bin/bash

if [ ! -f ft_ssl ]; then
	make
fi

TEST[0]=$(echo "repeat after me 'encoding is not encryption'" | ./ft_ssl base64)
TEST[1]=$(echo "All your base are belong to us. You have no chance make your time." | ./ft_ssl base64 | ./ft_ssl base64 -d)

RET[0]='cmVwZWF0IGFmdGVyIG1lICdlbmNvZGluZyBpcyBub3QgZW5jcnlwdGlvbicK'
RET[1]='All your base are belong to us. You have no chance make your time.'

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