@echo off
chcp 65001
call "C:\Program Files\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86     
cl.exe /sdl /Od /Zi /EHsc main.cpp /Fo:main.obj /Fe:Lab.exe
echo Linking ended!