bits 32

global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data

    ;.....
    sir_q dq 0x1234577, 1234, 0x7777
    sir_len equ ($ - sir_q) / 8
    result resd sir_len
    
    format db `%s\n`, 0

segment code use32 class=code

    determina_grad:
        push ebp
        mov ebp, esp
        
        mov eax, [ebp + 8]
        mov edx, 0
        
        .loop:
            push eax
            and eax, 111b
            
            cmp eax, 7
            pop eax
            jne .not_equal
        
            inc edx
            shr eax, 3
            jmp .next
        
            .not_equal:
                shr eax, 1
            
            .next:
                cmp eax, 0
                jne .loop
        
        mov esp, ebp
        pop ebp
        
        mov eax, edx
        
        ret
        
    base2_print:
        push ebp
        mov ebp, esp
        
        mov eax, [ebp + 8]
        push dword 0
        .print_loop:
            mov dl, '0'
            shr eax, 1
            adc dl, 0
            
            mov byte [esp], dl
            sub esp, 1
            
            cmp eax, 0
            jne .print_loop
        
        add esp, 1
        push esp
        push dword format
        call [printf]
        add esp, 4 * 2
        
        
        mov esp, ebp
        pop ebp
        
        ret

    start:
        cld
        mov esi, sir_q
        mov edi, result
        mov ecx, sir_len
        jecxz end_loop
        start_loop:
            lodsd
            pusha
            push eax
            call determina_grad
            add esp, 4
            
            cmp eax, 2
            popa
            jb .not_add
        
            pusha
            push eax
            call base2_print
            add esp, 4
            popa
            
            stosd 
            .not_add:
            lodsd
            
            loop start_loop
        end_loop:
        
     
        
        
        ;exit(0)
        push dword 0
        call [exit]
        