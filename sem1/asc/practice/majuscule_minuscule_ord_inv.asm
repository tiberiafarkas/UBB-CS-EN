bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fprintf, fopen, fclose, printf, gets               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import gets msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;8.	Citesc string tastatura, creem fisier string.txt, adaugam in fisier prima data majusculele apoi minusculele invers de cum apar in sir.

                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
    source times 100 db 0
    db 0
    small_letters times 100 db 0
    db 0
    cnt_small db 0
    capital_letters times 100 db 0
    db 0
    cnt_capital db 0
    format_w db "%s", 10, 0
    access_mode db "w", 0
    file db "string.txt", 0
    file_ptr dd 0
    message db "introdu string:", 10, 0
    cpy dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push dword message
        call [printf]
        add esp, 4
        
        ;read the string
        push dword source
        call [gets]
        add esp, 4
        
        ;open the output file
        push dword access_mode
        push dword file
        call [fopen]
        add esp, 4 * 2
        
        mov dword[file_ptr], eax   
        
        mov esi, source
        mov edi, small_letters + 100 - 1 ;we start from the end to the beggining
        mov ebx, capital_letters
        
        repeat:
            cmp byte[esi], 0 ;it means we reached the end of the string
            je final
            
            cmp byte[esi], 'a'
            jb check_majuscule
            ;check if there are other characters after z
            cmp byte[esi], 'z'
            ja next
            
            jmp minuscule ;we pass the check
           
            check_majuscule:
                cmp byte[esi], 'A'
                jb next     ;it means we have other characters but not letters
                
                cmp byte[esi], 'Z'
                ja next
          
            ;if we got here it means we have letters
            majuscule:
                mov al, byte[esi]
                mov byte[ebx], al   ;store the capital letter
                add ebx, 1
                jmp next
                ;inc byte[cnt_capital]
                
            minuscule:
                ;we keep the small letters in a string and we iterate through it at the end starting from right to left
                ;load in edi the letters
                mov al, byte[esi]
                mov byte[edi], al
                sub edi, 1
                jmp next
                ;inc byte[cnt_small]
                
            next:
                add esi, 1
                jmp repeat
                
        final:
        
            push dword capital_letters
            push dword format_w
            push dword [file_ptr]
            call [fprintf]
            add esp, 4 * 2

            ; printf(newline)
            ;push dword newline
            ;call [printf]
            ;add esp, 4

            ; vom scrie sirul de minuscule, trb sa ajungem pana la primul caracter diferit de 0, care prin coincidenta e edi + 1
            lea ebx, [edi + 1]

            ; printf(ebx)
            push dword ebx
            push dword format_w
            push dword[file_ptr]
            call [fprintf]
            add esp, 4 * 2
        
            ;std  ;we set the direction flag to print the small letters from left to right
            ;mov ecx, 0
            ;mov ebx, capital_letters
            ;repeat1:
            ;    cmp cl, byte[cnt_capital] ;we pass through all the letters
            ;    je repeat2
            ;    
            ;    mov eax, 0
            ;    mov al, byte[ebx+ecx]
            ;    
            ;    mov dword[cpy], ecx  ;keep in mind the value of ecx
            ;    
            ;    push dword eax
            ;    push dword format_w
            ;    push dword [file_ptr]
            ;    call [fprintf]
            ;    add esp, 4 * 3
            ;    
            ;    mov ecx, dword[cpy]
            ;    inc ecx
            ;    jmp repeat1
                
            ;mov ecx, 0
            ;mov cl, byte[cnt_small]
            ;mov edi, small_letters
            ;repeat2:
            ;    cmp ecx, 0  ;it means we pass through all our letters
            ;    je get_out
            ;    
            ;    mov eax, 0
            ;    mov al, byte[edi+ecx-1]
            ;    
            ;    mov dword[cpy], ecx
            ;    
            ;    push dword eax
            ;    push dword format_w
            ;    ;push dword [file_ptr]
            ;    call [printf]
            ;    add esp, 4 * 2
            ;    
            ;    mov ecx, dword[cpy]
            ;    dec ecx
            ;    jmp repeat2
               
        
        get_out:
            ;we need to close the file
            push dword [file_ptr]
            call [fclose]
            add esp, 4
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
