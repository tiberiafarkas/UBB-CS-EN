bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import printf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s1 dq 7148_6534_1258_9622h, 8796_1145_8742_0142h, 6988_6974_6221_1420h
    len equ ($-s1)/8
    s2 resd len
    contor db 0
    voc db 'aeiouAEIOU'
    len2 equ ($-voc)
    contor_voc db 0
    format_w db "%d", 0
    
; our code starts here
segment code use32 class=code
    vocale:
        mov esi, [esp+4]    ;to take the offset of s2
        
        mov ecx, 0
        mov cl, byte[contor]
        
        repeat2:
            lodsd   ;eax <- esi
            ;shl
            mov bl, ah  ;keep only the high byte
            
            mov edi, voc        ;to go through the vocals
            
            push dword ecx     ;save the value of the contor register  
            mov ecx, len2
            
            loop1:
                mov al, byte[edi]   ;take each vocal
                
                cmp al, bl 
                jne next1
                
                inc byte[contor_voc]    ;if it is a voc increase the contor
                
                next1:
                    inc edi     ;go to the next vocal
                    loop loop1
            
            pop ecx     ;restore the value of ecx
            loop repeat2
        
        mov eax, 0
        mov al, byte[contor_voc]    ;the result will be returned in eax
        
        ret
        
    start:
        ; ...
        
        mov esi, s1 ;load the offset of s1 in esi
        mov edi, s2 ;load the offset of s2 in edi
        
        ;while len > 0
        mov ecx, len
        repeat:
            
            ;save the high doublewords
            mov eax, dword[esi+4]
            
            mov bx, ax   ;save the low word of the doubleword
            mov edx, eax
            shr edx, 16     ;shift eax with 16 bits to the right to remain only the high word, dx = high word 
            ;mov dx, ax ;save the high word of the doubleword
            
            cmp dx, bx          ;check if the high word is bigger than the low word in sign interpretation
            jg check_highbyte
            jle next
            
            check_highbyte:
                stosd  ;save the qword in s2
                       ;edi <- eax, edi += 4
                inc byte[contor]    ;to know how many word i have in s2
                
            next:
                add esi, 8  ;go to the next qword
                loop repeat
        
        push dword s2
        call vocale
        
        ;stack looks like
        ;   |________|
        ;   |_return_|  <- esp
        ;   |___s2___|  <- esp + 4
        ;   |________|
        
        push dword eax
        push dword format_w
        call [printf]
        add esp, 4 * 2
            
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
