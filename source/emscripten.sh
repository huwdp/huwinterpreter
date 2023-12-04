rm -rf wasm-build
mkdir wasm-build
cd wasm-build
emcmake cmake ..
cmake --build . --target HuwInterpreter

