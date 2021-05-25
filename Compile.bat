rem --------------------------------------------------------------------------
rem --------------------------------------------------------------------------
rem -------------------------------OGRE---------------------------------------
rem --------------------------------------------------------------------------
rem --------------------------------------------------------------------------

cd dependencies\Ogre
rem Creacion de carpetas
mkdir Build
mkdir Build32
mkdir OgreSolution

cd ..\CMake\bin
rem Se crea la solucion de ogre usando cmake
echo Creating Ogre solution from source code...
cmake -D OGRE_BUILD_RENDERSYSTEM_D3D9=FALSE -D OGRE_BUILD_RENDERSYSTEM_GL3PLUS=FALSE -D OGRE_BUILD_RENDERSYSTEM_GL=FALSE -D OGRE_BUILD_RENDERSYSTEM_GLES2=FALSE -D OGRE_BUILD_PLUGIN_ASSIMP=FALSE -D OGRE_BUILD_PLUGIN_BSP=FALSE -D OGRE_BUILD_PLUGIN_OCTREE=FALSE -D OGRE_BUILD_PLUGIN_DOT_SCENE=FALSE -D OGRE_BUILD_PLUGIN_PCZ=FALSE -D OGRE_BUILD_COMPONENT_TERRAIN=FALSE -D OGRE_BUILD_COMPONENT_VOLUME=FALSE -D OGRE_BUILD_COMPONENT_BITES=FALSE -D OGRE_BUILD_COMPONENT_PYTHON=FALSE -D OGRE_BUILD_COMPONENT_JAVA=FALSE -D OGRE_BUILD_COMPONENT_CSHARP=FALSE -D OGRE_INSTALL_CMAKE=FALSE -D OGRE_INSTALL_SAMPLES=FALSE -D OGRE_INSTALL_DOCS=FALSE -D OGRE_INSTALL_PDB=FALSE -D OGRE_BUILD_TOOLS=FALSE -S "..\..\Ogre\Src" -B "..\..\Ogre\OgreSolution"
echo Ogre solution created

cd ..\..\Ogre\OgreSolution
rem Se compila Ogre para Debug y Release
echo Compiling Ogre for debug and release...
msbuild "OGRE.sln" /p:configuration=Debug
msbuild "OGRE.sln" /p:configuration=Release

rem Se copia el resultado de la build al proyecto
echo Coping build to project...
mkdir .\bin ..\Build\bin
mkdir .\bin ..\Build\lib
mkdir .\bin ..\Build\include
XCOPY /y /s .\bin ..\Build\bin\
XCOPY /y /s .\lib ..\Build\lib\
XCOPY /y /s .\include ..\Build\include

cd ..
rmdir /s /q OgreSolution

rem --------------------------------------------------------------------------
rem --------------------------------------------------------------------------
rem -------------------------------SDL2---------------------------------------
rem --------------------------------------------------------------------------
rem --------------------------------------------------------------------------

cd ..\SDL2

mkdir Build

cd ..\CMake\bin

cmake -S "..\..\SDL2\Src" -B "..\..\SDL2\Build"

cd ..\..\SDL2\Build
msbuild "SDL2.sln" /p:configuration=Debug
msbuild "SDL2.sln" /p:configuration=Release