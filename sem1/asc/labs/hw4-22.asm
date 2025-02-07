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
    ;Two byte strings S1 and S2 of the same length are given. 
    ;Obtain the string D where each element contains the minimum of the corresponding elements from S1 and S2.
    ;Example:
    ;S1: 1, 3, 6, 2, 3, 7
    ;S2: 6, 3, 8, 1, 2, 5
    ;D: 1, 3, 6, 1, 2, 5
    
    s1 db 1, 3, 6, 2, 3, 7
    lens equ ($-s1)     ;length of the strings
    s2 db 6, 3, 8, 1, 2, 5
    d db
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov ecx, 0
        
        repeat:
            mov al, byte [s1+ecx]
            mov bl, byte [s2+ecx]
            cmp al, bl      ;compare the elements on the same position from the 2 strings
            jbe add_elem_s1     ;if the element from the first string is smaller, then we add it in d
            jmp add_elem_s2     ;else we add the element from the second string
            
        add_elem_s1:
            mov [d+ecx], al
            jmp increment       ;we jump directly to incrementation so the element from the second string is not added in d 
            
        add_elem_s2:
            mov [d+ecx], bl
            
        increment:
            inc ecx
            cmp ecx, lens       ;compare to see if we riched the length of the strings
            jnz repeat
            
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
