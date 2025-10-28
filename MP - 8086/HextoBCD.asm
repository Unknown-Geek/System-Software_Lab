assume cs:code ds:data
data segment
    num db 21h
    result db ?
data ends

code segment
    start:
    mov ax,@data
    mov ds,ax
    
    mov al,num
    mov ah,00h
    mov bl,0AH
    div bl
    
    mov cl,04h
    shl al,cl
    add al,ah
    
    mov result,al
    
    mov ah,4ch
    int 21h
code ends
end start