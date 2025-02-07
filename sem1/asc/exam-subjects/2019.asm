bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s1 dd 12345678h, 99663225h, 15250211h
    len_s1 equ ($-s1)/4
    s2 resw len_s1 
    cnt dd 0
    format_w dd "%d", 0
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov esi, s1     ;mov in esi the offset of s1 to can parse the string
        mov edi, s2
        
        mov ecx, len_s1     ;contor
        cld             ;make sure df = 0
        

        loop1:
            lodsd       ;eax <- [esi], esi += 4
            
            ;| high byte high word || low byte high word || high byte low word || low byte low word|  
            
            shr eax, 8 ;shift with 8 bytes such that now in al = high byte of the low word of the initial number
            
            ;|__________|| high byte high word || low byte high word || high byte low word | 
            
            stosb       ;edi <- [al]
            shr eax, 16 ;shift with 16 bytes to remain only the high byte of the high word in al
            
            ;|_________||_______|| _____ || high byte low word| 

            stosb       ;edi <- [al]
            loop loop1
            
            
        mov esi, s2
        mov ecx, len_s1
        
        cld
        loop2:
            lodsw   ;ax<-[esi], esi += 2
            
            count_1:
                clc
                shr ax, 1
                
                jnc next    ;if the bit is 0 jump over
                inc byte[cnt]
                
                next:
                    cmp ax, 0
                    jne count_1
            
            loop loop2
                        
        push dword [cnt]
        push dword format_w
        call [printf]
        add esp, 4 * 2
                
        
            
            
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
