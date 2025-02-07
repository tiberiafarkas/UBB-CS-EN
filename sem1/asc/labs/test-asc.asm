bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 3, -6, 9, -7, 2, 3, -10
    lena equ ($-a)
    b db 5, 7, 2, 4, 2, 3, 9
    lenb equ ($-b)
    cnt resb 1
    r resq 1

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, lena
        mov esi, b
        std
        lodsb
        mov ecx, lena
        repeat:
            lodsb
            mov bl, 0xFF
            cmp al, bl
            jbe add_char
            jmp increment
            
        add_char:
            mov edx, 0
            mov dl, byte[cnt]
            mov [r+edx], al
            inc byte[cnt]
            
        increment:
            loop repeat
            
        mov esi, b
        cld
        mov ecx, lenb
        repeat2:
            lodsb
            mov ah, 0
            mov bl, 2
            div bl
            mov edx, 0
            mov dl, byte[cnt]
            mov [r+edx], ah
            inc byte[cnt]
            loop repeat2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
