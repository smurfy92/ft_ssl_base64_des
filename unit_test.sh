#!/bin/bash

if [ ! -f ft_ssl ]; then
	make
fi
echo "And above all," > file
echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > big_smoke_order_remix
TEST[0]=$(echo "pickle rick" | ./ft_ssl md5)
TEST[1]=$(echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p)
TEST[2]=$(echo "Pity the living." | ./ft_ssl md5 -q -r)
TEST[3]=$(./ft_ssl md5 file)
TEST[4]=$(./ft_ssl md5 -r file)
TEST[5]=$(./ft_ssl md5 -s "pity those that aren't following baerista on spotify.")
TEST[6]=$(echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file)
TEST[7]=$(echo "some of this will not make sense at first" | ./ft_ssl md5 file)
TEST[8]=$(echo "but eventually you will understand" | ./ft_ssl md5 -p -r file)
TEST[9]=$(echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file)
TEST[10]=$(echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar")
TEST[11]=$(echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file)
TEST[12]=$(./ft_ssl sha256 -q big_smoke_order_remix)
TEST[13]=$(./ft_ssl sha256 -s "wubba lubba dub dub")


RET[0]='c5e433c1dbd7ba01e3763a9483e74b04'
RET[1]=$(printf "Do not pity the dead, Harry.\n2d95365bc44bf0a298e09a3ab7b34d2f")
RET[2]='e20c3b973f63482a778f3fd1869b7f25'
RET[3]='MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
RET[4]='53d53ea94217b259c11a5a2d104ec58a file'
RET[5]=$(printf "MD5 (\"pity those that aren't following baerista on spotify.\") = a3c990a1964705d9bf0e602f44572f5f")
RET[6]=$(printf "be sure to handle edge cases carefully\n3553dc7dc5963b583c056d1b9fa3349c\nMD5 (file) = 53d53ea94217b259c11a5a2d104ec58a")
RET[7]='MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
RET[8]=$(printf "but eventually you will understand\ndcdd84e0f635694d2a943fa8d3905281\n53d53ea94217b259c11a5a2d104ec58a file")
RET[9]=$(printf "GL HF let's go\nd1e3cc342b6da09480b27ec57ff243e2\nMD5 (\"foo\") = acbd18db4cc2f85cedef654fccc4a4d8\nMD5 (file) = 53d53ea94217b259c11a5a2d104ec58a")
RET[10]=$(printf "one more thing\na0bd1876c6f011dd50fae52827f445f5\nacbd18db4cc2f85cedef654fccc4a4d8 \"foo\"\n53d53ea94217b259c11a5a2d104ec58a file\nft_ssl: md5: -s: No such file or directory\nft_ssl: md5: bar: No such file or directory")
RET[11]=$(printf "just to be extra clear\n3ba35f1ea0d170cb3b9a752e3360286c\nacbd18db4cc2f85cedef654fccc4a4d8\n53d53ea94217b259c11a5a2d104ec58a")
RET[12]='a8dc621c3dcf18a8a2eddae1845e8e5f6498970a867056ac5f7121ac3d66cfd9'
RET[13]=$(printf "SHA256 (\"wubba lubba dub dub\") = 23a0944d11b5a54f1970492b5265c732044ae824b7d5656acb193e7f0e51e5fa")

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
rm file
rm big_smoke_order_remix
