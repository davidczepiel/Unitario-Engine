rem copia las dlls en caso de que sean nuevas -noexistan- o se hayan modificado. Version inicial 2.01.08
del ..\bin\*.dll /s /f /q
del ..\bin\OgreDEBUG\*.dll /s /f /q
del ..\bin\OgreRELEASE\*.dll /s /f /q

exit 0