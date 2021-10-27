; GLOBAL initLock
GLOBAL acquire
GLOBAL release

section .text

; initLock:
;     mov BYTE[rdi], 1
;     ret

acquire: 
    mov rax, 1
    xchg rax, [rdi]

    test rax, rax
    jnz acquire

    ret

release:
    mov rax, 0
    xchg rax, [rdi]
    ret