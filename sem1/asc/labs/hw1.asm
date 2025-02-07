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
    ;section simple exercises
    ;128 + 127
    a db 128
    b db 127
    ;16/4
    c db 16
    d db 4
    
    ;section addition and substractions
    ;bytes
    ;(a+b-d)+(a-b-d)
    ;(a+b+b)-(c+d)
    
    ;words
    ;(b+c+d)-(a+a) -> i will use other variables -> (b1+c1+d1)-(a1+a1)
    a1 dw 350
    b1 dw 15
    c1 dw 475
    d1 dw 1754
    
    ;multiplications and divisions
    ;a2, b2, c2 bytes and d2 word
    ;(100*a+d+5-75*b)/(c-5)
    a2 db 113
    b2 db 100
    c2 db 78
    d2 dw 500
    
    ;[(10+d)-(a*a-2*b)]/c
    a3 db 12
    b3 db 100
    c3 db 75
    d3 dw 500
    
    ;a,b,c,d-byte, e,f,g,h-word
    ;2*(a4+b4)-e4
    a4 db 110
    b4 db 90
    e4 dw 300
    
    ;(a+(b-c))*3 - i'm gonna use the values of a4 and b4
    c4 db 50
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;makes the addition 127 + 128
        mov eax, 0
        mov ebx, 0
        mov al, BYTE [a]
        add al, BYTE [b]
        
        ;makes the division 16 / 4 and stores it in the ebx register
        mov eax, 0
        mov edx, 0
        mov al, BYTE [c]
        mov bl, BYTE [d]
        div bl
        mov bl, al
        
        ;(a+b-d)+(a-b-d) = a+b-d+a-b-d = a-d+a-d
        mov eax, 0
        mov ebx, 0
        mov al, BYTE [a]
        sub al, BYTE [d]
        ;adc ah, 0 ;if the operation exceeds 1 byte, then we add the carry flag in the next register to obtain the correct result
        add al, BYTE [a]
        sub al, BYTE [d]
        
        ;(a+b+b)-(c+d)
        mov eax, 0
        mov ebx, 0
        mov al, BYTE [a]
        add al, BYTE [b]
        add al, [b]
        adc ah, 0 
        mov bl, BYTE [c]
        add bl, BYTE [d]
        adc bh, 0
        sub ax, bx
        
        ;(b1+c1+d1)-(a1+a1)
        mov eax, 0
        mov ax, WORD [b1]
        add ax, WORD [c1]
        add ax, WORD [d1]
        sub ax, WORD [a1]
        sub ax, WORD [a1]
        
        ;(100*a2+d2+5-75*b2)/(c2-5)
        mov eax, 0
        mov ebx, 0
        mov edx, 0
        
        ;100*a2
        mov al, BYTE [a2]
        cbw
        mov ah, 100
        mul ah
        
        ;+d2+5
        add ax, WORD [d2]
        add al, 5
        
        mov bx, ax
        
        ;-75*b2
        mov eax, 0
        mov al, BYTE [b2]
        cbw
        mov ah, 75
        mul ah
        sub bx, ax
        
        
        ;c2 - 5
        mov al, BYTE [c2]
        sub al, 5
        cbw
        mov cx, ax
        
        ;division
        mov ax, bx
        div cx
        
        ;[(10+d3)-(a3*a3-2*b3)]/c2 = (10+d3-a3*a3+2*b3)/c3
        mov eax, 0
        mov ebx, 0
        mov ecx, 0
        mov edx, 0
        
        ;10+d3
        mov ax, WORD [d3]
        add ax, 10
        mov bx, ax
        
        ;a3*a3
        mov eax, 0
        mov al, BYTE [a3]
        cbw
        mov ah, BYTE [a3]
        mul ah
        mov cx, ax
        
        ;2*b3
        mov eax, 0
        mov al, BYTE [b3]
        cbw
        mov ah, 2
        mul ah
        
        ;+10+d3-a3*a3
        add ax, bx
        sub ax, cx
        
        ;/c3 ;aici se foloseste registrul dx
        mov dx, 0
        mov ebx, 0
        mov bl, BYTE [c3]
        mov bh, 0
        div bx
        
        ;2*(a4+b4)-e4
        mov eax, 0
        mov al, BYTE [a4]
        add al, BYTE [b4]
        mov ah, 2
        mul ah
        sub ax, WORD [e4]
        
        ;(a4+(b4-c4))*3
        mov eax, 0
        mov al, BYTE [b4]
        sub al, BYTE [c4]
        add al, BYTE [a4]
        mov ah, 3
        mul ah
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
