@echo off
:: init developer console (VS14)
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\vsvars32.bat"


cd libs
set OUT_D_DIR=%cd%/../../bin/Debug
set OUT_R_DIR=%cd%/../../bin/Release
set LIB_DIR=%cd%/__lib/
set INC_DIR=%cd%/__include/

call :yaml-cpp-d





echo All dependencies prepared.
goto :exit

:: 
:yaml-cpp
pushd "yaml-cpp/build"

@msbuild yaml-cpp.vcxproj /t:Clean,Build /p:Configuration=Release
robocopy Release "%OUT_D_DIR%" yaml-cpp.dll /V
robocopy Release "%OUT_R_DIR%" yaml-cpp.dll /V
robocopy Release "%LIB_DIR%" yaml-cpp.lib /V
robocopy ../include "%INC_DIR%" /MIR /V

popd
exit /B
:: 

:: 
:yaml-cpp-d
pushd "yaml-cpp/build"

@msbuild yaml-cpp.vcxproj /t:Clean,Build /p:Configuration=Debug
robocopy Debug "%OUT_D_DIR%" yaml-cpp.dll /V
robocopy Debug "%OUT_R_DIR%" yaml-cpp.dll /V
robocopy Debug "%LIB_DIR%" yaml-cpp.lib /V
robocopy ../include "%INC_DIR%" /MIR /V

popd
exit /B
:: 

:exit
pause
