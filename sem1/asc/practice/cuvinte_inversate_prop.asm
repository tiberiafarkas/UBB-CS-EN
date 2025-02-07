bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf, perror, gets               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import printf msvcrt.dll
import perror msvcrt.dll  
import gets msvcrt.dll                        

;3.	Se citeste o propozitie de la tastatura. Sa se inverseze fiecare cuvant si sa se afiseze pe ecran.                          
                          
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    format_rw db "%s", 0
    message db "introdu propozitia:", 10, 0
    source times 256 db 1 ;string to hold the sentence 
    destination times 256 db 1
    inv times 256 db 1
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
        
        mov esi, source
        mov edi, destination
        
        repeta:
            cmp byte[esi], 0 ;check if we reached the end
            je final
            
            cmp byte[esi], ' '; check if we reached a space between words
            je inverseaza
            jne keep_letter
            
            keep_letter:
                movsb   ;store in edi the character
                jmp repeta
                
            inverseaza:
                sub edi, 1 ;it was increased when we added the last letter
                mov eax, inv    ;we store the offset of the inv word in eax
                
                repeta1:
                    cmp edi, destination - 1; we check if the offset of edi got before the start address of destination -> it means that all the letters were stored
                    je end_repeta1
                    
                    mov bl, byte[edi]
                    mov byte[eax], bl
                    sub edi, 1  ;we go to the next letter
                    add eax, 1  ;store on the next position in eax
                    jmp repeta1
                    
                end_repeta1:
                    mov byte[eax], 0 ;reset
                    
                ;print the inverse word
                push dword inv
                push dword format_rw
                call [printf]
                add esp, 4 * 2
                
                push dword space
                call [printf]
                add esp, 4
                
                mov edi, destination ;we start again from the beggining of the destination offset not to have the current word
                add esi, 1
                jmp repeta
                
        final:
            ;the last word from the sentence remained to be switched
            sub edi, 1
            mov eax, inv
            
            repeta2:
                cmp edi, destination - 1
                je end_repeta2
                
                mov bl, byte[edi]
                mov byte[eax], bl
                sub edi, 1
                add eax, 1
                jmp repeta2
                
            end_repeta2:
                mov byte[eax], 0
                
            ;print the last word
            push dword inv
            push dword format_rw
            call [printf]
            add esp, 4 * 2
                
        
        ;call [perror]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
