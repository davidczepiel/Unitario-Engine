rem -------------------------------OGRE---------------------------------------
cd dependencies\Ogre
rem Creacion de carpetas
mkdir Build
cd Build
mkdir Debug
mkdir Release
cd ..
mkdir Build32
cd Build32
mkdir Debug
mkdir Release
cd ..
mkdir OgreSolution

cd ..\CMake\bin
rem Se crea la solucion de ogre usando cmake
echo Creating Ogre solution from source code...
rem -D OGRE_BUILD_RENDERSYSTEM_D3D9=FALSE -D OGRE_BUILD_RENDERSYSTEM_GL3PLUS=FALSE -D OGRE_BUILD_RENDERSYSTEM_GL=FALSE -D OGRE_BUILD_RENDERSYSTEM_GLES2=FALSE -D OGRE_BUILD_PLUGIN_ASSIMP=FALSE -D OGRE_BUILD_PLUGIN_BSP=FALSE -D OGRE_BUILD_PLUGIN_OCTREE=FALSE -D OGRE_BUILD_PLUGIN_DOT_SCENE=FALSE -D OGRE_BUILD_PLUGIN_PCZ=FALSE -D OGRE_BUILD_COMPONENT_TERRAIN=FALSE -D OGRE_BUILD_COMPONENT_VOLUME=FALSE -D OGRE_BUILD_COMPONENT_BITES=FALSE -D OGRE_BUILD_COMPONENT_PYTHON=FALSE -D OGRE_BUILD_COMPONENT_JAVA=FALSE -D OGRE_BUILD_COMPONENT_CSHARP=FALSE -D OGRE_INSTALL_CMAKE=FALSE -D OGRE_INSTALL_SAMPLES=FALSE -D OGRE_INSTALL_DOCS=FALSE -D OGRE_INSTALL_PDB=FALSE -D OGRE_BUILD_TOOLS=FALSE
cmake -S "..\..\Ogre\Src" -B "..\..\Ogre\OgreSolution"
echo Ogre solution created

cd ..\..\Ogre\OgreSolution
msbuild "OGRE.sln" /p:configuration=Debug
msbuild "OGRE.sln" /p:configuration=Release

XCOPY /y /s .\bin\debug\OgreMain_d.dll ..\..\..\bin
XCOPY /y /s .\bin\release\OgreMain.dll ..\..\..\bin

XCOPY /y /s .\bin\debug\OgreOverlay_d.dll ..\..\..\bin
XCOPY /y /s .\bin\release\OgreOverlay.dll ..\..\..\bin

XCOPY /y /s .\bin\debug\OgreRTShaderSystem_d.dll ..\..\..\bin
XCOPY /y /s .\bin\release\OgreRTShaderSystem.dll ..\..\..\bin

XCOPY /y /s .\bin\debug\Codec_STBI_d.dll ..\..\..\bin
XCOPY /y /s .\bin\release\Codec_STBI.dll ..\..\..\bin

XCOPY /y /s .\bin\debug\RenderSystem_Direct3D11_d.dll ..\..\..\bin
XCOPY /y /s .\bin\release\RenderSystem_Direct3D11.dll ..\..\..\bin

XCOPY /y /s .\bin\debug\RenderSystem_GL_d.dll ..\..\..\bin
XCOPY /y /s .\bin\release\RenderSystem_GL.dll ..\..\..\bin

XCOPY /y /s .\bin\debug\SDL2.dll ..\..\..\bin
XCOPY /y /s .\bin\release\zlib.dll ..\..\..\bin
rem Se compila la solucion
rem msbuild OGRE.sln/t:Codec_Assimp