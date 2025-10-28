assume cs:code ds:data
data segment
    num db 08h,01h,05h,02h,03h
    len db 05h
    msg dw "Sorted Array : $"
data ends

code segment
    start:
    mov ax,@data
    mov ds,ax
    
    mov ch,len
    dec ch
    lea SI,num
    
    outer:
    lea DI,num
    mov cl,len
    dec cl
    
        inner:
        mov al,[DI]
        mov bl,[DI+1]
        cmp al,bl
        ja swap
        jmp no_swap
        
        swap:
        mov [DI],bl
        mov [DI+1],al
        
        no_swap:
        dec cl
        inc DI
        cmp cl,00h
        jne inner
    
    dec ch
    inc SI
    cmp ch,00H
    jne outer
 
    lea SI,num
    mov cl,len
    lea dx,msg
    mov ah,09h
    int 21h
    
    display_loop:    
    mov dx,[SI]
    mov ah,02h
    add dx,30h
    int 21h
    
    mov dx,' '
    mov ah,02h
    int 21h
    
    dec cl
    inc SI
    cmp cl,00h
    jne display_loop
    
    mov ah,4ch
    int 21h
code ends
end start