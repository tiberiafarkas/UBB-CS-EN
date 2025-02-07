;It is given a number in base 2 represented on 32 bits. Write to the console the number in base 16. (use the quick conversion)


bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global _conversion        

; declare external functions needed by our program
;extern exit               ; tell nasm that exit exists even if we won't be defining it
;import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll

segment data public data use32

    hexa_digits db "0123456789ABCDEF", 0
    result db 9 dup(0), 0;buffer for the result
    ;the number on 32 bits can have at most 8 digits in base 16

segment code public code use32

_conversion:
    ;create a stack frame
    push ebp
    mov ebp, esp
 
    mov ecx, 8 ;contor for 8 digits
    lea esi, [hexa_digits]
    lea edi, [result + 7]   ;write from the end of the buffer
 
    conversion_loop:
        ; retreive the function's arguments from the stack
        ; [ebp+4] contains the return value 
        ; [ebp] contains the ebp value for the caller
        
        mov eax, [ebp+8]
        and eax, 0xF    ;we take the last 4 digits of the number (1 digit in hexa)
        mov bl, byte [esi + eax]
        mov byte[edi], bl   ;move the digit in buffer
        dec edi
        shr dword[ebp+8], 4     ;get rid of the last 4 digits of the number
        
        loop conversion_loop
        
        lea edi, [result]
        mov byte [result + 8], 0 ;null terminator
    
    
    ; the return value of the function should be in EAX
    mov eax, edi
    
    ; restore the stack frame
    mov esp, ebp
    pop ebp
    
    ret
    ; cdecl call convention - the caller will remove the parameters from the stack
