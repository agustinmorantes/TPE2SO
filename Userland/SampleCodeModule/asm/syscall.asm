GLOBAL _syswrite
GLOBAL _sysread
GLOBAL _systime
GLOBAL _sysclear
GLOBAL _sysprintmem
GLOBAL _sysswitchterminal
GLOBAL _systerminalraw
GLOBAL _sysgetcurrentterminal

section .text

%macro systemCall 1
    push rbp
    mov rbp, rsp

    mov rax, %1
    int 80h

    leave
    ret
%endmacro

_sysread:
    systemCall 0
_syswrite:
    systemCall 1
_systime:
    systemCall 2
_sysclear:
    systemCall 3
_sysprintmem:
    systemCall 4
_systerminalraw:
    systemCall 5
_sysgetcurrentterminal:
    systemCall 6
