rem copia las dlls en caso de que sean nuevas -noexistan- o se hayan modificado. Version inicial 2.01.08
rem DEBUGx64
xcopy ..\..\dependencies\PhysX\Buildx64\debug\glut32.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\debug\PhysX_64.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\debug\PhysXCommon_64.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\debug\PhysXCooking_64.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\debug\PhysXDevice64.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\debug\PhysXFoundation_64.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\debug\PhysXGpu_64.dll ..\..\bin\ /s /d /y
rem RELEASEx64
xcopy ..\..\dependencies\PhysX\Buildx64\release\glut32.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\release\PhysX_64.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\release\PhysXCommon_64.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\release\PhysXCooking_64.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\release\PhysXDevice64.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\release\PhysXFoundation_64.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\PhysX\Buildx64\release\PhysXGpu_64.dll ..\..\bin\ /s /d /y
exit 0