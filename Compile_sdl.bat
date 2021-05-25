rem -------------------------------SDL2---------------------------------------
cd dependencies\SDL2

mkdir Build

cd ..\CMake\bin

cmake -S "..\..\SDL2\Src" -B "..\..\SDL2\Build"

cd ..\..\SDL2\Build
msbuild "SDL2.sln" /p:configuration=Debug
msbuild "SDL2.sln" /p:configuration=Release
