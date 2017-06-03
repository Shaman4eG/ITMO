use16
org 100h

;	Запись первой строки
	mov cx,-1
	mov si,0
	mov di,0
forI:
	inc cx
	mov bx,cx

	cmp cx,64
	je endOfFirstStrFilling

	mov dh,[curBitToCmp]
	test byte[bitMsc + si],dh
	jne checkIfNum
notNum:
	call updCurBitMsc
	jmp forI
    

addSym:
	call updCurBitMsc

	mov al,[srcStr + bx]
	mov [firstStr + di],al
	inc di

	jmp forI

endOfFirstStrFilling:
	mov [firstStr + di],'$'


;	Запись второй строки
	mov cx,64
	mov di,0

secondStrLoop:
	mov bx,cx
	dec bx

	cmp [srcStr + bx],41h  
	jne addSymToSecondStr
	cmp bx,0
	je addSymToSecondStr
	cmp [srcStr + bx - 1],41h
	jne addSymToSecondStr

	jmp doOutput

addSymToSecondStr:
	mov al,[srcStr + bx]
	mov [secondStr + di],al
	inc di

doLoop:
	loop secondStrLoop


doOutput:
	mov [secondStr + di],'$'
	call output


	mov ax,4C00h
	int 21h

;--------------------------------------------------------------------------
;	Процедуры

updCurBitMsc:
	cmp [curBitToCmp],1h
	je bitToFirstPos

	shr [curBitToCmp],1
	ret

bitToFirstPos:
	mov [curBitToCmp],80h
	inc si
	ret
  
;---
checkIfNum:
  push bx
  push cx
  push si
  
  mov cx,10
  mov si,0
checkNumLoop:
  mov dl,[zeroCode] 
  add dx,si
  cmp [srcStr + bx],dl
  je restoreRegisters
  
  inc si
  loop checkNumLoop
  
  pop si
  pop cx
  pop bx
  jmp notNum
  
restoreRegisters:
  pop si
  pop cx
  pop bx
  jmp addSym
;---
newLine:
	mov dl, 0ah
	mov ah, 02h
	int 21h

	mov dl, 0dh
	mov ah, 02h
	int 21h

	ret

;---
output:
	mov dx,srcStr
	mov ah,9
	int 21h

	call newLine

	call outBitMsc

	call newLine

	mov dx,firstStr
	mov ah,9
	int 21h

	call newLine

	mov dx,secondStr
	mov ah,9
	int 21h

	ret

;---
outBitMsc:

	mov cx,-1
	mov si,0
	mov [curBitToCmp],80h
forBM:
	inc cx

	cmp cx,64
	je return

	mov dh,[curBitToCmp]
	test [bitMsc + si],dh
	jne bitExists

	mov [bitMscBitKpr],30h
	jmp printBit

bitExists:
	mov [bitMscBitKpr],31h

printBit:
	mov dx,bitMscBitKpr
	mov ah,9
	int 21h

	call updCurBitMsc
	jmp forBM

return:
	ret

;--------------------------------------------------------------------------
;	Данные

srcStr	      db "150+4AAnet5asdjksASDndw ;..eQeqweqw112 3JAIDSOjdadaiw238123*&2AA$"
bitMsc	      db 8 dup(0F0h)
curBitToCmp   db 80h
zeroCode      db 30h
bitMscBitKpr  db ?
dollar	      db "$"
firstStr      db 64 dup(?)
secondStr     db 64 dup(?)













