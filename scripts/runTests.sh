#! /bin/bash

XCDLBUILD="xcdl-python.git/scripts/xcdlBuild.sh"
REPO="micro-os-plus-second.git/packages"
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

(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_trace_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_trace_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_trace_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_trace_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ios_base_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ios_base_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ios_base_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ios_base_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_fpos_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_fpos_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_fpos_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_fpos_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_basic_ios_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_basic_ios_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_basic_ios_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_basic_ios_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ostream_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ostream_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ostream_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ostream_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ostreamconv_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ostreamconv_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ostreamconv_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_ostreamconv_x32_gcc_Release run) && \
\
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_streambuf_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_streambuf_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_streambuf_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_dir="$DEST" --build_config=linux_streambuf_x32_gcc_Release run) && \
\
false

fi

echo
echo "XCDL runTests: completed, results in $DEST"
echo "PWD=`pwd`"
