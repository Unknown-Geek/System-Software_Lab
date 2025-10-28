assume cs:code ds:data
data segment
    num1 dw 1234h
    num2 dw 1024h
    diff dw ?
    borrow dw ?
data ends

code segment
    start:
    mov ax,@data
    mov ds,ax
    
    mov ax,num1
    mov bx,num2
    sbb ax,bx
    
    jnc skip
    mov borrow,01h
    
    skip:
    mov diff,ax
    mov ah,4ch
    int 21h
code ends
end start