assume cs:code ds:data
data segment
    num dw 000Ah
    msg_odd db "Odd Number$"
    msg_even db "Even Number$"
data ends

code segment
    start:
    mov ax,@data
    mov ds,ax
    
    mov ax,num
    mov bx,02h
    
    div bx
    
    cmp dx,00h
    jne odd
    jmp even
    
    odd:
    lea dx,msg_odd
    mov ah,09h
    int 21h
    jmp clean_up
    
    even:
    lea dx,msg_even
    mov ah,09h
    int 21h
    
    clean_up:
    mov ah,4ch
    int 21h
code ends
end start