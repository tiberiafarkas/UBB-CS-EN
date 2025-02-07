bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fscanf, printf, fopen, fclose
import fscanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;6.	Se citesc din fisierul numere.txt mai multe numere (pare si impare). Sa se creeze 2 siruri rezultat N si P astfel: N - doar numere impare si P - doar numere pare. Afisati cele 2 siruri rezultate pe ecran.                          
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    file db "numere.txt", 0
    access_r db "r", 0
    format_rw db "%d", 10, 0
    pare times 100 dd 0
    impare times 100 dd 0
    descriptor dd 0
    n dd 0
    cnt1 dd 0
    cnt2 dd 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        ;open the input file
        push dword access_r
        push dword file
        call [fopen]
        add esp, 4 * 2
        
        mov dword[descriptor], eax
        
        mov esi, pare
        mov edi, impare
        
        repeat:
            ;read the numbers
            push dword n
            push dword format_rw
            push dword[descriptor]
            call [fscanf]
            add esp, 4 * 3
            
            cmp eax, -1  ;the function returns -1 if it doesn't have something remained to read from the file
            je out_read
            
            ;check parity of the numbers
            mov eax, dword[n]
            parity:
                mov bx, 2
                mov edx, 0 
                ;ax/dx: ax = quotient, dx = remainder
                
                div bx
                
                ;if dx = 0 => even number
                cmp edx, 0
                je even_numbers
                jmp odd_numbers
            
            even_numbers:
                mov ecx, dword[cnt1]
                mov eax, dword[n]
                mov [esi+ecx*4], eax
                inc byte[cnt1]
                jmp repeat
                
            odd_numbers:
                mov ecx, dword[cnt2]
                mov eax, dword[n]
                mov [edi+ecx*4], eax
                inc byte[cnt2]
                jmp repeat
                
        out_read:
            ;we need to close the file
            push dword [descriptor]
            call [fclose]
            add esp, 4
        
            ;we mush check the last number read
            mov eax, dword[n]
            
            parity2:
                mov bx, 2
                mov edx, 0
                
                div bx
                
                cmp edx, 0
                je even_numbers2
                jmp odd_numbers2
            
            even_numbers2:
                mov ecx, dword[cnt1]
                mov eax, dword[n]
                mov [esi+ecx*4], eax
                
            odd_numbers2:
                mov ecx, dword[cnt2]
                mov eax, dword[n]
                mov [edi+ecx*4], eax
         
                
        printeaza_pare:

            mov esi, pare
            mov ecx, dword [cnt1]
            jecxz .pare_end_loop
            .pare_loop:
                lodsd

                pusha
                ; printf("d", eax)
                push eax
                push dword format_rw
                call [printf]
                add esp, 4 * 2

                popa

                loop .pare_loop


            .pare_end_loop:
        
         printeaza_impare:
            ; printf(pare_text)

            mov esi, impare
            mov ecx, dword [cnt2]
            jecxz .impare_end_loop
            .impare_loop:
                lodsd

                pusha
                ; printf("d", eax)
                push eax
                push dword format_rw
                call [printf]
                add esp, 4 * 2
                popa

                loop .impare_loop


            .impare_end_loop:

            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
