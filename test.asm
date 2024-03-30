global _start
_start:
    mov rax, 60
    mov rdi, [_var]
    syscall

_var:
    db 0xFF