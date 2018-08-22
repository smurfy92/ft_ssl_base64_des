#!/bin/bash

if [ ! -f ft_ssl ]; then
	make
fi
echo "And above all," > file
TEST[0]=$(echo "pickle rick" | ./ft_ssl md5)
TEST[1]=$(echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p)
TEST[2]=$(echo "Pity the living." | ./ft_ssl md5 -q -r)
TEST[3]=$(./ft_ssl md5 file)



RET[0]='c5e433c1dbd7ba01e3763a9483e74b04'
RET[1]=$(printf "Do not pity the dead, Harry.\n2d95365bc44bf0a298e09a3ab7b34d2f")
RET[2]='e20c3b973f63482a778f3fd1869b7f25'
RET[3]='MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'

I=0
while [ $I -lt ${#TEST[@]} ]; do
	if [ "${TEST[$I]}" = "${RET[$I]}" ]; then
		printf "\033[92m Ok \n\033[0m"
	else
		printf "\033[91m Error on test number %d \n\033[0m" $I
		printf "got :\n%s\n" "${TEST[$I]}"
		printf "expected:\n%s\n" "${TEST[$I]}"
	fi
	((I++))
done
rm file
