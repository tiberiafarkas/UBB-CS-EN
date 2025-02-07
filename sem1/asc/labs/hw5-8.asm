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
    ;A list of doublewords is given. Obtain the list made out of the low bytes of the high words of each doubleword from the given list with the property that these bytes are palindromes in base 10.
    ;Given the string of doublewords:
    ;s DD 12345678h, 1A2C3C4Dh, 98FCDC76h
    ;obtain the string of bytes:
    ;d DB 2Ch, FCh.
    
    ;   7  6  5  4   3  2  1  0
    ;  -------------------------
    ;  |  |  |  |  |  |  |  |  | 
    ;  -------------------------
    ;  ------------------   AL
    ;  -------------  AH -------
    ;  ------------      AX
    ;  ------------   LOW WORDS
    ;   HIGH WORDS -------------
    ; 
    ;  => 4 & 5 the low bytes of the high words of the dword
    
    s dd 12345678h, 1A2C3C4Dh, 98FCDC76h
    lens equ ($-s)/4
    d resd 1
    ten db 10
    digit1 db 0
    digit2 db 0
    digit3 dw 0
    cnt resq 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov esi, s  ;store the far address of the string s
        mov ecx, lens
        cld
        
        repeat:
            lodsd ;eax = s[1], s[2], s[3]
            shr eax, 16  ;we are interested only in the high word
            mov ah, 0   ;we also need only the low byte
            
            mov bl, al    ;we keep the value of the low byte
            div byte[ten]  ;we divide the low byte by 10 to get the digits of the number, if x = 34, we will have ah = 4 and al = 3 
            mov byte[digit1], ah      ;digit1 = the first remainder, the first digit
            
            mov dl, byte[ten]
            cmp al, dl     ;check if the quotient of the division is >= 10
            jae divide     ;it means we still have 2 digits to compute for the nr in ten base
            mov byte[digit2], al  ;our nr in base ten has only 2 digits so we can compare those 2
            jmp compare1     
            
        divide:
            mov ah, 0   ;put ah on 0 cause otherwise we might get a wrong division
            div byte[ten]   ;divide to get the digits
            mov byte[digit2], ah  ;digit2 = the second remainder, the middle digit
            mov byte[digit3], al    ;digit3 = the last remainder, the last digit
            jmp compare2
            
        compare1:
            mov al, byte[digit1]
            mov dl, byte[digit2]
            cmp al, dl
            je add_number
            jmp increment
            
        compare2:
            mov al, byte[digit1]
            mov dl, byte[digit3]
            cmp al, dl  
            je add_number
            jmp increment
            
        add_number:
            mov edx, 0
            mov dl, byte[cnt]
            mov [d+edx], bl        ;move the number on the next available byte
            inc byte[cnt]          ;increase the contor
            
        increment:
            loop repeat     ;while ecx > 0
            
            
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
