assume cs:code ds:data
data segment
    num dw 05h
    result dw ?
data ends

code segment   
    start:
    mov ax,@data
    mov ds,ax
    
    mov bx,num
    mov ax,01h
    
    fact_loop:
    mul bx
    dec bx
    cmp bx,00h
    jne fact_loop
    
    mov result,ax
    
    mov ah,4ch
    int 21h
    
code ends
end start