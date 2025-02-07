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
    ;A string of bytes 'input' is given together with two additional strings of N bytes each, 'src' and 'dst'. Obtain a new string of bytes called 'output' from the 'input' string, by replacing all the bytes with the value src[i] with the new value dst[i], for i=1..N.

    input db 'phone'
    lena equ ($-input)  ;length of the input string
    src db 'poe'
    lens equ ($-src)    ;length of the src and dst strings (consider it > 0)
    dst db 'tik'
    output resq 1
    copy_ecx resw 1
    character resb 1
    char_dst resb 1
    cnt_src resb 1
    cnt resb 1
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov esi, input
        mov ecx, lena
        cld
        
        repeat:
            mov ebx, esi        ;save the value from esi
            lodsb               ;al <- [esi]  = input string
            mov byte[character], al     ;keep the current character
            mov byte[copy_ecx], cl      ;save the contor of ecx for the moment
            jmp find_in_src
            jmp add_character
            
        find_in_src:        ;search the character from the input string in src string
            mov esi, src
            mov ecx, lens
            mov byte[cnt_src], 0
            
            repeat2:
                lodsb           ;al <- [esi] = src string
                mov dl, byte[character]
                cmp al, dl      ;check if the character from the input string is in src string
                je add_character
                inc byte[cnt_src]
                
            loop repeat2        ;while ecx > 0
            mov edx, 0          ;it means that the character wasnt found in the src string
            mov dl, byte[cnt]   ;and we add to the output string the initial character
            mov al, byte[input + edx]
            jmp direct
                
        add_character:
            mov edx, 0
            mov dl, byte[cnt_src]
            mov al, byte[dst + edx]     ;we add in output the character from the destination string from the cnt_src position
            jmp direct
            
        direct:
            mov dl, byte[cnt]
            mov byte[output + edx], al      ;in al we have stored the correct character no matter if this is from dst or input string 
            inc byte[cnt]
            jmp increment
            
        increment:
            mov esi, ebx                ;we need to restore the value of esi and ecx such that our loop is still working correctly
            lodsb                       ;we need to pass to the next character in the input
            mov ecx, 0
            mov cl, byte[copy_ecx]
            loop repeat
              
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
