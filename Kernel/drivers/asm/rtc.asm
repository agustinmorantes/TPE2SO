GLOBAL readRtcRaw

section .text

readRtcRaw:
    push rbp
    mov rbp,rsp

    mov rax,rdi
    out 70h,al
    mov rax,0
    in al,71h

    mov rsp,rbp
    pop rbp
    ret

