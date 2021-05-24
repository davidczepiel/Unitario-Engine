cd dependencies\Physx

cd Src\PhysX-4.1\physx
generate_projects.bat
echo 13
generate_projects.bat
echo 12

echo patata
cd compiler\vc16win64
msbuild "PhysXSDK.sln" \p:configuration=Debug 
echo patatadone
msbuild "PhysXSDK.sln" \p:configuration=Release

cd ..\vc16win32
msbuild "PhysXSDK.sln" \p:configuration=Debug
msbuild "PhysXSDK.sln" \p:configuration=Release

cd ..\..\..\..\..\
XCOPY Src\PhysX-4.1\physx\bin\win.x86_64.vc142.md .\Buildx64 /E
XCOPY Src\PhysX-4.1\physx\bin\win.x86_64.vc142.md .\Buildx64 /E
XCOPY Src\PhysX-4.1\physx\bin\win.x86_64.vc142.md .\Buildx86 /E
XCOPY Src\PhysX-4.1\physx\bin\win.x86_64.vc142.md .\Buildx86 /E






