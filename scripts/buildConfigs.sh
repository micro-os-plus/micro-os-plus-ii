
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

# ----- trace -----------------------------------------------------------------
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

CONFIG=/portable/diagnostics/tests/meta/trace-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/trace/' \
-e 's/ARTEFACTDESCRIPTION/Trace/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- minimal ---------------------------------------------------------------
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

CONFIG=/portable/tests/meta/minimal-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.tests/' \
-e 's/ARTEFACTNAME/minimal/' \
-e 's/ARTEFACTDESCRIPTION/Minimal/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/tests/meta/minimal-stm32h103-config.py
sed -e 's/IDPREFIX/config.os.portable.tests/' \
-e 's/ARTEFACTNAME/minimal/' \
-e 's/ARTEFACTDESCRIPTION/Minimal/' \
stm32h103-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- threads ---------------------------------------------------------------
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

CONFIG=/portable/core/tests/meta/threads-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/threads/' \
-e 's/ARTEFACTDESCRIPTION/Threads/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/threads-stm32h103-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/threads/' \
-e 's/ARTEFACTDESCRIPTION/Threads/' \
stm32h103-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- yields ----------------------------------------------------------------
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

CONFIG=/portable/core/tests/meta/yields-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/yields/' \
-e 's/ARTEFACTDESCRIPTION/Yields/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/yields-stm32h103-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/yields/' \
-e 's/ARTEFACTDESCRIPTION/Yields/' \
stm32h103-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- sleep -----------------------------------------------------------------
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

CONFIG=/portable/core/tests/meta/sleep-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/sleep/' \
-e 's/ARTEFACTDESCRIPTION/Sleep/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/sleep-stm32h103-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/sleep/' \
-e 's/ARTEFACTDESCRIPTION/Sleep/' \
stm32h103-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- sleepstress -----------------------------------------------------------
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

CONFIG=/portable/core/tests/meta/sleepstress-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/sleepstress/' \
-e 's/ARTEFACTDESCRIPTION/Sleep Stress/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/sleepstress-stm32h103-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/sleepstress/' \
-e 's/ARTEFACTDESCRIPTION/Sleep Stress/' \
stm32h103-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- mutex -----------------------------------------------------------------
CONFIG=/portable/core/tests/meta/mutex-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/mutex/' \
-e 's/ARTEFACTDESCRIPTION/Mutex/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/mutex-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/mutex/' \
-e 's/ARTEFACTDESCRIPTION/Mutex/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/mutex-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/mutex/' \
-e 's/ARTEFACTDESCRIPTION/Mutex/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/mutex-stm32h103-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/mutex/' \
-e 's/ARTEFACTDESCRIPTION/Mutex/' \
stm32h103-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- mutexstress -----------------------------------------------------------
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

CONFIG=/portable/core/tests/meta/mutexstress-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/mutexstress/' \
-e 's/ARTEFACTDESCRIPTION/Mutex Stress/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/core/tests/meta/mutexstress-stm32h103-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/mutexstress/' \
-e 's/ARTEFACTDESCRIPTION/Mutex Stress/' \
stm32h103-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- basic_ios -------------------------------------------------------------
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

CONFIG=/portable/language/cpp/tests/meta/basic_ios-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/basic_ios/' \
-e 's/ARTEFACTDESCRIPTION/C++ basic_ios/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- fpos ------------------------------------------------------------------
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

CONFIG=/portable/language/cpp/tests/meta/fpos-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/fpos/' \
-e 's/ARTEFACTDESCRIPTION/C++ fpos/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- ios_base --------------------------------------------------------------
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

CONFIG=/portable/language/cpp/tests/meta/ios_base-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ios_base/' \
-e 's/ARTEFACTDESCRIPTION/C++ ios_base/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- ostream ---------------------------------------------------------------
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

CONFIG=/portable/language/cpp/tests/meta/ostream-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostream/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- ostreamConversions ----------------------------------------------------
CONFIG=/portable/language/cpp/tests/meta/ostreamconv-linux-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostreamconv/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream conversions/' \
linux-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/language/cpp/tests/meta/ostreamconv-osx-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostreamconv/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream conversions/' \
osx-config-template.py >$DEST/$CONFIG
echo $CONFIG generated

CONFIG=/portable/language/cpp/tests/meta/ostreamconv-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/ostreamconv/' \
-e 's/ARTEFACTDESCRIPTION/C++ ostream conversions/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- streambuf -------------------------------------------------------------
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

CONFIG=/portable/language/cpp/tests/meta/streambuf-qemu-config.py
sed -e 's/IDPREFIX/config.os.portable.core.tests/' \
-e 's/ARTEFACTNAME/streambuf/' \
-e 's/ARTEFACTDESCRIPTION/C++ streambuf/' \
qemu-config-template.py >$DEST/$CONFIG
echo $CONFIG generated


# ----- string ----------------------------------------------------------------
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


# ----- exceptions ------------------------------------------------------------
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


# -----------------------------------------------------------------------------
echo
echo '[done]'