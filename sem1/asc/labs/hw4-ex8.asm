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
    ;A character string S is given. Obtain the string D that contains all capital letters of the string S.
    ;Examples
    ;S: 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
    ;D: 'A', 'B', 'M'
    
    s db 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
    lens equ ($-s)  ;length of string s
    d db
    cnt resb 1  ;contor to store the characters on different bytes in d
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, 0
        mov byte [cnt], 1
        
        ;the loop instruction will be executed until ecx = lens
        repeat:
            ;to have an upper letter, this should be between 'A' and 'Z' 
            mov al, byte [s+ecx]
            cmp al, 'A'      ;compare if the actual character is >= A
            jae compare2     ;if the condition is respected then we check the second part as well
            jmp increment    ;else we should ignore the other instructions and jump directly to the incrementation step
            
        compare2:
            cmp al, 'Z'     ;compare if the character is <= Z
            jbe addchar     ;if the condition is respected we can add it in d
            jmp increment   ;else ignore the following instructions and jump directly to the incrementation step
            
        addchar:
            mov ebx, 0
            mov bl, byte [cnt]
            mov [d+ebx], al     ;formula de la 2 noaptea, move the character on the following available byte
            inc byte [cnt]      ;increment the contor
           
        increment:
            inc ecx
            cmp ecx, lens       ;compare to see if we riched the length of the s 
            jnz repeat
            
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
