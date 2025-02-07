bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, gets, printf
import gets msvcrt.dll
import printf msvcrt.dll               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;5.	Se citeste de la tastatura un sir de caractere (litere mici si litere mari, cifre, caractere speciale, etc). Sa se formeze un sir nou doar cu literele mici si un sir nou doar cu literele mari. Sa se afiseze cele 2 siruri rezultate pe ecran.                          
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

    source times 100 db 0
    db 0
    small_letters times 100 db 0
    db 0
    capital_letters times 100 db 0
    db 0
    format_rw db "%s", 10, 0
    message db "introdu text: ", 10, 0
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push dword message
        call [printf]
        add esp, 4
        
        push dword source   ;read the text
        call [gets]
        add esp, 4
        
        mov esi, source
        mov edi, small_letters
        mov ebx, capital_letters
        
        repeat:
            cmp byte[esi], 0 ;we reached the end of the text
            je final
            
            cmp byte[esi], 'a' 
            jb check_capitals
            
            cmp byte[esi], 'z'
            je next
            
            jmp small_let   ;if we reached here we have to deal with small letters
            
            check_capitals:
                cmp byte[esi], 'A'
                jb next
                
                cmp byte[esi], 'Z'
                ja next
                
                capitals:
                    mov eax, 0
                    mov al, byte[esi]
                    mov byte[ebx], al   ;we add the letter in the capital_letters sequence
                    
                    add ebx, 1
                    jmp next
                    
            small_let:
                mov eax, 0
                mov al, byte[esi]
                mov byte[edi], al   ;we add the letter in the small_letters sequence
                
                add edi, 1
                jmp next
                    
            next:
                add esi, 1
                jmp repeat
                
        final:            
            ;print the 2 sequences
            push dword small_letters
            push dword format_rw
            call [printf]
            add esp, 4 * 2
            
            push dword capital_letters
            push dword format_rw
            call [printf]
            add esp, 4 * 2
        
                    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
