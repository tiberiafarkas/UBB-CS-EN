;Given the words A and B, compute the byte C as follows:
;the bits 0-5 are the same as the bits 5-10 of A
;the bits 6-7 are the same as the bits 1-2 of B.
;Compute the doubleword D as follows:
;the bits 8-15 are the same as the bits of C
;the bits 0-7 are the same as the bits 8-15 of B
;the bits 24-31 are the same as the bits 0-7 of A
;the bits 16-23 are the same as the bits 8-15 of A

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
    a dw 1001_0101_0000_1101b
    b dw 0010_1100_0011_0001b
    c db  ;0010_1000 = 28h
    d dd  ;0000_1101_1001_0101_0010_1000_0010_1100b = D95282Ch

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov eax, 0
        mov ax, word [a]
        and ax, 0000_0111_1110_0000b ;isolate the bits 5-10 of A
        shr ax, 5 
        mov byte [c], al ;0->5 bits from C are the same as the 5->10 bits of A
        mov ebx, 0
        mov bx, word [b]
        and bx, 0000_0000_0000_0110b  ;isolate the bits 1-2 of B
        shr bx, 1
        mov byte [c+6], bl   ;0010_1000
        mov eax, 0
        mov al, byte [c]
        shl ax, 8
        mov word [d], ax  ;0->7 bits from C are the same as the 8->15 bits of D
        mov ebx, 0
        mov bx, word [b]
        shr bx, 8
        mov byte [d], bl ;8->15 bits from B are the same as the 0->7 bits of D 
        mov eax, 0
        mov ax, word [a]
        and ax, 0000_0000_1111_1111b  ;isolate the bits 0-7 of A
        shl eax, 24
        add eax, dword [d]
        mov dword [d], eax  ;0->7 bits from A are the same as the 24-31 bits of D
        mov eax, 0
        mov ax, word [a]
        and ax, 1111_1111_0000_0000b ;isolate the bits 8-15 of A
        shl eax, 8
        add eax, dword [d]  
        mov dword [d], eax  ;8->15 bits from A are the same as the 16->23 bits of D
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
