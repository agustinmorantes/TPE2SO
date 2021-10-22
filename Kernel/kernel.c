#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <idtLoader.h>
#include <interrupts.h>
#include <keyboard.h>
#include <rtc.h>
#include <console.h>
#include <syscallHandlers.h>
#include <processManagement.h>
#include <time.h>
#include <scheduler.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void *const sampleCodeModuleAddress = (void *)0x400000;
static void *const sampleDataModuleAddress = (void *)0x500000;

typedef int (*EntryPoint)();

void clearBSS(void *bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void *getStackBase()
{
	return (void *)((uint64_t)&endOfKernel + PageSize * 8 //The size of the stack itself, 32KiB
					- sizeof(uint64_t)					  //Begin at the top of the stack
	);
}

void *initializeKernelBinary()
{
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};
	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);
	
	// Interrupciones
	load_idt();
	
	initVideo();

	return getStackBase();
}

void testProc() {
	int t = 0;
	while(1) {
		int lastT = t;
		t = seconds_elapsed();
		if(t != lastT && t%3 == 0) {
			print("Time:");
			printnum(t);
			newLine();
		}
		_hlt();
	}
}

void haltProc() {
	while(1) _hlt();
}

int main()
{
	clearTerminal();
	printcln("[Kernel Main]", Black, Yellow);

	_cli();

	char* argv[] = {0};

	PID pid = processCreate(&haltProc, 0, argv);
	print("Halt process created with PID ");
	printnum(pid);
	newLine();

	// pid = processCreate(&testProc, 0, argv);
	// print("Second process created with PID ");
	// printnum(pid);
	// newLine();

	char* argv2[] = {"Hola!"};
	pid = processCreate(sampleCodeModuleAddress, 1, argv2);
	print("First process created with PID ");
	printnum(pid);
	newLine();

	initScheduler();

	println("Waiting for processes to run...");
	while(1) _hlt();

	return 0;
}