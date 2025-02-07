bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
                  

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
    ;A natural number a (a: dword, defined in the data segment) is given. 
    ;Read a natural number b from the keyboard and calculate: a + a/b. 
    ;Display the result of this operation. The values will be displayed in decimal format (base 10) with sign.

    a dd 10
    b dw 0
    message db "b=", 0
    format db "%u", 0
    display_message db "%u + %u = %u", 0
    division_by_0 db "Error: Division by zero!", 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push dword message  ;print the message 'b=' 
        call [printf]
        add esp, 4
        
        push dword b        ;read the value of b
        push dword format
        call [scanf]
        add esp, 4 * 2 
        
        
        mov eax, dword[a]       ;load in eax the value of a
        
        xor edx, edx            ;be sure edx is 0 because you have to deal with a division of a dword to a word
        mov ebx, 0
        mov bx, word[b]         ;load in bx the value of b
        
        test bx, bx             ;test if we have a div by 0
        jz div_by_zero
        
        div bx                  ;compute the division
        
        mov ecx, eax            ;save in ecx the division
        
        add eax, dword[a]       ;add the value of a to the division
        
        push dword eax          ;display the message
        push dword ecx
        push dword[a]
        push dword display_message
        call [printf]
        add esp, 4*4
        jmp get_out
        
        div_by_zero:
            ; handle division by zero
            push dword division_by_0
            call [printf]
            add esp, 4
    
        ; exit(0)
        get_out:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
