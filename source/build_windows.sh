#

rm -rf build
mkdir build
cd build
i686-w64-mingw32.static-cmake -lcurl -lreadline ..
make
