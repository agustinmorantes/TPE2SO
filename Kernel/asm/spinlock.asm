; GLOBAL initLock
GLOBAL acquire
GLOBAL release

section .text

; initLock:
;     mov BYTE[rdi], 1
;     ret

acquire: 
    mov al, 1
    xchg al, [rdi]

    test al, al
    jnz acquire

    ret

release:
    mov al, 0
    xchg al, [rdi]
    ret