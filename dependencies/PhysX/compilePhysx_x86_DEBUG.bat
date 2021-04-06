rem copia las dlls en caso de que sean nuevas -noexistan- o se hayan modificado. Version inicial 2.01.08
rem DEBUGx86
xcopy ..\..\dependencies\PhysX\Buildx86\debug\glut32.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx86\debug\PhysX_32.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx86\debug\PhysXCommon_32.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx86\debug\PhysXCooking_32.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx86\debug\PhysXDevice.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx86\debug\PhysXFoundation_32.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx86\debug\PhysXGpu_32.dll ..\..\bin\ /s /d /y
exit 0