GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _exception0Handler
GLOBAL _exception6Handler

GLOBAL _syscallHandler

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallDispatcher

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

;Macros para _syscallHandler (que necesita devolver un valor en rax)
%macro pushStateWithoutRax 0
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popStateWithoutRax 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
%endmacro

%macro irqHandlerMaster 1
	cli
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	sti
	iretq
%endmacro

%macro exceptionHandler 1
	cli ;Desactivo interrupciones
	push rbp
	mov rbp, rsp

	;Armo el struct en stack para poder accederlo desde C
    push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rsi
	push rdi
	push rdx
	push rcx
	push rbx
	push rax
	
	;Agarro el RBP anterior.
	mov rax, [rbp]
	push rax
	;Agarro el RIP que pushea la excepción.
	mov rax, [rbp + 8]
	push rax
	;Agarro el RFLAGS que pushea la excepción.
	mov rax, [rbp + 24]
	push rax
	;Agarro el RSP que puseha la excepción.
	mov rax, [rbp + 32]
	push rax

	mov rdi, %1 ; pasaje de parametro
	mov rsi, rsp
	call exceptionDispatcher

	;Desarmo el stack
    add rsp, 8
    pop rax
	pop rbx
	pop rcx
	pop rdx
	pop rdi
	pop rsi
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15

    leave

	iretq
%endmacro

_int20:
	int 20h
	ret

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	pushState

	mov rdi, 0 ; pasaje de parametro
	call irqDispatcher

	mov rdi, rsp
	call scheduler
	mov rsp, rax

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0
_exception6Handler:
	exceptionHandler 6

_syscallHandler:
	pushStateWithoutRax

	;Corro todos los parametros
	;Para que coincidan con la firma del handler
	mov rcx,rdx ; arg2
	mov rdx,rsi ; arg1
	mov rsi,rdi ; arg0
	mov rdi,rax ; numero de syscall

	call syscallDispatcher

	popStateWithoutRax
	iretq

haltcpu:
	cli
	hlt
	ret

SECTION .bss
	aux resq 1