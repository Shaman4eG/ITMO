PUBLIC inputProc
PUBLIC cleanFile
PUBLiC outputProc 
PUBLIC closeFile

commonStack SEGMENT STACK 'stack'																								
commonStack ENDS


inputCode SEGMENT
    assume cs:inputCode
inputProc PROC FAR

  push bp
  mov bp,sp
  
  push cx
  push dx
  push bx
  push sp
  push si
  push di

input:
  call newLine
  mov al,9
  call inputStr
  
  mov ch,0
  mov cl,al                   ; CX = length of input string
  mov si,0
  mov bx,[bp + 8]
  add bx,2
checkInputForAppropriatenessLoop:
  mov dl,[bx + si]
  call checkIfHexDigit
  jc errMsg
  inc si
  loop checkInputForAppropriatenessLoop

  mov cx,si
  mov si,0
saveParLoop: 
  mov bx,[bp + 8]
  add bx,2
  mov dl,[bx + si]
  mov bx,[bp + 14]
  mov [bx + si],dl
  inc si
  loop saveParLoop
  mov al,'$' 
  mov [bx + si],al
  
  pop di
  pop si
  pop sp
  pop bx
  pop dx
  pop cx 
  
  pop bp
  ret

inputProc ENDP

;-------------------------------------------------------------------------------
inputStr:
    push dx
    mov ah,09h                ;\
    mov dx,[bp + 18]          ; Set input color
    int 21h                   ;/ 
    mov ah,0Ah                ; 0Ah - string input
    mov bx,[bp + 8]
    mov [bx],al               ; buffer[0] = maxNumOfSymbols
    mov dl,0
    mov [bx + 1],dl           ; buffer[1] = 0 (real length)
    mov dx,bx                                        
    int 21h
    mov ah,09h                ;\
    mov dx,[bp + 16]          ; Reset input color
    int 21h                   ;/         
    mov al,[bx + 1]           ; AL = length of input string
    mov bx,[bp + 12]
    mov [bx],al
    pop dx                                 
    ret
    
;---------------------
checkIfHexDigit:
    cmp dl,'0'              
    jl invalidInput               
    cmp dl,'9'              
    jg isAtoF               
    clc
    ret                  
 
isAtoF:       
    cmp dl,'A'              
    jl invalidInput                
    cmp dl,'F'             
    jg invalidInput 
    clc             
    ret                     
 
invalidInput:
    mov dl,0               
    stc                       ; CF = 1
    ret   

;---------------------
errMsg:
  call newLine
  mov bx,[bp + 6]
 	mov dx,bx
	mov ah,9
	int 21h
  jmp input
  
;---------------------
newLine:
  push dx
  push ax
  
	mov dl, 0ah
	mov ah, 02h
	int 21h

	mov dl, 0dh
	mov ah, 02h
	int 21h

  pop ax
  pop dx
	ret

inputCode ENDS

;-------------------------------------------------------------------------------
outputCode SEGMENT
    assume cs:outputCode
cleanFile PROC FAR
  ; rewrite file
  mov ah,3Ch              
  mov dx,[bp + 4]       
  mov cx,0                
  int 21h                 
  jc errorRewritingFile                           
	mov bx,[bp + 2]
  mov [bx],ax		                ; ax contains file descriptor
  mov ax,0
  ret 6

errorRewritingFile:
	mov ax,1
  ret   


cleanFile ENDP

;--------------------

outputProc PROC FAR
  push bx
	push cx
	push dx
	push bp
	mov bp,sp
	add bp,12   
	
  
	mov ah,40h
  mov cx,8  			             	;\              
	sub cx,[bp + 6]  	            ; length
  mov dx,[bp + 8]     	        ; adress DS:DX 
  mov bx,[bp + 2]               ; handle
	int 21h
	jc incorrectWriteToTextFile
  
	; write
	mov ah,40h  			             	              
	mov cx,[bp + 6]  	            ; length
  mov dx,[bp + 4]     	        ; adress DS:DX 
	int 21h
	jc incorrectWriteToTextFile
  
  ; writing 2 spaces
	mov ah,40h  			             	              
	mov cx,2  	            
  mov dx,[bp]     	                       
	int 21h
	jc incorrectWriteToTextFile
	
  ; if correct
	mov ax,0
	jmp exitWriteToTextFile
  
incorrectWriteToTextFile:
	mov ax,1
	
exitWriteToTextFile:
	pop bp
	pop dx
	pop cx
	pop bx
	ret 10  
  
outputProc ENDP

;--------------------
closeFile PROC FAR
	; close file
	mov ah,3Eh
  mov bx,[bp - 2]
	int 21h
	jc errorClosingFile
  mov ax,0
  ret 4

errorClosingFile:
	mov ax,1
	ret

closeFile ENDP

  
outputCode ENDS

end                      