rem compilamos ogre
cd dependencies\Ogre
mkdir build
mkdir build32
mkdir OgreSolution
cd ..\CMake\bin
cmake.exe  -S "..\..\Ogre\Src" -B "..\..\Ogre\OgreSolution" -U "OGRE_BUILD_COMPONENT_BITES"
rem call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\Common7\Tools\VsMSBuildCmd.bat"
rem msbuild OGRE.sln/t:Codec_Assimp