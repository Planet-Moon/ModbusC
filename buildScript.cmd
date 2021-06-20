mkdir build
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="E:/Users/Andreas/Andreas/Private Elektronik/Cpp/vcpkg/scripts/buildsystems/vcpkg.cmake"
cd build
make
