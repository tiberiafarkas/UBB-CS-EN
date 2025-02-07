bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fopen, fclose, fprintf, printf, perror              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll
import perror msvcrt.dll

                          
    ;2.	Se citește de la tastatură un număr N și apoi N numere.
    ;Să se calculeze suma numerelor pare introduse, să se calculeze suma numerelor impare introduse, apoi diferența dintre cele două sume.
    ;Să se afișeze în fișierul output.txt cele 3 rezultate, în baza 16, pe linii separate.
                      
                          
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
    n dd 0
    sum_pare dd 0
    sum_imp dd 0
    dif_sume dd 0
    numar dd 0
    file_ptr resd 1
    access_r db "r", 0
    access_w db "w", 0
    format_r db "%d", 0
    format_w db "%x", 0
    message db "n=", 0
    message1 db "sum of even numbers:", 0
    message2 db "sum of odd numbers:", 0
    message3 db "difference:", 0
    newline db 10, 0
    file db "output.txt", 0
    cpy dd 0
    errors db "Error found:", 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword message
        call [printf]
        add esp, 4
        
        ;read number n
        push dword n
        push dword format_r
        call [scanf]
        add esp, 4 * 2
        
        mov ecx, dword[n]
        ;while ecx > 0
        
        while_loop:
            mov dword[cpy], ecx
            
            ;read the number
            push dword numar
            push dword format_r
            call [scanf]
            add esp, 4*2
            
            
            ;check if the number is even or not
            mov eax, dword[numar]
            compute_parity:
                mov bx, 2
                mov edx, 0
                div bx
                
                ;cmp eax, 0
                ;jne compute_parity
                
            cmp edx, 0  ;in edx we have the remainder, if it is 0 then we have an even number
            je add_even
            jmp add_odd
            
            add_even:
                mov eax, dword[sum_pare]
                add eax, dword[numar]
                mov dword[sum_pare], eax
                jmp end_loop
                
            add_odd:
                mov eax, dword[sum_imp]
                add eax, dword[numar]
                mov dword[sum_imp], eax
                jmp end_loop
                
            end_loop:
                mov ecx, dword[cpy]
                loop while_loop
               
        mov eax, dword[sum_pare]
        mov ebx, dword[sum_imp]
        sub eax, ebx
        mov dword[dif_sume], eax
        
        ;open the output file
        push dword access_w
        push dword file
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        jz get_out
        
        mov dword[file_ptr], eax
                
        push dword message1
        push dword[file_ptr]
        call [fprintf]
        add esp, 4 * 2
        
        push dword[sum_pare]  
        push format_w
        push dword[file_ptr]
        call [fprintf]
        add esp, 4 * 3
        
        push dword newline
        push dword[file_ptr]
        call [fprintf]
        add esp, 4 * 2
        
        push dword message2
        push dword[file_ptr]
        call [fprintf]
        add esp, 4 * 2
        
        push dword[sum_imp]
        push format_w
        push dword[file_ptr]
        call [fprintf]
        add esp, 4 * 3
        
        push dword newline
        push dword[file_ptr]
        call [fprintf]
        add esp, 4 * 2
        
        push dword message3
        push dword[file_ptr]
        call [fprintf]
        add esp, 4 * 2
        
        push dword[dif_sume]
        push format_w
        push dword[file_ptr]
        call [fprintf]
        add esp, 4 * 3
                
        ;make the print
        ;push dword[dif_sume]
        ;push dword format_w
        ;push dword[sum_imp]
        ;push dword format_w
        ;push dword[sum_pare]
        ;push dword format_w
        ;;push dword message1
        ;push dword[file_ptr]
        ;call [fprintf]
        ;add esp, 4*7
        
        ;close the file
        push dword[file_ptr]
        call [fclose]
        add esp, 4
        
        
        ; exit(0)
        get_out:
            push dword[errors]
            call [perror]
            add esp, 4
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
