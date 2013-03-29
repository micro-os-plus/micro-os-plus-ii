#! /bin/bash

XCDLBUILD="xcdl-python.git/scripts/xcdlBuild.sh"
REPO="micro-os-plus-second.git/packages"


echo "XCDL runTests: started"

(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_config=linux_trace_x64_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_config=linux_trace_x64_gcc_Release run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_config=linux_trace_x32_gcc_Debug run) && \
(/bin/bash "$XCDLBUILD" --repository="$REPO" --build_config=linux_trace_x32_gcc_Release run) && \
\
false

echo
echo "XCDL runTests: completed"
echo "PWD=`pwd`"
