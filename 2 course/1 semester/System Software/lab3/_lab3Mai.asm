EXTRN startOfAuxProg:FAR

commonStack SEGMENT STACK 'stack'
  db 100 dup(?)																								
commonStack ENDS

;-------------------------------------------------------------------------------
mainData SEGMENT PUBLIC 'data'

par1            db '13FBD$'
par2            db 'F$'

buffer          db 100 dup(?)

mainData ENDS
                   
;-------------------------------------------------------------------------------
mainCode SEGMENT
    assume cs:mainCode, ds:mainData, ss:commonStack
start:
  mov dx,mainData            
  mov ds,dx 

  mov dx,offset par1
  push dx
  mov dx,offset par2
  push dx
  
  call FAR PTR startOfAuxProg
  add sp,2            ; To see the result in stack
  add sp,30
                                      
  mov ax,4C00h
  int 21h
  

;-------------------------------------------------------------------------------
  
  
mainCode ENDS

end start