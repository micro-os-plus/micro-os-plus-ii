#! /bin/bash

# run arguments: generate jUnit XML files
MAKE_ARGS=-Wr,-x,junit.xml

XCDLBUILD="xcdl-python.git/scripts/xcdlBuild.sh"
REPO="micro-os-plus-se.git/packages"
UNAME=`uname`

DEST=build

declare -a testNames=( 'minimal' 'trace' 'fpos' 'ios_base' 'basic_ios' 'streambuf' 'ostream' 'ostreamconv' )

# Check for custom destination folder
if [ $# -gt 0 ]
then
  DEST=$1
fi

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
		action='run'
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

function runTestArray()
{
	[ $# -ge 2 ] || exit 1

	for bc in "${testNames[@]}"
	do
		runTestPair $1"_"$bc"_"$2 $3
	done
}


echo "XCDL runTests: started"

if [ $UNAME == "Linux" ]
then

	time (
		if [ "$MACHINE" == "x86_64" ]
		then
			(PATH=$PATH; runTestArray "linux" "x64_gcc" "run")
		fi
		(PATH=$PATH; runTestArray "linux" "x32_gcc" "run")
	)

elif [ $UNAME == "Darwin" ]
then

	
	time ( 
	
		# clang is always available on OS X
		if [ "$MACHINE" == "x86_64" ]
		then
			(PATH=$PATH; runTestArray "osx" "x64_llvm" "run")
		fi
		(PATH=$PATH; runTestArray "osx" "x32_llvm" "run")

		PATH_GCC47=/opt/local/bin
		
		if [ -x /opt/local/bin/g++-mp-4.7 ]
		then
			if [ "$MACHINE" == "x86_64" ]
			then
				(PATH=$PATH_GCC47:$PATH; runTestArray "osx" "x64_gcc47" "run")
			fi
			(PATH=$PATH_GCC47:$PATH; runTestArray "osx" "x32_gcc47" "run")
		fi
		
		PATH_GCC46=/opt/local/bin
		
		if [ -x /opt/local/bin/g++-mp-4.6 ]
		then
			if [ "$MACHINE" == "x86_64" ]
			then
				(PATH=$PATH_GCC46:$PATH; runTestArray "osx" "x64_gcc46" "run")
			fi
			(PATH=$PATH_GCC46:$PATH; runTestArray "osx" "x32_gcc46" "run")
		fi
	)

fi

echo
echo "XCDL runTests: completed, results in $DEST"
echo
echo "PWD=`pwd`"

if [ "$MACHINE" == "x86_64" ]
then
	echo "64 bit versions included"
else
	echo "32 bit versions only"
fi

if [ -x /opt/local/bin/g++-mp-4.7 ]
then
	echo "g++-mp-4.7 included"
fi

if [ -x /opt/local/bin/g++-mp-4.6 ]
then
	echo "g++-mp-4.6 included"
fi

