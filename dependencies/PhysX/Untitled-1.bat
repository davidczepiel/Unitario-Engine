cd dependencies\Physx

cd Src\PhysX-4.1\physx
call generate_projects.bat

cd compiler\vc16win64
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\Common7\Tools\VsMSBuildCmd.bat"
msbuild PhysXSDK.sln /p:Configuration=Debug /p:Platform=x64
msbuild PhysXSDK.sln /p:Configuration=Release /p:Platform=x64

cd ..\..\..\..\..\
XCOPY Src\PhysX-4.1\physx\bin\win.x86_64.vc142.md .\Buildx64 /E /y /i


