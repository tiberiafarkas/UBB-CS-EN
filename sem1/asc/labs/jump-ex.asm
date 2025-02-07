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

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al,200 ; AL = C8h
        mov bl,100
        cmp al, bl ; fictive subtraction al-bl and set flangs 
        ; accordingly (in our case this means SF=0, OF=1, CF=0 şi ZF=0)
        JB et2 ;the conditional jump statement establishes the comparison criterion, in this case Jump if Below - comparison for unsigned numbers (is 200 below 100?) and test CF content: if CF = 1 the jump will be performed, if CF = 0 NO jump will be done. 
        ;In our case CF=0, so the jump will not be performed.
        ;............. ;instructions set
        et2:
        ;............. ;instructions set after this label
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
