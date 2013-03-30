#! /bin/bash

XCDLBUILD="xcdl-python.git/scripts/xcdlBuild.sh"
REPO="micro-os-plus-se.git/packages"
UNAME=`uname`

DEST=build

# Check for custom destination folder
if [ $# -gt 0 ]
then
  DEST=$1
fi

echo "XCDL runTests: started"

if [ $UNAME == "Linux" ]
then

(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_trace_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_trace_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_trace_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_trace_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ios_base_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ios_base_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ios_base_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ios_base_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_fpos_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_fpos_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_fpos_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_fpos_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_basic_ios_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_basic_ios_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_basic_ios_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_basic_ios_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ostream_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ostream_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ostream_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ostream_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ostreamconv_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ostreamconv_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ostreamconv_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_ostreamconv_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_streambuf_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_streambuf_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_streambuf_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_dir="$DEST" --build_config=linux_streambuf_x32_gcc_Release run) && \
\
false

elif [ $UNAME == "Darwin" ]
then

PATH_GCC46=/opt/local/bin
PATH_GCC47=/opt/local/bin

(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x64_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x64_llvm_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x32_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x32_llvm_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x64_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x64_gcc47_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x32_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x32_gcc47_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x64_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x64_gcc46_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x32_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_trace_x32_gcc46_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x64_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x64_llvm_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x32_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x32_llvm_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x64_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x64_gcc47_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x32_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x32_gcc47_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x64_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x64_gcc46_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x32_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_fpos_x32_gcc46_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x64_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x64_llvm_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x32_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x32_llvm_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x64_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x64_gcc47_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x32_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x32_gcc47_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x64_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x64_gcc46_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x32_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ios_base_x32_gcc46_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x64_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x64_llvm_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x32_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x32_llvm_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x64_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x64_gcc47_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x32_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x32_gcc47_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x64_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x64_gcc46_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x32_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_basic_ios_x32_gcc46_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x64_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x64_llvm_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x32_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x32_llvm_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x64_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x64_gcc47_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x32_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x32_gcc47_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x64_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x64_gcc46_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x32_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_streambuf_x32_gcc46_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x64_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x64_llvm_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x32_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x32_llvm_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x64_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x64_gcc47_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x32_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x32_gcc47_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x64_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x64_gcc46_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x32_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostream_x32_gcc46_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x64_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x64_llvm_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x32_llvm_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x32_llvm_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x64_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x64_gcc47_Release run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x32_gcc47_Debug run) && \
(PATH=$PATH_GCC47:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x32_gcc47_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x64_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x64_gcc46_Release run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x32_gcc46_Debug run) && \
(PATH=$PATH_GCC46:$PATH; /bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=osx_ostreamconv_x32_gcc46_Release run) && \
\
false

fi

echo
echo "XCDL runTests: completed, results in $DEST"
echo "PWD=`pwd`"
