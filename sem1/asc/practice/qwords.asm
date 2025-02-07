bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, fopen, fclose, fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

;7.	Se da un sir de qword definit in data segment. elementele sirului sunt in baza 16
;a)	sa se printeze bytes care compun qword urile din sir
;b) sa se identifice words care au ultima cifra egala cu constanta k definita in segmentul de date. sa se salveze aceste words in sirul d
;c)	sa se identifice dwords care sunt cuprinse in intervalul AAA - FFFF. sa se determine numarul dwords din acest interval. sa se afiseze acest numar in baza 10 in fisierul 'iesire.txt'

    sir dq 12_34_56_78_91_01_11_02h, 10_22_33_44_55_66_77_88h, 10_12_12_33_44_55_12_10h, 0h
    file db "iesire.txt", 0
    format_h db "%x", 0
    descriptor dd 0
    d times 100 dw 0
    space db " ", 0
    cnt dd 0
    i dd 0
    newline db 10
    k db 2h
    copy_word resw 1
    cnt1 dd 0
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        repeat_a:
            mov ecx, dword[i]   ;iteram printe qwordurile din sir
            mov eax, dword[sir + ecx * 4] ;mutam partea low dword in eax
            ;mov edx, dword[sir + ecx + 4] ;mutam partea high dword in edx
            
            cmp eax, 0  ;verificam daca am ajuns la ultima valoarea din sir -> stop
            je  check_0
            jmp continue
            
            check_0:
                mov edx, dword[sir + ecx * 4 + 4]   ;mutam partea high 
                cmp edx, 0
                je final
            
            continue:
                ;stosd   ;[edi] = eax
                mov ecx, 4
                ;while (ecx > 0)
                print_low:
                    mov ebx, 0
                    mov bl, al  ;tinem in bl pe rand bytes
                    
                    pusha   ;save the value from register -> in this case we are inerested in ecx
                    
                    push ebx        ;print the byte
                    push dword format_h
                    call [printf] 
                    add esp, 4 * 2
                    
                    push dword space
                    call [printf]
                    add esp, 4 
                    
                    popa    
                    
                    shr eax, 8  ;putem elimina byteul ca l-am afisat deja
                    
                    dec ecx
                    cmp ecx, 0
                    jne print_low
               
                inc dword[i]
                jmp repeat_a
                
        final:
        push dword newline
        call [printf]
        add esp, 4
        
        mov dword[i], 0
        mov edi, d
        repeat_b:
            ;22%10 = 2 => ultima cifra din numar e 2
            ;daca am ax = 22, bl = 10 => ah = 2 - remainder al = 2 - quotient
            mov ecx, dword[i]
            mov eax, 0
            mov ax, word[sir + ecx * 2]
            cmp eax, 0
            je check_end
            jmp continue1
           
            
            check_end:
                mov eax, 0
                mov ax, word[sir + ecx * 2 + 4]
                cmp eax, 0
                je dublu_check
                
                dublu_check:
                    mov eax, dword[sir + ecx * 4 + 4]
                    cmp eax, 0
                    je final_2
            
            continue1:
                mov word[copy_word], ax  ;we need to keep in mind the word
                
                mov bl, al
                mov eax, 0
                mov al, bl ;we are interested only in the last byte so scapam de restul
                
                mov bl, 16
                div bl
                
                mov dl, byte[k] ;compare to see if the last digit is k
                cmp ah, dl
                je add_in_d
                jmp continue2
                
                add_in_d:
                    mov eax, 0
                    mov ax, word[copy_word]
                    mov [edi], ax    ;we keep in d the word
                    add edi, 2
                    inc dword[cnt1]
                    
                    pusha 
                    push dword edi
                    push dword format_h
                    call [printf]
                    add esp, 4 * 2
                    
                    push newline
                    call [printf]
                    add esp, 4
                    popa
                 
                continue2:
                    inc dword[i]
                    jmp repeat_b
                
        final_2:
            mov esi, d
            mov ecx, dword[cnt1]
            jecxz final_print
            
            print_words:
                pusha
                lodsw
                
                push eax
                push dword format_h
                call [printf]
                add esp, 4 * 2
                
                push space
                call [printf]
                add esp, 4
                
                popa
                
                add esi, 2
                
                loop print_words
                
            final_print:
                
            
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
