assume cs:code,ds:data
data segment
    num1 dw 145
    result dw ?
data ends

code segment 
    start:
    mov ax,@data
    mov ds,ax
              
    mov ax,num1         
    mov dx,01h
    mov cx,00h
    
    loop:
    sub ax,dx
    inc cx
    inc dx
    inc dx
    cmp ax,dx
    ja loop
    
    mov result,cx
    
    mov ah,4ch
    int 21h
code ends
end start