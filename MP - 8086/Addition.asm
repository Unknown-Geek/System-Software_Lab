assume cs:code ds:data
data segment
    num1 dw 1234h
    num2 dw 0032h
    carry dw ?
    sum dw ?
data ends

code segment
    start:
    mov ax,@data
    mov ds,ax
    
    mov ax,num1
    mov bx,num2
    add ax,bx
    mov sum,ax   
    jnc skip
    mov carry,01h
    
    skip:
    mov ah,4ch
    int 21h
code ends
end start