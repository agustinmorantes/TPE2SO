GLOBAL _syswrite
GLOBAL _sysread
GLOBAL _systime
GLOBAL _sysclear
GLOBAL _sysprintmem
GLOBAL _systerminalraw
GLOBAL _sysexit
GLOBAL _sysgetpid
GLOBAL _syskill
GLOBAL _syschgpriority
GLOBAL _sysblock
GLOBAL _sysunblock
GLOBAL _sysyield

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
_sysexit:
    systemCall 6
_sysgetpid:
    systemCall 7
_syskill:
    systemCall 8
_syschgpriority:
    systemCall 9
_sysblock:
    systemCall 10
_sysunblock:
    systemCall 11
_sysyield:
    systemCall 12