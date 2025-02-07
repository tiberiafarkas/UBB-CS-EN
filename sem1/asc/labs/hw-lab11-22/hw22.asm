bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
extern module             ;import the module
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

global number
global nr
global digits
global cnt
global s2
global cnt2
global digit
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;Read a string of integers s1 (represented on doublewords) in base 10. 
    ;Determine and display the string s2 composed by the digits in the hundreds place of each integer in the string s1.
    ;Example:    The string s1: 5892, 456, 33, 7, 245
    ;The string s2: 8,    4,   0,  0, 2

    question db "How many numbers do you want to introduce? (Must be more than 0!!)  ", 0
    format1 db "%d", 0
    message db "number = %d", 13, 10, 0
    message1 db "introduce a new number = ", 0
    message2 db "the number introduced is: %d", 13, 10, 0
    message3 db "the digit in the hundreads place is: %d", 13, 10, 0
    number resd 1
    nr db 0
    digits resq 2
    cnt resb 1
    s2 resq 1
    cnt2 resb 1
    digit db 0
    
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword question
        call [printf]
        add esi, 4
        
        push dword number       ;we read how many numbers to be introduced from the console
        push dword format1
        call [scanf]
        add esi, 4*2
        
        push dword[number]          ;we check the number has been read correctly
        push dword message
        call [printf]
        add esi, 4 * 2
        
        ;now we need to read the rest of the numbers
        ;while ecx > 0 
        
        mov ecx, dword[number]
        
    while_loop:
        mov dword[number], ecx      ;save the value of ecx because it will be changed because of the calls
        
        push dword message1
        call [printf]
        add esi, 4
        
        push dword nr           ;we read the numbers
        push dword format1
        call [scanf]
        add esi, 4*2
        
        push dword[nr]          ;print them to check if everything is alright
        push dword message2
        call [printf]
        add esi, 4*2
        
        ;find the hundread placed digits of the numbers
                
        call module
     
        ;turn to display the digits:
        
        display_digits:
            mov edx, 0
            mov dl, byte[cnt2]
            dec dl
            mov bl, byte[s2 + edx]
            mov byte[digit], bl
            push dword[digit]
            push dword message3
            call [printf]
            add esp, 4*2
            
        
        next:
            mov ecx, dword[number]      ;restore the value of ecx
            dec ecx
            mov ebx, 0
            cmp ecx, ebx
            jne while_loop
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
