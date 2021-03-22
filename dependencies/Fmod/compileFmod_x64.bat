rem copia las dlls en caso de que sean nuevas -noexistan- o se hayan modificado. Version inicial 2.01.08
xcopy ..\..\dependencies\Fmod\Buildx64\fmod.dll ..\..\bin\ /s /d
xcopy ..\..\dependencies\Fmod\Buildx64\fmodL.dll ..\..\bin\ /s /d

exit 0