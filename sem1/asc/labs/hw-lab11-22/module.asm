;%ifndef _MODULE_ASM_ ; continue if _BASE8_ASM_ is undefined
;%define _MODULE_ASM_ ; make sure that it is defined
;                        ; otherwise, %include allows only one inclusionbits 32 ; assembling for the 32 bits architecture
;

;find the hundread placed digits of the numbers
;this part of the program will be moved in a different module after i finish with it


bits 32                         
segment code use32 public code
global module

extern nr
extern cnt
extern digits
extern s2
extern cnt2

;convert the hexa number in decimal
module:
    mov eax, dword[nr]
    mov dword[cnt], 0
    convert_to_ten:
        mov edx, 0
        mov bx, 10
        div bx              ;ax = quotient  dx = remainder
        
        mov ecx, 0
        mov cl, byte[cnt]
        mov [digits + ecx], dl     ;the remainders of the division are the digits of the number in base 10
        inc byte[cnt]
        
        cmp ax, 0           ;while we still have something to divide by 0
    jnz convert_to_ten
   
    
        ;we have 2 situations: either cnt < 3 or cnt >= 3 (means that we have a digit in the hundred place)
    
        mov al, byte[cnt]
        mov bl, 3
        cmp al, bl
        jb no_hundred_place
        jmp there_is_hundred_place
    
        
        no_hundred_place:
            mov edx, 0
            mov dl, byte[cnt2]
            mov byte[s2 + edx], 0
            inc byte[cnt2]
            
            ret
        
        there_is_hundred_place:
            mov ecx, 0
            mov cl, byte[digits + 2]        ;we store the digit in the hundred place
            mov edx, 0
            mov dl, byte[cnt2]
            mov [s2 + edx], cl
            inc byte[cnt2]
            
            ret
            ;jmp display_digits
            
            
;%endif