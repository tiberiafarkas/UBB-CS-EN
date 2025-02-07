bits 32

global _base8

segment data public data use32

    result resb 255 ;buffer for base8

segment code public code use32

_base8:
    ;create a stack frame
    push ebp
    mov ebp, esp
    
    mov eax, [ebp+8] ;the number
    lea edi, [result]
    
    ;while(num != 0)
    cld
    while_z:
        mov edx, 0
        mov ebx, 8
        div ebx
        
        mov bl, dl
        add bl, '0'
        mov byte [edi], bl
        inc edi
        
        cmp eax, 0
        jnz while_z
        
    ;remember the current address of edi
    mov ebx, edi
    dec edi
    
    lea esi, [result]
    
    ;while esi < edi
    reverse:
        cmp esi, edi
        jae end_reverse
        
        mov al, byte [edi]
        mov dl, byte [esi]
        mov byte [esi], al
        mov byte [edi], dl
        inc esi
        dec edi
        jmp reverse
        
    end_reverse:
        ;append a 0 as terminator
        mov byte [ebx], 0
    
    lea eax, [result]
    mov esp, ebp
    pop ebp
    
    ret
    
    