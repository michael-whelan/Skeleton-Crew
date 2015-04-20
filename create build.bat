for /f "tokens=1* delims=" %%a in ('date /T') do set datestr=%%a
move "*build" "old builds\%datestr:/= %previous build"
"C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE\devenv.exe" /Clean release "Skeleton Crew\Skeleton Crew.sln"
"C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE\devenv.exe" /build release "Skeleton Crew\Skeleton Crew.sln"
xcopy "Skeleton Crew\Release" "%datestr:/= %build" /s /i /e /h /k /y
xcopy "Skeleton Crew\Skeleton Crew\images" "%datestr:/= %build\images" /s /i /e /h /k /y
xcopy "Skeleton Crew\Skeleton Crew\sounds" "%datestr:/= %build\sounds" /s /i /e /h /k /y
xcopy "Skeleton Crew\SkeletonCrewInstaller\SkeletonCrewInstaller\Express\SingleImage\DiskImages\DISK1\setup.exe" "%datestr:/= %build" /s /i /e /h /k /y
for /d  %%X in (*build) do "..\7-Zip\7z.exe" a "%%X.ZIP" "%%X\"
move /Y "*.ZIP" "%datestr:/= %build"