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
    ;a - byte, b - word, c - double word, d - qword - Unsigned representation
    ;(a+b-d)+(a-b-d)
    a db 30
    b dw 70
    c dd 100
    d dq 20
    rez resq 1
    
    ;(d+c) - (c+b) - (b+a) 
    a0 db 10
    b0 dw 20
    c0 dd 100
    d0 dq 200
    rez0 resq 1 
    
    ;a - byte, b - word, c - double word, d - qword - Signed representation
    ;(b+c+d)-(a+a)
    a1 db -10
    b1 dw 10
    c1 dd 20
    d1 dq -5
    rez1 resq 1
    
    ;c+b-(a-d+b) = 32h -> 50h -> 5Ah -> 46h -> 28h
    a10 db -10
    b10 dw 30
    c10 dd 50
    d10 dq -20
    rez10 resq 1
    

    ;1/a+200*b-c/(d+1)+x/a-e; a,b-word; c,d-byte; e-doubleword; x-qword
    a2 dw 10
    b2 dw 100
    c2 db 20
    d2 db 3
    x dq 100
    e dd -50
    
    ;a/2+b*b-a*b*c+e+x; a,b,c-byte; e-doubleword; x-qword - unsigned representation
    a3 db 10
    b3 db -5
    c3 db 2
    e1 dd -20
    x1 dq 100
    rez3 resq 1

    ;a/2+b*b-a*b*c+e+x; a,b,c-byte; e-doubleword; x-qword - signed representation
    a4 db 10
    b4 db 100
    c4 db 2
    e4 dd 500
    x4 dq 1000
    rez4 resq 1


; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;(a+b-d)+(a-b-d)
        mov eax, 0
        mov al, byte [a]
        add ax, word [b] ;ax=a+b
        adc ax, 0
        mov edx, 0 ; edx:eax = higher part of a+b
        sub eax, dword [d]
        ;if signed
        ;sub edx, dword [d+4] - substract the higher part of qword from edx register
        add al, byte [a]
        adc ax, 0
        sub ax, word [b]
        sub eax, dword [d]
        mov dword [rez], eax  ;it will store the lowest part of the value
        mov dword [rez+4], edx ;it will store the highest part of the value
        
        ;(d+c) - (c+b) - (b+a) 
        mov eax, 0
        mov eax, dword [d0]
        mov edx, 0
        mov edx, dword [d0+4]
        add eax, dword [c0]
        adc edx, 0
        sub eax, dword [c0]
        sbb edx, 0
        sub ax, word [b0]
        sbb eax, 0
        sbb edx, 0
        sub ax, word [b0]
        sbb eax, 0
        sbb edx, 0
        sub al, byte [a0]
        sbb ax, 0
        mov dword [rez0], eax
        mov dword [rez0+4], edx
        
        ;(b+c+d)-(a+a)
        mov eax, 0
        mov ax, word [b1]
        cwde
        add eax, dword [c1]
        mov edx, 0
        add eax, dword [d1]
        add edx, dword [d1+4]
        sub al, byte [a1]
        sub al, byte [a1]
        mov dword [rez1], eax
        mov dword [rez1+4], edx
        
        ;c+b-(a-d+b)
        mov eax, 0
        mov eax, dword [c10]
        add ax, word [b10]
        adc eax, 0
        sub al, byte [a10]
        add eax, dword [d10]
        mov edx, 0
        adc edx, dword [d10+4]
        sub ax, word [b10]
        sbb eax, 0
        mov dword [rez10], eax
        mov dword [rez10+4], edx
        
        
        ;1/a+200*b-c/(d+1)+x/a-e; a,b-word; c,d-byte; e-doubleword; x-qword
        mov eax, 0
        ;1/a2
        mov al, 1
        cbw
        cwd
        ;mov ebx, 0
        mov bx, word [a2]
        idiv bx
        mov ecx, 0
        mov ecx, eax
        ;mov eax, 0
        ;200*b2
        mov ax, word[b2]
        mov bx, 200
        mul bx
        ;1/a2+200*b2
        add cx, ax
        adc ecx, 0
        ;c2/(d2+1)
        add byte [d2], 1
        mov al, byte [c2]
        cbw
        idiv byte [d2]
        ;1/a2+200*b2-c2/(d2+1)
        sub cl, al
        ;x/a
        mov eax, dword [x]
        ;mov edx, 0
        mov edx, dword [x+4]
        idiv word [a2]
        ;x/a-e
        sub eax, dword [e]
        ;1/a1+200*b2-c2/(d2+1)+x/a-e
        add eax, ecx
        
        
        ;a/2+b*b-a*b*c+e+x; a,b,c-byte; e-doubleword; x-qword - unsigned representation
        ;a/2
        mov eax, 0
        mov al, byte [a3]
        cbw
        mov bl, 2
        idiv bl
        mov ebx, 0
        mov bl, al
        ;b*b
        mov eax, 0
        mov al, byte [b3]
        imul byte [b3]
        ;a/2+b*b
        add bx, ax
        mov eax, 0
        ;a*b*c
        mov al, byte [a3]
        imul byte [b3]
        mov edx, 0
        mov dl, byte [b3]
        cbw
        imul dx
        ;a2+b*b-a*b*c
        sub bx, ax
        ;x+e
        mov eax, dword [x1]
        mov edx, dword [x1+4]
        add eax, dword [e1]
        adc edx, 0
        ;a/2+b*b-a*b*c+e+x
        add ax, bx
        adc eax, 0
        mov dword [rez3], eax
        mov dword [rez3+4], edx

        
        ;a/2+b*b-a*b*c+e+x; a,b,c-byte; e-doubleword; x-qword - signed representation
        mov eax, 0
        mov edx, 0
        mov ebx, 0
        ;a/2
        mov al, byte [a4]
        cbw
        mov bl, 2
        div bl
        mov ebx, 0
        mov bl, al
        ;b*b
        mov eax, 0
        mov al, byte [b4]
        mul byte [b4]
        mov bh, 0
        ;a/2+b*b
        add bx, ax
        ;a*b*c
        mov al, byte [a3]
        mul byte [b3]
        mov edx, 0
        mov dl, byte [b3]
        cbw
        mul dx
        ;a/2+b*b-a*b*c
        sub bx, ax
        ;x+e
        mov eax, 0
        mov eax, dword [x4]
        mov edx, dword [x4+4]
        add eax, dword [e4]
        adc edx, 0
        ;a/2+b*b-a*b*c+e+x
        add ax, bx
        adc eax, 0
        mov dword [rez4], eax
        mov dword [rez4+4], edx
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
