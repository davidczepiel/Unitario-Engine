rem copia las dlls implicitas a bin
xcopy ..\..\dependencies\fmod 2.01.08\Buildx64\fmod.dll ..\..\bin\ /y
xcopy ..\..\dependencies\fmod 2.01.08\Buildx64\fmod_vc.lib ..\..\bin\ /y
xcopy ..\..\dependencies\fmod 2.01.08\Buildx64\fmodL.dll ..\..\bin\ /y
xcopy ..\..\dependencies\fmod 2.01.08\Buildx64\fmodL_vc.lib ..\..\bin\ /y

exit 0