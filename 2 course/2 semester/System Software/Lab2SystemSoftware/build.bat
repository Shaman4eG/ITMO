@echo off
chcp 65001
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86     
cl.exe /sdl /Od /Zi /EHsc main.cpp /Fo:./Debug/main.obj /Fe:./Debug/Lab.exe 
PAUSE