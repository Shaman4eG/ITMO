use16
org 100h

	; Переформирование исходного массива
	mov cx,-1
forI:
	inc cx
	mov bx,4
	imul bx,cx

	cmp cx,9
	je endOfPart1

	mov [outerLpCounterKpr],cl
forJ:
	inc cx
	mov si,4
	imul si,cx

	test byte[srcArr + bx + 3],80h
	jns if1ElemPos
	mov [sign1],1
	jmp if1ElemNeg
if1ElemPos:
	mov [sign1],0
if1ElemNeg:

	test byte[srcArr + si + 3],80h
	jns if2ElemPos
	mov [sign2],1
	jmp if2ElemNeg
if2ElemPos:
	mov [sign2],0
if2ElemNeg:

	mov dl,[sign1]
	cmp dl,[sign2]
	je nextJ

	mov eax,[srcArr + si]
	mov edx,[srcArr + bx + 4]
	mov [srcArr + bx + 4],eax
	mov [srcArr + si],edx
	mov cx,10

nextJ:
	cmp cx,10
	jl forJ

	mov cl,[outerLpCounterKpr]
	jmp forI



endOfPart1:

	; Перенос части элементов исходного массива в конечный
	mov eax,[srcArr + 4]
	neg eax
	mov [negSecondArrElem],eax

	mov eax,[srcArr + 32]
	neg eax
	mov [negPenultArrElem],eax


	mov cx,-1
	mov di,0
forI2:
	inc cx
	mov bx,4
	imul bx,cx

	cmp cx,10
	je endOfPart2


	mov eax,[negSecondArrElem]
	cmp [srcArr + bx],eax
	js chkBotLim
	je forI2

	mov eax,[negPenultArrElem]
	cmp eax,[srcArr + bx]
	jns addElem
	jmp forI2

chkBotLim:
	mov eax,[negPenultArrElem]
	cmp [srcArr + bx],eax
	js forI2
	je forI2

addElem:
	mov eax,[srcArr + bx]
	mov [resArr + di],eax
	add di,4
	jmp forI2


endOfPart2:
	mov ax,4C00h
	int 21h



; Данные
k      db ?
srcArr dd 1,2,3,4,-5,-6,7,-8,-9,3;-1,5,-5,7,-7,0,-8,3,-5,10;123, -124, 234, 665, 232, -11, 3, 243, -55, 22
resArr dd 10 dup(?)
sign1  db ?
sign2  db ?
outerLpCounterKpr db ?

negSecondArrElem dd ?
negPenultArrElem dd ?