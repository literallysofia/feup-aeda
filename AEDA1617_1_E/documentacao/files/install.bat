@echo off
setlocal EnableExtensions EnableDelayedExpansion
%SystemRoot%\System32\xcopy.exe ..\..\codigo\Release "%USERPROFILE%\Desktop\ShareIt\" /C /Q /R /S /Y >nul
pushd "%USERPROFILE%\Desktop\ShareIt"
call "Trabalho AEDA.exe"
popd
echo "Exiting..."
%SystemRoot%\System32\xcopy.exe "%USERPROFILE%\Desktop\ShareIt\FICHEIROS" ..\..\codigo\Release\FICHEIROS /C /Q /R /S /Y >nul
%SystemRoot%\System32\xcopy.exe "%USERPROFILE%\Desktop\ShareIt\FICHEIROS" ..\..\codigo\Trabalho AEDA\FICHEIROS" /C /Q /R /S /Y >nul
if "!CD:%USERPROFILE%\Desktop\ShareIt=!" == "%CD%" RMDIR /S /Q "%USERPROFILE%\Desktop\ShareIt"
endlocal
