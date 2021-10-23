#include <stdint.h>
#include "syscallHandlers.h"

int64_t syscallDispatcher(uint64_t num, int64_t arg0, int64_t arg1, int64_t arg2) {
	switch (num) {
		case 0:
			return read((uint64_t)arg0, (char*)arg1, (uint64_t)arg2);
			break;
		case 1:
			return write((uint64_t)arg0, (const char*)arg1, (uint64_t)arg2);
			break;
		case 2:
			return time((Time*)arg0);
			break;
		case 3:
			clearTerminalSyscall();
			return 0;
			break;
		case 4:
			printmem((const void*)arg0);
			return 0;
			break;
		case 5:
			setTerminalRawMode((uint8_t)arg0);
			return 0;
			break;
		case 6: 
			exit();
			return 0;
			break;
		case 7:
			return getPidSyscall();
			break;
		case 8: 
			return kill((PID) arg0);
			break;
		case 9:
			return changePrioritySyscall((PID) arg0, (Priority) arg1);
			break;
		case 10:
			return blockProcessSyscall((PID) arg0);
			break; 
		case 11:
			return unblockProcessSyscall((PID) arg0);
			break;
		case 12:
			yieldSyscall();
			return 0;
			break;
	}
	return -1;
}

