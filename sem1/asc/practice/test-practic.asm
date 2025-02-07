bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

;Se da un fisier cuvinte.txt care contine cuvinte separate prin spatii.
;Sa se determine si sa se afiseze pe ecran numarul de cuvinte care au lungimea (numarul de caractere din fiecare cuvant) egala cu o valoare L citita de la tasatura.


; declare external functions needed by our program
extern exit, scanf, printf, fscanf, fprintf, fopen, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fscanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
    file db "cuvinte.txt", 0
    access_r db "r", 0
    format_rw db "%d", 0
    format_r_file db "%c", 0
    descriptor dd 0
    l dd 0
    cnt dd 0
    message db "L = ", 0
    message1 db "cuvinte care au lungimea %d: ", 0
    chr times 100 db 0
    cnt_bun dd 0
  

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;citim numarul l
        push message
        call [printf]
        add esp, 4
        
        push dword l
        push dword format_rw
        call [scanf]
        add esp, 4 * 2
        
        ;deschidem fisierul
        push dword access_r
        push dword file
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0      ;inseamna ca nu s-a putut deschide fisierul
        je get_out
    
        mov dword[descriptor], eax
        
        ;acum rezolvam problema
             
        repeta:
            ;fscanf(descriptor, format, variabile)
            push dword chr  ;citim pe rand caracterele din cuvant
            push dword format_r_file
            push dword[descriptor]
            call [fscanf]
            add esp, 4 * 3
            
            cmp eax, -1 ;inseamna ca nu a mai avut ce sa citeasca => am citit tot din fisier
            je final_repeta
            
            mov al, byte[chr]
            cmp al, ' '     ;am ajuns la un spatiu deci trebuie sa verificam numarul de caractere ale cuvantului
            je verifica
            
            inc dword[cnt]  ;crestem contorul de caractere dintr-un cuvant
            
            jmp repeta
            
            verifica:
                mov eax, dword[l]
                mov ebx, dword[cnt]
                cmp eax, ebx    ;verificam daca nr de caractere ale cuvantului e egal cu l
                je cuvant_bun
                jmp final_verifica
                
                cuvant_bun:
                    inc dword[cnt_bun]  ;crestem contorul de cuvinte de lungime l
                    
                final_verifica:
                    mov dword[cnt], 0   ;reinitializam contorul pentru urmatorul cuvant
                    jmp repeta
                
                       
        final_repeta:
            ;printam cate cuvinte au l litere
            push dword[l]
            push dword message1
            call [printf]
            add esp, 4 * 2
            
            push dword [cnt_bun]
            push dword format_rw
            call [printf]
            add esp, 4 * 2
        
        ;inchidem fisierul
        push dword[descriptor]
        call [fclose]
        add esp, 4
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
        
        get_out:    ;nu s-a deschis fisierul dam return 1
            push dword 1
            call [exit] 
