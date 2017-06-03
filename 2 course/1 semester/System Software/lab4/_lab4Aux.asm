PUBLIC startOfAuxProg 

commonStack SEGMENT STACK 'stack'																								
commonStack ENDS


auxCode SEGMENT
    assume cs:auxCode
startOfAuxProg PROC FAR

  push cx
  push dx
  push bx
  push sp
  push bp
  push si
  push di

  push bp
  mov bp,sp

  sub sp,12               ; 12 byte in stack for 6 local variables
  mov bx,[bp + 22]        ; bx = currentParametrAddress           
  call parProcessing
  
  mov ax,[bp - 2]         ;\
  mov [bp - 6],ax         ; \
  mov ax,[bp - 4]         ;  Freeing space for second DWORD number.    
  mov [bp - 8],ax         ;_/
  
  mov bx,[bp + 20]
  call parProcessing
                                              
  pop ax    ;!!!!!!!!!!UBRAT'
  mov ax,0  
  
endOfAuxilProc:
      
  sub sp,6
  mov ax,[bp + 18]
  mov [bp - 14],ax
  mov ax,[bp + 16]
  mov [bp - 16],ax
  
  mov ax,0  
  
  mov di,[bp + 2]
  mov si,[bp + 4]
  mov bp,[bp + 6]
  mov bx,[bp + 10]
  mov dx,[bp + 12]
  mov cx,[bp + 14]               
  ret 
  
startOfAuxProg ENDP

;-------------------------------------------------------------------------------
; Подпрограммы

parProcessing:
    mov ax,0                ;\
    mov [bp - 2],ax         ; \
    mov [bp - 4],ax         ;  \
    mov ax,1                ;   initialization of local variables
    mov [bp - 10],ax        ;  /
    mov [bp - 12],ax        ;_/
    
    
    mov si,-1 
  countLengthFor:           ; *BEGIN* Counting digits
    inc si                  ;
                            ;
    cmp si,9                ; If '$' wasn't found in first 9 symbols, the
    jne notFinished         ; number can't be converted to DWORD.
                            ;
    mov ax,1                ; Put error number to ax.
    jmp endOfAuxilProc      ; Return to main program.
                            ;
  notFinished:              ;
    mov al,'$'              ;
    cmp [bx + si],al        ;
    jne countLengthFor      ; *END* Counting digits
    
    mov cx,si
    mov di,si
    dec si
  pushStrsLoop:
    dec si      
    dec cx
  
    cmp cx,0
    jne notFinished2
    call specialConvert
    jmp checkForSpecialCases                    
  
  notFinished2:
    call convert
    dec si
    dec cx

  checkForSpecialCases:
    cmp di,2
    jbe if1or2digits
    
    
    mov ax,0
    cmp [bp - 10],ax
    jl checkIfWorkingWithUpperDigits

  checkIfShlNeeded:
    mov ax,1
    cmp [bp - 12],ax
    jne swapUpAndLowByte
    mov ax,0
    mov [bp - 12],ax         
    
    mov ax,[bp - 2]
    shl ax,1
    shl ax,1
    shl ax,1
    shl ax,1
    shl ax,1
    shl ax,1
    shl ax,1
    shl ax,1
    mov [bp - 2],ax                    
    
    jmp checkForNextSlot          
    
  swapUpAndLowByte:
    mov ax,1
    mov [bp - 12],ax
    
    mov ax,[bp - 2]           
    rol ax,1  
    rol ax,1
    rol ax,1
    rol ax,1
    rol ax,1
    rol ax,1
    rol ax,1
    rol ax,1
    mov [bp - 2],ax          
    
    
  checkForNextSlot:
    mov ax,0
    cmp [bp - 10],ax
    jne preNextPair
    
  movLower:
    mov ax,[bp - 2]
    mov [bp - 4],ax
    mov ax,0
    mov [bp - 2],ax
  
  preNextPair:
    mov ax,[bp - 10]
    dec ax
    mov [bp - 10],ax  
    
  nextPair:
    cmp cx,0
    jne pushStrsLoop
    
    ret

;--------------------
convert:
  push cx
  push di
  
  mov ax,2
  add si,2
  
loopForTwoDigits:
  dec ax
  mov dh,dl
  
  mov cx,6
  mov di,0
  dec si 
  
  checkAtoFLoop:
    mov dl,'A'
    add dx,di
    cmp [bx + si],dl
    je  highDigit
  
    inc di
    loop checkAtoFLoop
    
lowDigit:
  mov dl,[bx + si]
  sub dl,'0'
  jmp checkWhichRound
  
highDigit:
  mov dl,[bx + si]
  sub dl,'A' - 10
    
checkWhichRound:
  cmp ax,0
  jne loopForTwoDigits
  
  shl dl,1
  shl dl,1
  shl dl,1
  shl dl,1
  add dl,dh
  mov dh,0
  mov [bp - 2],dl
  
  pop di
  pop cx
  ret
  
;---------------------------
specialConvert:
  push cx
  push di
  
  mov cx,6
  mov di,0
  inc si
  
  checkAtoFLoopInSC:
    mov dl,'A' 
    add dx,di
    cmp [bx + si],dl
    je  highDigitInSC
  
    inc di
    loop checkAtoFLoopInSC
    
lowDigitInSC:
  mov dl,[bx + si]
  sub dl,'0'
  jmp endSpecialConvert
  
highDigitInSC:
  mov dl,[bx + si]
  sub dl,'A' - 10
  
endSpecialConvert:  
  mov [bp - 2],dl
  
  pop di
  pop cx
  ret 
  
;---------------------------
if1or2digits:
    mov ax,[bp - 2]
    mov [bp - 4],ax
    mov ax,0
    mov [bp - 2],ax
    
    ret

;---------------------------    
checkIfWorkingWithUpperDigits:
    cmp di,6
    jg checkIfShlNeeded
    
    ret

;---------------------------
  
auxCode ENDS

end 
  
  