#include <stdint.h>
#include <console.h>
#include <numtostr.h>
#include <color.h>

#define COLS 80
#define ROWS 25

static uint8_t* screen = (uint8_t*)0xB8000;
static uint32_t cursorPos = 2; //Si lo coloco en 0 gcc coloca la variable en la sección .bss (que no me sirve)
static char buffer[64];

//Inicializo lo necesario para el funcionamiento del driver
void initVideo() {
	resetCursor();
}

// static uint64_t getCursorX() {
// 	return cursorPos%COLS;
// }

// static uint64_t getCursorY() {
// 	return cursorPos/COLS;
// }

static void scrollUp() {
	//Muevo todo una linea hacia arriba
	for(int y = 0; y<ROWS-1; y++) {
		for(int x = 0; x < COLS; x++) {
			unsigned int idx1 = (y*COLS + x)*2,
						 idx2 = ((y+1)*COLS+x)*2;
			screen[idx1]=screen[idx2];
			screen[idx1+1]=screen[idx2+1];
		}
	}

	//Limpio la ultima linea
	for(int x = 0; x < COLS; x++) {
		unsigned int idx = ((ROWS-1)*COLS + x)*2;
		screen[idx]=' ';
		screen[idx+1]=Black<<4;
	}

	//Pongo el cursor al principio de la linea
	cursorPos = (ROWS-1)*COLS*2;
}

//Imprime un caracter con un color de fondo y otro para la letra
void printcharc(char c, Color background, Color foreground) {
	if(c == 8) { //Si recibo el ascii de backspace borro
		if(cursorPos < 2) return;
		cursorPos -= 2;
		screen[cursorPos] = ' ';
		screen[cursorPos+1] = (background<<4) | foreground;
		return;
	}
		
	if(cursorPos >= COLS*ROWS*2) //Scrolleo si llego al final
		scrollUp();

	if(c == '\n') { //Si recibo \n voy a la linea siguiente
		newLine();
		return;
	}

	if(c == '\t') { 
		return;
	}

	//Seteo el caracter y sus colores y avanzo el cursor
	screen[cursorPos] = c;
	screen[cursorPos+1] = (background<<4) | foreground;
	cursorPos+=2;
}

//Imprime un caracter
void printchar(char c) {
	printcharc(c, Black, LightGray);
}

//Imprime una string con un color de fondo y otro para las letras
void printc(const char* string, Color background, Color foreground) {
	//Recorro la string
	char c;
	while((c = *string++) != 0) {
		printcharc(c, background, foreground);
	}
}

//Imprime una string con un color de fondo y otro para las letras y luego hace una nueva linea
void printcln(const char* string, Color background, Color foreground) {
	printc(string, background, foreground);
	newLine();
}

//Imprime una string y luego hace una nueva linea
void println(const char* string) {
    print(string);
    newLine();
}

//Imprime una string
void print(const char* string) {
	printc(string, Black, LightGray);
}

static void printbasec(uint64_t num, uint32_t base, Color background, Color foreground) {
	uintToBase(num, buffer, base);
	printc(buffer,background,foreground);
}

//Imprime un entero base 10 con un color de fondo y otro para las letras
void printnumc(uint64_t num, Color background, Color foreground) {
	printbasec(num, 10, background, foreground);
}

//Imprime un entero base 10
void printnum(uint64_t num) {
	printnumc(num, Black, LightGray);
}

//Imprime un entero base 16 con un color de fondo y otro para las letras
void printhexc(uint64_t hex, Color background, Color foreground) {
	printbasec(hex, 16, background, foreground);
}

//Imprime un entero base 16
void printhex(uint64_t hex) {
	printhexc(hex, Black, LightGray);
}

//Imprime un entero base 2 con un color de fondo y otro para las letras
void printbinc(uint64_t bin, Color background, Color foreground) {
	printbasec(bin, 2, background, foreground);
}

//Imprime un entero base 2
void printbin(uint64_t bin) {
	printbinc(bin, Black, LightGray);
}

//Cambio una posicion en la pantalla por un caracter dado con colores de fondo y letra
void setScreenPos(unsigned int topX, unsigned int topY, uint8_t c, Color background, Color foreground) {
	unsigned int idx = (topY*COLS + topX)*2;
	screen[idx] = c;
	screen[idx+1] = background<<4 | foreground;
}

//Limpia la pantalla con un color de fondo
void clearTerminalColor(Color background) {
	for(int i = 0; i < COLS*ROWS*2; i+=2) {
		screen[i] = ' ';
		screen[i+1] = background<<4;
	}
	resetCursor();
}

//limpia la terminal que se esta utilizando
void clearTerminal() {
	clearTerminalColor(Black);
}

//Nueva linea
void newLine() {
	cursorPos += COLS*2-(cursorPos%(COLS*2));
	if(cursorPos >= COLS*ROWS*2)
		scrollUp();
}

//Retorna la posicion actual del cursor
int getCursorPos() { return cursorPos/2; }

uint8_t getColumns() {
	return COLS;
}

//Resetea el cursor
void resetCursor() {
	cursorPos = 0;
}
