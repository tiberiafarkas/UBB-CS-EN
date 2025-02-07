bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf, fopen, fclose, fscanf, fprintf            
import exit msvcrt.dll     
import printf msvcrt.dll     ; indicating to the assembler that the printf fct can be found in the msvcrt.dll library
import scanf msvcrt.dll      ; similar for scanf
import fscanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll


; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
    ;exemplul 1:
    ;a dd 10
    ;b dd 20
    ;message db '%d + %d = %d', 0

    ;exemplul 2:
    ;a dd 0
    ;b dd 0
    ;format db '%d %d', 0
    
    f dd 0
    g dd 0
    file1 db "in.txt.txt", 0
    access_r db "r", 0
    a dd 0
    b dd 0
    format_r db "%d %d", 0
    file2 db "out.txt", 0
    access_w db "w", 0
    format_w db "%d", 0
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push dword access_r
        push dword file1
        call [fopen]
        add esp, 4*2
        cmp eax, 0
        jz out
        mov dword[f], eax
        push dword b
        push dword a
        push dword format_r
        push dword[f]
        call [fscanf]
        add esp, 4*4
        push dword[f]
        call [fclose]
        add esp, 4
        push dword access_w
        push dword file2
        call [fopen]
        add esp, 4*2
        cmp eax, 0
        jz out
        mov dword[g], eax
        mov eax, dword[a]
        add eax, dword[b]
        push eax
        push dword format_w
        push dword [g]
        call [fprintf]
        add esp, 4*3
        push dword[g]
        call [fclose]
        add esp, 4
        
        out:
            push 0
            call [exit]
        
        ;teoretic exemplul 2 practic NU-MI CITESTE NIMIC
        ;push dword b
        ;push dword a
        ;push dword format
        ;call [scanf]
        ;add esp, 4*3
        ;
        ;mov eax, [a]
        ;add eax, [b]
        ;push eax
        ;push dword[a]
        ;push dword[b]
        ;push dword message
        ;call [printf]
        ;add esp, 4*4
        
        
        
        ;exemplul 1:
        ;mov eax, [a]
        ;add eax, [b]
        ;push eax,
        ;push dword[b]
        ;push dword[a]
        ;push dword message
        ;call [printf]
        ;add esp, 4*4
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
