bits 32                ; Assemble for a 32-bit architecture

global start

extern exit, fopen, fclose, fscanf, printf, perror
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
import perror msvcrt.dll

section .data
    file_name db "input.txt", 0       ; Input file name
    read_mode db "r", 0               ; Read mode for fopen
    format_in db "%x", 0              ; Format string for reading integers
    format_out db "Minim digit of the number: %d", 10, 0 ; Format string for printing integers (with newline)
    error_msg db "Error: ", 0         ; Error message prefix
    file_ptr resd 1                   ; File pointer (for fopen)
    number resd 1                     ; Buffer to store each number
    min_dig resd 1
    cpy dd 0

section .code
    start:
        ; Open the file
        push dword read_mode              ; Push mode string
        push dword file_name              ; Push file name
        call [fopen]                        ; Call fopen
        add esp, 4 * 2                       ; Clean up the stack
        
        test eax, eax                     ; Check if fopen returned NULL (error)
        jz case_error                     ; Jump if the file couldn't be opened
        
        mov [file_ptr], eax               ; Store the file pointer

        ; Loop to read and print 10 numbers
        mov ecx, 10                       ; Loop counter (read 10 numbers)
        read_loop:
            mov dword[cpy], ecx

            push dword number                 ; Push address of buffer for fscanf
            push dword format_in              ; Push format string for fscanf
            push dword [file_ptr]                          ; Push file pointer for fscanf
            call [fscanf]                       ; Call fscanf
            add esp, 4*3                      ; Clean up the stack
            
            cmp eax, 1                        ; Check if fscanf successfully read a number
            jne case_error                    ; Jump if fscanf failed

            mov dword[min_dig], 10   ;prepare the min digit

            mov eax, dword [number] ;deimpartitul
            find_min_digit:
                mov bx, 10  ;impartitorul
                
                ;ax/dx is used for division, ax = quotient, dx = remainder
                
                mov edx, 0
                div bx
                
                mov ecx, dword[min_dig]  ;compare the actual base 10 digit with the min_digit
                cmp ecx, edx
                ja update_min   ;if it is smaller update it
                jmp loop_condition
               
                update_min:
                    mov dword[min_dig], edx
                
                loop_condition:
                    cmp ax, 0
                    jne find_min_digit
                    
                    
            ; Print the number to the console
            push dword [min_dig]               ; Push the number to print
            push dword format_out             ; Push the format string for printf
            call [printf]                       ; Call printf
            add esp, 4*2                        ; Clean up the stack
                
            mov ecx, dword[cpy]
                
            dec ecx                           ; Decrement loop counter
            jnz read_loop                     ; Continue loop if counter != 0

        ; Close the file
        push eax                          ; Push file pointer for fclose
        call [fclose]                       ; Call fclose
        add esp, 4                        ; Clean up the stack
        jmp program_end                   ; Exit the program

        case_error:
            ; Print error message if fscanf failed
            push dword error_msg              ; Push the error message
            call [perror]                       ; Call perror
            add esp, 4                        ; Clean up the stack
            jmp exit_program                  ; Exit the program

        program_end:
            ; Exit the program
            push dword 0                      ; Push exit code (0 = success)
            call exit                         ; Call exit

        exit_program:
            push dword 1                      ; Push exit code (1 = error)
            call exit                         ; Call exit
