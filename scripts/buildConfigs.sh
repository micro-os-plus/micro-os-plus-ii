
# Get absolute path of shell script. Supports:
# source ./script (When called by the . dot operator)
# Absolute path /path/to/script
# Relative path like ./script
# /path/dir1/../dir2/dir3/../script
# When called from symlink
# When symlink is nested eg) foo->dir1/dir2/bar bar->./../doe doe->script
# When caller changes the scripts name

DEST=../packages

pushd . > /dev/null
SCRIPT_PATH="${BASH_SOURCE[0]}";
  while([ -h "${SCRIPT_PATH}" ]) do 
    cd "`dirname "${SCRIPT_PATH}"`"
    SCRIPT_PATH="$(readlink "`basename "${SCRIPT_PATH}"`")"; 
  done
cd "`dirname "${SCRIPT_PATH}"`" > /dev/null
SCRIPT_PATH="`pwd`";
popd  > /dev/null
#echo "script=[${SCRIPT_PATH}]"
#echo "pwd   =[`pwd`]"

cd "$SCRIPT_PATH"


sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/trace/' \
-e 's/ARTEFACTDESCRIPTION/Trace/' \
-e 's/OSNAME/linux/' \
-e 's/OSDESCRIPTION/GNU\/Linux/' \
linux-config-template.py >$DEST/portable/diagnostics/tests/meta/trace-linux-config.py

sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/trace/' \
-e 's/ARTEFACTDESCRIPTION/Trace/' \
-e 's/OSNAME/osx/' \
-e 's/OSDESCRIPTION/OS X/' \
osx-config-template.py >$DEST/portable/diagnostics/tests/meta/trace-osx-config.py

sed -e 's/IDPREFIX/config.os.portable.tests/' \
-e 's/ARTEFACTNAME/minimal/' \
-e 's/ARTEFACTDESCRIPTION/Minimal/' \
-e 's/OSNAME/linux/' \
-e 's/OSDESCRIPTION/GNU\/Linux/' \
linux-config-template.py >$DEST/portable/tests/meta/minimal-linux-config.py

sed -e 's/IDPREFIX/config.os.portable.tests/' \
-e 's/ARTEFACTNAME/minimal/' \
-e 's/ARTEFACTDESCRIPTION/Minimal/' \
-e 's/OSNAME/osx/' \
-e 's/OSDESCRIPTION/OS X/' \
osx-config-template.py >$DEST/portable/tests/meta/minimal-osx-config.py


sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/threads/' \
-e 's/ARTEFACTDESCRIPTION/Threads/' \
-e 's/OSNAME/linux/' \
-e 's/OSDESCRIPTION/GNU\/Linux/' \
linux-config-template.py >$DEST/portable/core/tests/meta/threads-linux-config.py

sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/threads/' \
-e 's/ARTEFACTDESCRIPTION/Threads/' \
-e 's/OSNAME/osx/' \
-e 's/OSDESCRIPTION/OS X/' \
osx-config-template.py >$DEST/portable/core/tests/meta/threads-osx-config.py


sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/yields/' \
-e 's/ARTEFACTDESCRIPTION/Yields/' \
-e 's/OSNAME/linux/' \
-e 's/OSDESCRIPTION/GNU\/Linux/' \
linux-config-template.py >$DEST/portable/core/tests/meta/yields-linux-config.py

sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/yields/' \
-e 's/ARTEFACTDESCRIPTION/Yields/' \
-e 's/OSNAME/osx/' \
-e 's/OSDESCRIPTION/OS X/' \
osx-config-template.py >$DEST/portable/core/tests/meta/yields-osx-config.py


sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/basic_ios/' \
-e 's/ARTEFACTDESCRIPTION/C++ basic_ios/' \
-e 's/OSNAME/linux/' \
-e 's/OSDESCRIPTION/GNU\/Linux/' \
linux-config-template.py >$DEST/portable/language/cpp/tests/meta/basic_ios-linux-config.py

sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/basic_ios/' \
-e 's/ARTEFACTDESCRIPTION/C++ basic_ios/' \
-e 's/OSNAME/osx/' \
-e 's/OSDESCRIPTION/OS X/' \
osx-config-template.py >$DEST/portable/language/cpp/tests/meta/basic_ios-osx-config.py


sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/fpos/' \
-e 's/ARTEFACTDESCRIPTION/C++ fpos/' \
-e 's/OSNAME/linux/' \
-e 's/OSDESCRIPTION/GNU\/Linux/' \
linux-config-template.py >$DEST/portable/language/cpp/tests/meta/fpos-linux-config.py

sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/fpos/' \
-e 's/ARTEFACTDESCRIPTION/C++ fpos/' \
-e 's/OSNAME/osx/' \
-e 's/OSDESCRIPTION/OS X/' \
osx-config-template.py >$DEST/portable/language/cpp/tests/meta/fpos-osx-config.py


sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ios_base/' \
-e 's/ARTEFACTDESCRIPTION/C++ ios_base/' \
-e 's/OSNAME/linux/' \
-e 's/OSDESCRIPTION/GNU\/Linux/' \
linux-config-template.py >$DEST/portable/language/cpp/tests/meta/ios_base-linux-config.py

sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ios_base/' \
-e 's/ARTEFACTDESCRIPTION/C++ ios_base/' \
-e 's/OSNAME/osx/' \
-e 's/OSDESCRIPTION/OS X/' \
osx-config-template.py >$DEST/portable/language/cpp/tests/meta/ios_base-osx-config.py


sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostream/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream/' \
-e 's/OSNAME/linux/' \
-e 's/OSDESCRIPTION/GNU\/Linux/' \
linux-config-template.py >$DEST/portable/language/cpp/tests/meta/ostream-linux-config.py

sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostream/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream/' \
-e 's/OSNAME/osx/' \
-e 's/OSDESCRIPTION/OS X/' \
osx-config-template.py >$DEST/portable/language/cpp/tests/meta/ostream-osx-config.py


sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostreamconv/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream conversions/' \
-e 's/OSNAME/linux/' \
-e 's/OSDESCRIPTION/GNU\/Linux/' \
linux-config-template.py >$DEST/portable/language/cpp/tests/meta/ostreamConversions-linux-config.py

sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostreamconv/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream conversions/' \
-e 's/OSNAME/osx/' \
-e 's/OSDESCRIPTION/OS X/' \
osx-config-template.py >$DEST/portable/language/cpp/tests/meta/ostreamConversions-osx-config.py


sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/streambuf/' \
-e 's/ARTEFACTDESCRIPTION/C++ streambuf/' \
-e 's/OSNAME/linux/' \
-e 's/OSDESCRIPTION/GNU\/Linux/' \
linux-config-template.py >$DEST/portable/language/cpp/tests/meta/streambuf-linux-config.py

sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/streambuf/' \
-e 's/ARTEFACTDESCRIPTION/C++ streambuf/' \
-e 's/OSNAME/osx/' \
-e 's/OSDESCRIPTION/OS X/' \
osx-config-template.py >$DEST/portable/language/cpp/tests/meta/streambuf-osx-config.py
