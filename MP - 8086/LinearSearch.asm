assume cs:code ds:data
data segment
    num db 08h,01h,05h,02h,03h
    item db 0Ah
    len db 05h
    msg_found db "Item found at index : $"
    msg_notfound db "Item not found$"
data ends

code segment
    start:
    mov ax,@data
    mov ds,ax
    
    lea SI,num
    mov bl,item
    mov cl,len
    
    mov ch,00h ;index 
    
    check_loop:
    mov al,[SI]
    dec cl
    cmp al,bl
    jne not_found
    
    found:
    mov ch,len
    sub ch,cl
    dec ch
    
    lea dx,msg_found
    mov ah,09h
    int 21h
    
    mov dl,ch
    add dl,30h
    mov ah,02h
    int 21h
    jmp clean_up
    
    not_found:
    inc SI
    cmp cl,00h
    jne check_loop
    
    lea dx,msg_notfound
    mov ah,09h
    int 21h
    
    clean_up:
    mov ah,4ch
    int 21h
code ends
end start