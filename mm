# mm - CMake shortcut command for Mac

SOURCE_DIR=$(printf "%q" "$PWD") # escapes the dir with backslashes

export STEAMWORKS_ROOT="dependencies/steamworks"

mkdir -p build/debug

cd build/debug

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$SOURCE_DIR  -DCMAKE_INSTALL_PREFIX=./ -G "Unix Makefiles" ../..

make
make install

cd ../..

cp -r build/release/lib ./
cp -r build/release/include ./