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
GLOBAL _syscreateprocess
GLOBAL _syssetbackground
GLOBAL _syspipe
GLOBAL _sysclose
GLOBAL _sysmkfifo
GLOBAL _sysopenfifo
GLOBAL _sysmapstdfds
GLOBAL _sysrmfifo
GLOBAL _syslistpipes
GLOBAL _syslistprocesses
GLOBAL _semopen
GLOBAL _semwait
GLOBAL _sempost
GLOBAL _semclose
GLOBAL _syslistsem
GLOBAL _sysalloc
GLOBAL _sysfree
GLOBAL _sysmem

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
_syscreateprocess:
    systemCall 13
_syssetbackground:
    systemCall 14
_syspipe:
    systemCall 15
_sysclose:
    systemCall 16
_sysmkfifo:
    systemCall 17
_sysopenfifo:
    systemCall 18
_sysmapstdfds:
    systemCall 19
_sysrmfifo:
    systemCall 20
_syslistpipes:
    systemCall 21
_syslistprocesses:
    systemCall 22
_semopen:
    systemCall 23
_semwait:
    systemCall 24
_sempost:
    systemCall 25
_semclose:
    systemCall 26
_syslistsem:
    systemCall 27
_sysalloc:
    systemCall 28
_sysfree:
    systemCall 29
_sysmem:
    systemCall 30
