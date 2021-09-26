GLOBAL _invalidopcode

SECTION .text

_invalidopcode:
    ud2 ;Instrucción invalida
    ret
