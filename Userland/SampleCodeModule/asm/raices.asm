GLOBAL _getRoots


section .data
    discriminante dq 0
    denominador dq 0
    aux dq 0
    menoscuatro dq -4.0

section .text
_getRoots:
    push rbp
    mov rbp, rsp


    ; Cargo A al Stack.
    movlpd [aux], xmm0
    fld qword[aux]

    ; Cargo C al Stack.
    movlpd [aux], xmm2
    fld qword[aux]

    ; A*C en ST0
    fmulp st1
    ; -4*A*C en ST0
    fmul qword[menoscuatro]
    
    ; Cargo B al Stack.
    movlpd [aux], xmm1
    fld qword[aux]
    fld qword[aux]
    fmulp st1

    faddp st1

    ftst
    ;muevo los flags del fpu a rflags
    fstsw ax
    sahf
    ; Si el discriminante es menor a 0, no hay raices reales.
    jb .sin_raices
    ; Si estoy acá, tengo raíces reales.
    fsqrt
    fstp qword[discriminante]

    fld1
    movlpd [aux], xmm0
    fld qword[aux]
    ; ST0 = 2*A
    fscale
    ; ST0 = 1/(2*A)
    fdivp st1
    fst qword[denominador]

    fld qword[discriminante]
    movlpd [aux], xmm1
    fld qword[aux]
    fchs ; Ahora tengo -B, discriminante
    faddp
    fmulp
    ; Ahora tengo en ST0 la raíz superior

    fstp qword[rdi]

    ;Stack vacío. Cargo todo y resto.
    fld qword[denominador]
    fld qword[discriminante]
    fchs
    movlpd [aux], xmm1
    fld qword[aux]
    fchs
    faddp
    fmulp
    ; Ahora tengo en ST0 la raíz inferior

    fstp qword[rsi]
    mov rax, 1
    jmp .fin

.sin_raices:
    ; Si no hay raíces, retorno 0.
    mov rax, 0

.fin:
    leave 
    ret