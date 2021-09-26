GLOBAL _testCpuidSupport
GLOBAL _getExtendedCpuFeatures
GLOBAL _getCpuFeatures


section .text
_testCpuidSupport:
    pushfq 
    pushfq ;guardo las eflags
    xor qword [rsp], 0x200000 ; invierto el valor del bit de esp
    popfq ; popeo las flags modificadas en las flags
    pushfq ; pusheo las flags de nuevo para ver si estan modificadas o no
    pop rax ; popeo las flags que pueden estar modificadas o no en eax
    xor rax, [rsp] ; borro los bits que sean iguales con la flag
    popf
    ret
_getCpuFeatures:
    push rbp
	mov rbp, rsp

    push rbx
    
    mov rax,1
    cpuid
    mov rax,rdx
    shl rcx, 32
    or rax, rcx

    pop rbx
    
    leave
    ret

_getExtendedCpuFeatures:
    push rbp
	mov rbp, rsp

    push rbx
    
    mov rax,7
    mov rcx,0

    cpuid
    mov rax,rbx
    shl rcx, 32
    or rax, rcx

    pop rbx
    
    leave
    ret