rem copia las dlls en caso de que sean nuevas -noexistan- o se hayan modificado. Version inicial 2.01.08
xcopy ..\Motor\dependencies\SDL2\Buildx64\SDL2.dll ..\bin\ /s /d /y
exit 0