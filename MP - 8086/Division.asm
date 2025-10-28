assume cs:code,ds:data
data segment
    num1 dw 001Ah
    num2 dw 0005h
    quo dw ?
    rem dw ?
data ends

code segment 
    start:
    mov ax,@data
    mov ds,ax
    
    mov ax,num1
    mov bx,num2
    
    div bx
    mov quo,ax
    mov rem,dx
    
    mov ah,4ch
    int 21h
code ends
end start