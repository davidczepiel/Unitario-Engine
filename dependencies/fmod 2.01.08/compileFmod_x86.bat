rem copia las dlls y libs en caso de que sean nuevas -noexistan- o se hayan modificado
xcopy ..\..\dependencies\fmod 2.01.08\Buildx86\fmod.dll ..\..\bin\ /s /d
xcopy ..\..\dependencies\fmod 2.01.08\Buildx86\fmod_vc.lib ..\..\bin\ /s /d
xcopy ..\..\dependencies\fmod 2.01.08\Buildx86\fmodL.dll ..\..\bin\ /s /d
xcopy ..\..\dependencies\fmod 2.01.08\Buildx86\fmodL_vc.lib ..\..\bin\ /s /d

exit 0