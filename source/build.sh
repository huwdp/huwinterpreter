rm -rf build
mkdir build
cd build
cmake -lcurl -lreadline ..
make
