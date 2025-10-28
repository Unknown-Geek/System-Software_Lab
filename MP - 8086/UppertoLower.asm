assume cs:code ds:data
data segment
    str db "ThiS is A SamPle sTrIng$"
    result db 25 dup(?)
data ends

code segment
    start:
    mov ax,@data
    mov ds,ax
    
    lea SI,str 
    lea DI,result 
    
    outer_loop:
    mov al,[SI]
    cmp al,'Z'
    ja skip
    
    toLower:
    cmp al,' '
    je skip
    add al,32
      
    skip:
    mov [DI],al
    inc DI
    inc SI
    
    mov al,[SI]
    cmp al,'$'
    jne outer_loop 
    
    mov [DI],'$'
    lea dx,result
    mov ah,09h
    int 21h
    
    mov ah,4ch
    int 21h
code ends
end start
        
    