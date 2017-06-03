masm _lab3Mai.asm, _lab3Mai.obj
masm _lab3Aux.asm, _lab3Aux.obj
link _lab3Mai.obj+_lab3Aux.obj, _lab3RDY.exe
..\..\..\..\TASM\td.exe _lab3RDY.exe
