rem copia las dlls implicitas a bin
xcopy ..\..\dependencies\fmod 2.01.08\Buildx86\fmod.dll ..\..\bin\ /y
xcopy ..\..\dependencies\fmod 2.01.08\Buildx86\fmod_vc.lib ..\..\bin\ /y
xcopy ..\..\dependencies\fmod 2.01.08\Buildx86\fmodL.dll ..\..\bin\ /y
xcopy ..\..\dependencies\fmod 2.01.08\Buildx86\fmodL_vc.lib ..\..\bin\ /y

exit 0