@echo off
setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
cd /d "%~dp0"
rc.exe /nologo resource.rc
cl.exe /nologo /O2 /MT /W3 /utf-8 main.c resource.res /Fe:AntigravityMA.exe /link /SUBSYSTEM:WINDOWS /MANIFEST:EMBED
del /q main.obj resource.res AntigravityMA.exe.manifest 2>nul
echo Build completed: AntigravityMA.exe
