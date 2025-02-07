;Given the doubleword A and the word B, compute the word C as follows:
;the bits 0-4 of C are the invert of the bits 20-24 of A
;the bits 5-8 of C have the value 1
;the bits 9-12 of C are the same as the bits 12-15 of B
;the bits 13-15 of C are the same as the bits 7-9 of A

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
    a dd 1110_0101_1101_0001_1001_0110_1111_0100b ;E5D1 96F4h
    b dw 1010_1100_0001_0010b 
    c dw ;1011_0101_1110_0010b ;= B5E2h
    ; 11101 -> 00010 
    ; 12345 -> 54321
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov eax, 0
        mov eax, dword [a]
        not eax  ;we invert the value of A
        and eax, 0000_0001_1111_0000_0000_0000_0000_0000b   ;we isolate the bits 20-24 of A
        ror eax, 20   ;we rotate the bits 20 positions to the right   
        mov word [c], ax  ;we set the 0-4 bits   = 2h
        xor word [c], 0000_0001_1110_0000b   ;we set the 5-8 bits of C to 1 ->  0001_1110_0010  = 1E2h
        mov eax, 0
        mov ax, word [b]
        and ax, 1111_0000_0000_0000b  ;we isolate the bits 12-15 of B
        shr ax, 3  ;we shift the bits 3 position to the right
        xor word [c], ax  ;  0001_0101_1110_0010   = 15E2h
        mov eax, 0
        mov eax, dword [a]
        and eax, 0000_0000_0000_0000_0000_0011_1000_0000b  ;we isolate the bits 7-9 of A
        shl ax, 6  ;we shift the bits 6 position to the left
        xor word [c], ax
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
