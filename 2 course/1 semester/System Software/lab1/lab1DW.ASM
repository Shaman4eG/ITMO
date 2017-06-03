use16
org 100h

	; Переформирование исходного массива
	mov cx,-1
forI:
	inc cx
	mov bx,2
	imul bx,cx

	cmp cx,9
	je endOfPart1

	mov [outerLpCounterKpr],cl
forJ:
	inc cx
	mov si,2
	imul si,cx

	test byte[srcArr + bx + 1],80h
	jns if1ElemPos
	mov [sign1],1
	jmp if1ElemNeg
if1ElemPos:
	mov [sign1],0
if1ElemNeg:

	test byte[srcArr + si + 1],80h
	jns if2ElemPos
	mov [sign2],1
	jmp if2ElemNeg
if2ElemPos:
	mov [sign2],0
if2ElemNeg:

	mov dl,[sign1]
	cmp dl,[sign2]
	je nextJ

	mov ax,[srcArr + si]
	mov dx,[srcArr + bx + 2]
	mov [srcArr + bx + 2],ax
	mov [srcArr + si],dx
	mov cx,10

nextJ:
	cmp cx,10
	jl forJ

	mov cl,[outerLpCounterKpr]
	jmp forI



endOfPart1:

	; Перенос части элементов исходного массива в конечный
	mov ax,[srcArr + 2]
	neg ax
	mov [negSecondArrElem],ax

	mov ax,word[srcArr + 16]
	neg ax
	mov [negPenultArrElem],ax


	mov cx,-1
	mov di,0
forI2:
	inc cx
	mov bx,2
	imul bx,cx

	cmp cx,10
	je endOfPart2


	mov ax,[negSecondArrElem]
	cmp [srcArr + bx],ax
	js chkBotLim
	je forI2

	mov ax,[negPenultArrElem]
	cmp ax,[srcArr + bx]
	js forI2
	je forI2
	jmp addElem

chkBotLim:
	mov ax,[negPenultArrElem]
	cmp [srcArr + bx],ax
	js forI2
	je forI2

addElem:
	mov ax,[srcArr + bx]
	mov [resArr + di],ax
	add di,2
	jmp forI2


endOfPart2:
	mov ax,4C00h
	int 21h



; Данные

srcArr dw -1,5,-5,7,-7,0,-8,3,-5,10;123, -124, 234, 665, 232, -11, 3, 243, -55, 22
resArr dw 10 dup(?)
sign1  db ?
sign2  db ?
outerLpCounterKpr db ?

negSecondArrElem dw ?
negPenultArrElem dw ?