cd dependencies\Physx
mkdir PhysxSolution

cd Src\PhysX-4.1\physx
generate_projects.bat
13
generate_projects.bat
12

cd compiler\vc16win64
msbuild "PhysXSDK.sln" \p:configuration=Debug 
msbuild "PhysXSDK.sln" \p:configuration=Release

cd ..\vc16win32
msbuild "PhysXSDK.sln" \p:configuration=Debug
msbuild "PhysXSDK.sln" \p:configuration=Release

cd ..\..\..\..\..\
XCOPY Src\PhysX-4.1\physx\bin\win.x86_64.vc142.md .\Buildx64 /E
XCOPY Src\PhysX-4.1\physx\bin\win.x86_64.vc142.md .\Buildx64 /E
XCOPY Src\PhysX-4.1\physx\bin\win.x86_64.vc142.md .\Buildx86 /E
XCOPY Src\PhysX-4.1\physx\bin\win.x86_64.vc142.md .\Buildx86 /E






