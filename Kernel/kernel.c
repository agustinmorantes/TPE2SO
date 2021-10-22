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

void aProc() {
	while (1) { 
		_cli();
		printchar('a');
		_hlt();
	}
}

void bProc() {
	while (1) {
		_cli();
		printchar('b');	
		_hlt();
	} 
}

void cProc() {
	while (1) {
		_cli();
		printchar('c');	
		_hlt();
	} 
}

void testProc() {
	int t = 0;
	int flag = 1;
	while(1) {
		int lastT = t;
		t = seconds_elapsed();
		if(t != lastT && t%3 == 0) {
			print("Time:");
			printnum(t);
			newLine();
			if (t == 3) {
				_cli();
				blockProcess(2);
				_sti();
			}
			if (t == 6) {
				_cli();
				blockProcess(3);
				_sti();
			}
			if (t == 9) {
				_cli();
				blockProcess(4);
				_sti();
			}
			if (t == 12) {
				_cli();
				unblockProcess(2);
				unblockProcess(3);
				unblockProcess(4);
				_sti();
			}
			if (t == 15) {
				_cli();
				changePriority(2,LOW);
				changePriority(3,MEDIUM);
				changePriority(4,HIGH);
				_sti();
			}
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

	char* argv[1] = {0};
	char* argvt[2] = {"time" ,0};
	char* argva[2] = {"a" ,0};
	char* argvb[2] = {"b" ,0};
	char* argvc[2] = {"c" ,0};


	PID pid = processCreate(&haltProc, 0, argv, HIGH);
	print("Halt process created with PID ");
	printnum(pid);
	newLine();

	// pid = processCreate(sampleCodeModuleAddress, 0, argv, LOW);
	// print("First process created with PID ");
	// printnum(pid);
	// newLine();

	pid = processCreate(&testProc, 0, argvt, LOW);
	print("Second process created with PID ");
	printnum(pid);
	newLine();
	
	pid = processCreate(&aProc, 0, argva, HIGH);

	pid = processCreate(&bProc, 0, argvb, MEDIUM);

	pid = processCreate(&cProc, 0, argvc, LOW);

	initScheduler();

	println("Waiting for processes to run...");
	while(1) _hlt();

	return 0;
}