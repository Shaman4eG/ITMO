masm _lab4Mai.asm, _lab4Mai.obj
masm _lab4iCk.asm, _lab4iCk.obj
masm _lab4Aux.asm, _lab4Aux.obj
lib _lab4.lib _lab4Aux.obj _lab4iCk.obj
link _lab4Mai.obj+_lab4.lib, _lab4.exe

