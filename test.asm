global _start
_start:
    mov rax, 60
    mov rbx, [_var2]
    mov [_var], rbx
    mov rdi, [_var]
    syscall

section .data
_var db 0xFF
_var2 db 0x10