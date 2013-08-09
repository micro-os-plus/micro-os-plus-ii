#! /bin/bash

# run arguments: generate jUnit XML files
MAKE_ARGS=-Wr,-x,junit.xml

XCDLBUILD="xcdl-python.git/scripts/xcdlBuild.sh"
REPO="micro-os-plus-se.git/packages"
UNAME=`uname`

FULL=""
DEST=build

declare -a testNamesDefault=( 'trace' )
testNamesDefault=("${testNamesDefault[@]}" 'fpos' 'ios_base' 'basic_ios' 'streambuf' 'ostream' 'ostreamconv' )
testNamesDefault=("${testNamesDefault[@]}" 'minimal' )
testNamesDefault=("${testNamesDefault[@]}" 'threads' 'yields' 'sleep' 'mutex' )

# empty array
declare -a testNames=(  )

while [ $# -gt 0 ]
do
	#echo $1
	if [ $1 == "--full" ]
	then
		#echo "Full"
		FULL="Y"
	elif [ $1 == "--dest" -a $# -gt 1 ]
	then
		#echo "Dest" $2
		DEST=$2
		shift
	elif [ ${1:0:2} == "--" ]
	then
		echo "unsupported option" $1
	else
		#
		testNames=("${testNames[@]}" $1)
	fi
	shift
done

if [ ${#testNames[@]} -eq 0 ]
then
  testNames=("${testNamesDefault[@]}")
fi

echo "Running ( ${testNames[@]} )"
echo

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
	
	echo
	echo /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=$1 $MAKE_ARGS $action
	/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=$1 $MAKE_ARGS $action
	[ $? -eq 0 ] || exit $?
}

function runTestPair()
{
	[ $# -ge 1 ] || exit 1

	(runTest $1"_Debug" $2) || exit $?
	(runTest $1"_Release" $2) || exit $?
}

function runTestArray()
{
	[ $# -ge 3 ] || exit 1

	platform=$1
	bits=$2
	compiler=$3
	action=$4
	for bc in "${testNames[@]}"
	do
		(runTestPair $platform"_"$bc"_"$bits"_"$compiler $action) || exit $?
	done
	
	echo "$compiler $bits tests performed" >>$SUMMARY_FILE
}

# make sure the destination folder is there
mkdir -p $DEST

SUMMARY_FILE=$DEST/summary.txt
rm -f $SUMMARY_FILE
touch -f $SUMMARY_FILE

echo "XCDL runTests: started"

if [ $UNAME == "Linux" ]
then

	time (
	
		if [ ! -z "$(g++ --version | grep 4.7)" ]
		then
			defaultCompiler=gcc47
		elif [ ! -z "$(g++ --version | grep 4.8)" ]
		then
			defaultCompiler=gcc48
		else
			defaultCompiler=gcc
		fi
		echo "Default compiler: $defaultCompiler" >>$SUMMARY_FILE
		
		if [ -z "$FULL" ]
		then
			# quick tests, use only default g++

			compiler=$defaultCompiler			

			# decide on 64/32 bits			
			if [ "$MACHINE" == "x86_64" ]
			then
				echo "$UNAME $MACHINE, quick tests" >>$SUMMARY_FILE
				(PATH=$PATH; runTestArray "linux" "x64" "$compiler" "run") || exit $?
			else
				echo "$UNAME $MACHINE, quick tests" >>$SUMMARY_FILE
				(PATH=$PATH; runTestArray "linux" "x32" "$compiler" "run") || exit $?
			fi
			
		else

			if [ "$MACHINE" == "x86_64" ]
			then
				echo "$UNAME $MACHINE, full tests" >>$SUMMARY_FILE
			else
				echo "$UNAME $MACHINE, full tests" >>$SUMMARY_FILE
			fi
			
			# full tests, try to use all possible compilers
			
			if [ -x /usr/bin/clang++ ]
			then
				compiler=llvm			
				if [ "$MACHINE" == "x86_64" ]
				then
					(PATH=$PATH; runTestArray "linux" "x64" "$compiler" "run") || exit $?
				fi
				(PATH=$PATH; runTestArray "linux" "x32" "$compiler" "run") || exit $?
			fi
			
			if [ -x /usr/bin/g++-4.8 -o "$defaultCompiler" == "gcc48" ]
			then
				if [ -x /usr/bin/g++-4.8 ]
				then
					compiler=gcc48
				else
					compiler=gcc
				fi		
				if [ "$MACHINE" == "x86_64" ]
				then
					(PATH=$PATH; runTestArray "linux" "x64" "$compiler" "run") || exit $?
				fi
				(PATH=$PATH; runTestArray "linux" "x32" "$compiler" "run") || exit $?
			fi
			
			if [ -x /usr/bin/g++-4.7 -o "$defaultCompiler" == "gcc47" ]
			then
				if [ -x /usr/bin/g++-4.7 ]
				then
					compiler=gcc47
				else
					compiler=gcc
				fi		
				if [ "$MACHINE" == "x86_64" ]
				then
					(PATH=$PATH; runTestArray "linux" "x64" "$compiler" "run") || exit $?
				fi
				(PATH=$PATH; runTestArray "linux" "x32" "$compiler" "run") || exit $?
			fi
			
		fi
	) || exit $?

elif [ $UNAME == "Darwin" ]
then
	
	time ( 
		
		if [ -z "$FULL" ]
		then
		
			# clang is always available on OS X
			# decide only on 64/32 bits			
			if [ "$MACHINE" == "x86_64" ]
			then
				echo "$UNAME $MACHINE, quick tests" >>$SUMMARY_FILE
				(PATH=$PATH; runTestArray "osx" "x64" "llvm" "run") || exit $?
			else
				echo "$UNAME $MACHINE, quick tests" >>$SUMMARY_FILE
				(PATH=$PATH; runTestArray "osx" "x32" "llvm" "run") || exit $?
			fi
		
		else

			if [ "$MACHINE" == "x86_64" ]
			then
				echo "$UNAME $MACHINE, full tests" >>$SUMMARY_FILE
			else
				echo "$UNAME $MACHINE, full tests" >>$SUMMARY_FILE
			fi

			# full tests, try to use all possible compilers
		
			# clang is always available on OS X
			if [ "$MACHINE" == "x86_64" ]
			then
				(PATH=$PATH; runTestArray "osx" "x64" "llvm" "run") || exit $?
			fi
			(PATH=$PATH; runTestArray "osx" "x32" "llvm" "run") || exit $?
	
			PATH_GCC48=/opt/local/bin			
			if [ -x /opt/local/bin/g++-mp-4.8 ]
			then
				if [ "$MACHINE" == "x86_64" ]
				then
					(PATH=$PATH_GCC48:$PATH; runTestArray "osx" "x64" "gcc48" "run") || exit $?
				fi
				(PATH=$PATH_GCC48:$PATH; runTestArray "osx" "x32" "gcc48" "run") || exit $?
			fi

			PATH_GCC47=/opt/local/bin			
			if [ -x /opt/local/bin/g++-mp-4.7 ]
			then
				if [ "$MACHINE" == "x86_64" ]
				then
					(PATH=$PATH_GCC47:$PATH; runTestArray "osx" "x64" "gcc47" "run") || exit $?
				fi
				(PATH=$PATH_GCC47:$PATH; runTestArray "osx" "x32" "gcc47" "run") || exit $?
			fi
			
		fi
	) || exit $?

fi

echo
echo "XCDL runTests: completed ( ${testNames[@]} )"
echo "Results in $DEST"
echo
echo "PWD=`pwd`"
echo
cat $SUMMARY_FILE
echo
