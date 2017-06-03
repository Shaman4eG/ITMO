@echo off
chcp 65001
call "D:\Program Files\VisualStudioEnterprise2015\VC\vcvarsall.bat" x86     
cl.exe /sdl /Od /Zi /EHsc main.cpp /Fo:./Debug/main.obj /Fe:./Debug/Lab.exe 
PAUSE