assume cs:code ds:data
data segment
    num1 dw 1234h
    num2 dw 1f32h
    resulth dw ?
    resultl dw ?
data ends

code segment
    start:
    mov ax,@data
    mov ds,ax
    
    mov ax,num1
    mov bx,num2
    
    mul ax
    mov resulth,dx
    mov resultl,ax
    
    mov ah,4ch
    int 21h
code ends
end start