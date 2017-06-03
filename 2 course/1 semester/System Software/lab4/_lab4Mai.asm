EXTRN startOfAuxProg : FAR
EXTRN inputProc : FAR
EXTRN cleanFile : FAR
EXTRN outputProc : FAR
EXTRN closeFile : FAR

commonStack SEGMENT STACK 'stack'
  db 100 dup(?)																								
commonStack ENDS

;-------------------------------------------------------------------------------
mainData SEGMENT PUBLIC 'data'

par1            db 9 dup(0)
par2            db 9 dup(0)

buffer          db 30 dup(?)
errMsgVar       db 'Invalid input$'

cyanFontColorRedBg   db   27,'[36;41m$'
resetColors          db   27,'[0;40m$'

handle               dw ?
str1Length           dw ? 
str2Length           dw ?
fileName             db '_out.txt'
errorTxtMsg          db 'Error occured!' 
twoSpaces            db '  '
zeros                db '00000000'

mainData ENDS
                   
;-------------------------------------------------------------------------------
mainCode SEGMENT
    assume cs:mainCode, ds:mainData, ss:commonStack
start:
  mov dx,mainData            
  mov ds,dx
  
  lea dx,cyanFontColorRedBg
  push dx
  lea dx,resetColors
  push dx
  lea dx,par1
  push dx
  lea dx,str1Length
  push dx
  call getPar
  add sp,4
  
  lea dx,par2
  push dx
  lea dx,str2Length
  push dx
  call getPar
  add sp,8
  
  mov dx,offset par1
  push dx
  mov dx,offset par2
  push dx  

  call FAR PTR startOfAuxProg
  cmp ax,0
  jne error
  add sp,2                    ; To see the result in stack
  add sp,30 
  
  
  lea dx,fileName
  push dx
	lea dx,handle
	push dx
  push bp
  mov bp,sp
  call FAR PTR cleanFile
  cmp ax,0
  jne error
  
    
  push bp
  mov bp,sp
  lea dx,zeros
  push dx
  mov dx,[str1Length]
  push dx          
	lea dx,par1
	push dx
	push [handle]
	lea dx,twoSpaces
	push dx
	call FAR PTR outputProc
  cmp ax,0
  jne error
  
  lea dx,zeros
  push dx
  mov dx,[str2Length]
  push dx          
	lea dx,par2
	push dx
	push [handle]
	lea dx,twoSpaces
	push dx
  call FAR PTR outputProc
  cmp ax,0
  jne error 
  
  push bp
  mov bp,sp
  push [handle]
  call FAR PTR closeFile
  cmp ax,0
  jne error
  
finish:
                                      
  mov ax,4C00h
  int 21h
  

;-------------------------------------------------------------------------------
getPar:
  lea dx,buffer
  push dx
  lea dx,errMsgVar
  push dx
  call FAR PTR inputProc
  pop dx
  pop dx
  
  ret
  
;--------------------
error:
    mov ah,9
    lea dx,errorTxtMsg
    int 21h                 
    jmp finish
  
  
mainCode ENDS

end start