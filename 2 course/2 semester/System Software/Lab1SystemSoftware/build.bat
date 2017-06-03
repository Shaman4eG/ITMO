@echo off
chcp 65001
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86     
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:
cl.exe main.cpp /Fo:./Debug/main.obj /Fe:Lab1.exe /EHsc /link
PAUSE