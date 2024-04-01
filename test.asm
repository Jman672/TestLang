section .text
   global _start          ;must be declared for linker (gcc)
_start:                   ;tell linker entry point
    mov rax, 1
    mov rdi, 1
    mov rsi, test_
    mov rdx, 6
    syscall



    mov rax, 60
    mov rdi, 69
    syscall

 section .data
_var db 0xFF
_var2 db 0x10
test_ db "hello"