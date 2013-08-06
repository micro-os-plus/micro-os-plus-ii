
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

echo 'Building configuration files from template...'
echo


CONFIG=/portable/diagnostics/tests/meta/trace-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/trace/' \
-e 's/ARTEFACTDESCRIPTION/Trace/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/diagnostics/tests/meta/trace-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/trace/' \
-e 's/ARTEFACTDESCRIPTION/Trace/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/tests/meta/minimal-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.tests/' \
-e 's/ARTEFACTNAME/minimal/' \
-e 's/ARTEFACTDESCRIPTION/Minimal/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/tests/meta/minimal-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.tests/' \
-e 's/ARTEFACTNAME/minimal/' \
-e 's/ARTEFACTDESCRIPTION/Minimal/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/core/tests/meta/threads-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/threads/' \
-e 's/ARTEFACTDESCRIPTION/Threads/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/threads-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/threads/' \
-e 's/ARTEFACTDESCRIPTION/Threads/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/core/tests/meta/yields-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/yields/' \
-e 's/ARTEFACTDESCRIPTION/Yields/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/yields-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/yields/' \
-e 's/ARTEFACTDESCRIPTION/Yields/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/core/tests/meta/sleep-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/sleep/' \
-e 's/ARTEFACTDESCRIPTION/Sleep/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/sleep-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/sleep/' \
-e 's/ARTEFACTDESCRIPTION/Sleep/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/core/tests/meta/sleepstress-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/sleepstress/' \
-e 's/ARTEFACTDESCRIPTION/Sleep Stress/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/sleepstress-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/sleepstress/' \
-e 's/ARTEFACTDESCRIPTION/Sleep Stress/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/core/tests/meta/mutexstress-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/mutexstress/' \
-e 's/ARTEFACTDESCRIPTION/Mutex Stress/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/mutexstress-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/mutexstress/' \
-e 's/ARTEFACTDESCRIPTION/Mutex Stress/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/language/cpp/tests/meta/basic_ios-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/basic_ios/' \
-e 's/ARTEFACTDESCRIPTION/C++ basic_ios/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/language/cpp/tests/meta/basic_ios-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/basic_ios/' \
-e 's/ARTEFACTDESCRIPTION/C++ basic_ios/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/language/cpp/tests/meta/fpos-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/fpos/' \
-e 's/ARTEFACTDESCRIPTION/C++ fpos/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/language/cpp/tests/meta/fpos-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/fpos/' \
-e 's/ARTEFACTDESCRIPTION/C++ fpos/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/language/cpp/tests/meta/ios_base-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ios_base/' \
-e 's/ARTEFACTDESCRIPTION/C++ ios_base/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/language/cpp/tests/meta/ios_base-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ios_base/' \
-e 's/ARTEFACTDESCRIPTION/C++ ios_base/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/language/cpp/tests/meta/ostream-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostream/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/language/cpp/tests/meta/ostream-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostream/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/language/cpp/tests/meta/ostreamConversions-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostreamconv/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream conversions/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/language/cpp/tests/meta/ostreamConversions-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostreamconv/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream conversions/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/language/cpp/tests/meta/streambuf-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/streambuf/' \
-e 's/ARTEFACTDESCRIPTION/C++ streambuf/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/language/cpp/tests/meta/streambuf-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/streambuf/' \
-e 's/ARTEFACTDESCRIPTION/C++ streambuf/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/language/cpp/tests/meta/string-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/string/' \
-e 's/ARTEFACTDESCRIPTION/C++ string/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/language/cpp/tests/meta/string-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/string/' \
-e 's/ARTEFACTDESCRIPTION/C++ string/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


CONFIG=/portable/language/cpp/tests/meta/exception-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/exception/' \
-e 's/ARTEFACTDESCRIPTION/C++ exception/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/language/cpp/tests/meta/exception-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/exception/' \
-e 's/ARTEFACTDESCRIPTION/C++ exception/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

echo
echo '[done]'