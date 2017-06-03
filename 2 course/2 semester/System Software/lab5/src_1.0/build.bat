@echo off
chcp 65001
call "C:\Program Files\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86     
cl.exe /sdl /Od /Zi /EHsc data.cpp /Fo:data.obj /Fe:data.exe
echo Linking ended!