
chcp 65001
ml /c /coff uselibrary.asm
link /subsystem:windows uselibrary.obj

g++ main.cpp -g -o uselibrary
uselibrary