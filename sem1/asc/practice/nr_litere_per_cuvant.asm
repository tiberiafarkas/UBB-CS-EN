bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, gets               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import gets msvcrt.dll

;4.	Se citeste o propozitie de la tastatura. Sa se numere literele din fiecare cuvant si sa se afiseze aceste numere pe ecran.                          
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
    destination times 100 db 0
    source times 100 db 0
    format_w db "%d", 0
    message db "introdu propozitia:", 10, 0
    counter db 0
    space db " ", 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push dword message
        call [printf]
        add esp, 4
        
        ;read the sentence
        push dword source
        call [gets]
        add esp, 4
        
        mov esi, source ;store the offset of the text in esi
        mov edi, destination
        mov ecx, 0
        
        repeat:
            cmp byte[esi], 0  ;it means we reached the end
            je final
            
            cmp byte[esi], ' '    ;we iterate over a word
            jne count_letter
            je print_counter
            
            count_letter:
                inc ecx
                add esi, 1
                jmp repeat
                
            print_counter:
                push dword ecx
                push dword format_w
                call [printf]
                add esp, 4 * 2
                
                ;print space 
                push dword space
                call [printf]
                add esp, 4
                
                mov ecx, 0 ;reinitialize the counter to 0 for the next word
                
                add esi, 1
                jmp repeat
                
        final:
            push dword ecx
            push dword format_w
            call [printf]
            add esp, 4 * 2
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
