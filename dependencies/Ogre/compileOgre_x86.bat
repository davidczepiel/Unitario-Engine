rem copia las dlls implicitas a bin
xcopy ..\..\dependencies\Ogre\Build32\bin\debug\OgreMain_d.dll ..\..\bin\ /y
xcopy ..\..\dependencies\Ogre\Build32\bin\release\OgreMain.dll ..\..\bin\ /y
xcopy ..\..\dependencies\Ogre\Build32\bin\release\zlib.dll ..\..\bin\ /y

rem copia las dlls explicitas de los plugins a bin\Ogre[Debug/Release]
xcopy ..\..\dependencies\Ogre\Build32\bin\debug\Codec_STBI_d.dll ..\..\bin\OgreDEBUG\ /y
xcopy ..\..\dependencies\Ogre\Build32\bin\debug\RenderSystem_Direct3d11_d.dll ..\..\bin\OgreDEBUG\ /y
xcopy ..\..\dependencies\Ogre\Build32\bin\release\Codec_STBI.dll ..\..\bin\OgreRELEASE\ /y
xcopy ..\..\dependencies\Ogre\Build32\bin\release\RenderSystem_Direct3d11.dll ..\..\bin\OgreRELEASE\ /y

exit 0