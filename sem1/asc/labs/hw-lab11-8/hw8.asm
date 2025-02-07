bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, perror               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll
import perror msvcrt.dll

                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

%include "base8.asm"                          
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
    ;Show for each number from 32 to 126 the value of the number (in base 8) and the character with that ASCII code.

    errors db "Error found", 0
    number resd 1
    cnt resb 1
    numbers resd 1
    format db "ascii_code = %c", 10, 13, 0

    string_format db "base8 = %s", 10, 13, 0
    base8_buffer resb 255

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; for (ecx = 32; ecx <= 126; ecx++)
        mov ecx, 32
        for_loop:
            cmp ecx, 126
            ja end_for

            ; print the ascii code
            push ecx
            push dword format
            call [printf]
            add esp, 4
            pop ecx

            ; get the base8 representation
            ; convert_base8(char* buffer, int num)
            push ecx
            push dword base8_buffer
            call convert_base8
            add esp, 4
            pop ecx

            ; printf(string_format, base8_buffer)
            push ecx
            push dword base8_buffer
            push dword string_format
            call [printf]
            add esp, 4 * 2

            pop ecx

            inc ecx
            jmp for_loop
    
        end_for:
        
    
        ; exit(0)
        push dword errors ;it will show us if we have any errors
        call [perror]
        add esp, 4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
