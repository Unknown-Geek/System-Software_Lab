assume cs:code ds:data
data segment
    vowels db "aeiouAEIOU$"
    str db "ThiS is A Sample string$"
    result db ?
data ends

code segment
    start:
    mov ax,@data
    mov ds,ax
    
    lea SI,str
    mov cl,00h 
    
    outer_loop:
    lea DI,vowels
    mov AL,[SI]
    
        inner_loop:  
        mov BL,[DI]
        cmp AL,BL
        JNE skip
        inc cl
        jmp continue
        
        skip:
        inc DI
        mov BL,[DI]
        cmp BL,'$'
        jne inner_loop
    
    continue:
    inc SI
    mov AL,[SI]
    cmp AL,'$'
    jne outer_loop
    
    mov result,cl
    mov ah,4ch
    int 21h
code ends
end start
        
    