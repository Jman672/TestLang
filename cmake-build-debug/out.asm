global _start
_start:
    mov rax, 60
    mov rdi, [var]
    syscall
var:
    db 15
