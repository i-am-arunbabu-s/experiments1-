#README: You need to call 'source' command before calling this file to set enviornment in current console.
#eg:- source setenv.sh
#last=$(echo `history |tail -n2 |head -n1` | sed 's/[0-9]* //')
#echo "last command is [$last]"

if [ $_ = '/bin/sh' || $_ = '/bin' ] 
then
	echo "You need to call 'source' command before calling this file to set enviornment in current console."
	echo "eg:- source setenv.sh"
else
	export PATH=/home/agappe/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin:$PATH
	printenv |grep -w PATH
	export CROSS_COMPILE=arm-linux-gnueabihf-
	printenv |grep -w CROSS_COMPILE
	export ARCH=arm
	printenv |grep -w ARCH
fi
