%ifndef _BASE8_ASM_ ; continue if _BASE8_ASM_ is undefined
%define _BASE8_ASM_ ; make sure that it is defined
                        ; otherwise, %include allows only one inclusionbits 32 ; assembling for the 32 bits architecture


convert_base8:
    ; void convert_base8(char* buffer, int num)
    ; ---------------------------------------------

    mov edi, [esp + 4] ; buffer
    mov eax, [esp + 8] ; num

    ; while(num != 0)
    cld
    while_gz:
        mov edx, 0
        mov ebx, 8
        div ebx

        mov bl, dl
        add bl, '0'
        mov byte [edi], bl
        inc edi

        cmp eax, 0
        jnz while_gz

    mov esi, [esp + 4] ; buffer

    ; remember the current edi address
    mov ebx, edi
    dec edi
    ; while esi < edi
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
        ; append a 0
        mov byte [ebx], 0
        ret

        
%endif
