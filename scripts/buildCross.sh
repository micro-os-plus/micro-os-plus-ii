#! /bin/bash

# run arguments: generate jUnit XML files
MAKE_ARGS=-Wr,-x,junit.xml

XCDLBUILD="xcdl-python.git/scripts/xcdlBuild.sh"
REPO="micro-os-plus-se.git/packages"
UNAME=`uname`

FULL=""
DEST=build

while [ $# -gt 0 ]
do
	#echo $1
	if [ $1 == "--dest" -a $# -gt 1 ]
	then
		#echo "Dest" $2
		DEST=$2
		shift
	else
		echo "unsupported" $1
	fi
	shift
done

# this is x86_64 on 64 bit machines
MACHINE=$(uname -m)

function runTest()
{
	[ $# -ge 1 ] || exit 1
	
	#echo $1
	#return
	
	if [ $# -ge 2 ]
	then
		action=$2
	else
		action='all'
	fi
	/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=$1 $MAKE_ARGS $action
	[ $? -eq 0 ] || exit $? 
}

function runTestPair()
{
	[ $# -ge 1 ] || exit 1

	runTest $1"_Debug" $2
	runTest $1"_Release" $2
}

function runTestCollection()
{
	[ $# -ge 1 ] || exit 1

	runTestPair "stm32h103_cmsis_"$1
	runTestPair "olimexinostm32_cmsis_"$1
	runTestPair "stm32p107_cmsis_"$1
	runTestPair "stm32e407_cmsis_"$1
	runTestPair "stm32f4discovery_cmsis_"$1
}

echo "XCDL buildCross: started"

if [ $UNAME == "Linux" ]
then

	time (
		echo "add code"
	)

elif [ $UNAME == "Darwin" ]
then

	
	time ( 

		PATH_ARM="/usr/local/gcc-arm-none-eabi-4_7/bin"
		
		if [ -x "$PATH_ARM/arm-none-eabi-g++" ]
		then
			(PATH=$PATH_ARM:$PATH; runTestCollection "aep_gcc" )
		fi
			
	)

fi

echo
echo "XCDL buildCross: completed, results in $DEST"
echo
echo "PWD=`pwd`"
