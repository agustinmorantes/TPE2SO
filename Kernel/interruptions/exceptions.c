#include <exceptions.h>
#include <console.h>
#include <keyboard.h>
#include <interrupts.h>
#include <scheduler.h>

static void blueScreenOfDeath(const Registers * regs, char * msg);

void exceptionDispatcher(int exception, const Registers * regs) {
	switch (exception)
	{
	case ZERO_EXCEPTION_ID:
		printc("A division by zero was attempted", LightGray, Red);
		terminateProcess(getpid());
		break;
	case INVALID_OPCODE_ID:
		printc("An invalid instruction was read", LightGray, Red);
		terminateProcess(getpid());
		break;
	default:
		// Sabemos que no debería ser posible llegar a este punto, pues nosotros cargamos la tabla IDT como queremos. Sin embargo, dejamos esto por conveniencia para cuando se quiera seguir trabajando.
		blueScreenOfDeath(regs, "Unknown Error");
		terminateProcess(getpid());
		break;
	}
}

// Definimos una única función, pues la única diferencia entre ambas excepciones manejadas por nuestra Kernel es un mensaje al usuario.
// Si se quisiera algo particular para las excepciones en específico, se puede serparar en dos.
static void blueScreenOfDeath(const Registers * regs, char * msg) {

	clearTerminalColor(Blue);
	printc("The System has encountered an Error :(", Blue, White);
	newLine();
	printc("The error was the following: ", Blue, White);
	printc(msg, White, Blue);
	newLine();
	printc("The Registers at the moment of the Exception were:", Blue, White);
	newLine();
	printc("RAX: 0x", Blue, White);
	printhexc(regs->rax, Blue, White);
	newLine();
	printc("RBX: 0x", Blue, White);
	printhexc(regs->rbx, Blue, White);
	newLine();
	printc("RCX: 0x", Blue, White);
	printhexc(regs->rcx, Blue, White);
	newLine();
	printc("RDX: 0x", Blue, White);
	printhexc(regs->rdx, Blue, White);
	newLine();
	printc("RSI: 0x", Blue, White);
	printhexc(regs->rsi, Blue, White);
	newLine();
	printc("RDI: 0x", Blue, White);
	printhexc(regs->rdi, Blue, White);
	newLine();
	printc("RBP: 0x", Blue, White);
	printhexc(regs->rbp, Blue, White);
	newLine();
	printc("RSP: 0x", Blue, White);
	printhexc(regs->rsp, Blue, White);
	newLine();
	printc("R8: 0x", Blue, White);
	printhexc(regs->r8, Blue, White);
	newLine();
	printc("R9: 0x", Blue, White);
	printhexc(regs->r9, Blue, White);
	newLine();
	printc("R10: 0x", Blue, White);
	printhexc(regs->r10, Blue, White);
	newLine();
	printc("R11: 0x", Blue, White);
	printhexc(regs->r11, Blue, White);
	newLine();
	printc("R12: 0x", Blue, White);
	printhexc(regs->r12, Blue, White);
	newLine();
	printc("R13: 0x", Blue, White);
	printhexc(regs->r13, Blue, White);
	newLine();
	printc("R14: 0x", Blue, White);
	printhexc(regs->r14, Blue, White);
	newLine();
	printc("R15: 0x", Blue, White);
	printhexc(regs->r15, Blue, White);
	newLine();
	printc("RIP: 0x", Blue, White);
	printhexc(regs->rip, Blue, White);
	newLine();
	printc("RFLAGS: 0x", Blue, White);
	printhexc(regs->rflags, Blue, White);
	newLine();

	printc("Press ENTER to continue",Blue, White);

	while (readKeyPoll() != 28); //28 es el scancode de la tecla ENTER. Se lee por polling
	clearTerminal();
	_sti(); //Vuelvo a activar interrpuciones
}