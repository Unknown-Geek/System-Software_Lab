assume cs:code,ds:data
data segment
    num1 db 06h
    num2 db 05h
    result db ?
data ends

code segment 
    start:
    mov ax,@data
    mov ds,ax
              
    mov bl,num1         
    mov bh,num2
    mov al,00h
    mov cl,bl
    
    lcm_loop:
    mov al,cl
    mov ah,00h
    div bh
    cmp ah,00h
    je done
    add cl,bl
    jmp lcm_loop
           
    done:
    mov result,cl
    
    mov ah,4ch
    int 21h
code ends
end start