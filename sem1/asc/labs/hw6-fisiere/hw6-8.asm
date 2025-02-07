bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fscanf, fprintf, printf, perror               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll
import perror msvcrt

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    ;A file name and a decimal number (on 16 bits) are given (the decimal number is in the unsigned interpretation). 
    ;Create a file with the given name and write each digit composing the number on a different line to file.
    f dd 0
    g dd 0
    file1 db "in.txt", 0
    access_r db "r", 0
    n dd 0
    format_r db "%u", 0
    file2 db "out.txt", 0
    access_w db "w", 0
    format_w db "%c", 0
    digits resq 1
    cnt resd 1
    cnt1 resd 1
    digits1 resq 1
    digit db 0
    errors db "Error found", 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword access_r  ;we open the input file
        push dword file1
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0  ;in case the file doesn't exist
        jz get_out
        
        mov dword[f], eax   ;we read the number n from the file
        push dword n
        push dword format_r
        push dword[f]
        call [fscanf]
        add esp, 4 * 3
        
        push dword[f]   ;we close the input file
        call [fclose]
        add esp, 4
        
        mov eax, dword[n]
        
        repeat:
            mov edx, 0
            ;mov eax, dword[n]
            mov bx, 10
            div bx      ;ax = quotient, dx = remainder
            
            mov ecx, 0      ;add the remainder (which is the digit of the nr in base 10 in the digits array)
            mov cl, byte[cnt]
            mov [digits + ecx], dl
            inc byte[cnt]
            
            cmp ax, 0    ;while n > 0 
            jnz repeat 
        
        
        push dword access_w  ;we open the output file
        push dword file2
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        jz get_out
        
        mov dword[g], eax
        
        write_digits:
            dec byte[cnt]
            mov edx, 0
            mov dl, byte [cnt] ;get digit
            mov ecx, 0
            mov cl, byte[digits + edx]
            add cl, '0'           ; convert to ascii
            mov byte [digit], cl  ; store in digit buffer

            ; write digit 
            push dword[digit]
            push dword format_w
            push dword[g]
            call [fprintf]
            add esp, 4 * 3

            ; write newline character
            mov byte [digit], 10  ; ascii newline ('\n')
            push dword [digit]
            push dword format_w
            push dword [g]
            call [fprintf]
            add esp, 4 * 3

            mov eax, dword[cnt]
            cmp eax, 0
            jnz write_digits
                
        
        push dword[g]   ;we close the output file
        call [fclose]
        add esp, 4
    
    
        ; exit(0)
        get_out:
            push dword errors ;it will show us if we have any errors
            call [perror]
            add esp, 4
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
