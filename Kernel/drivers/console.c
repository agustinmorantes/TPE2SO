#include <stdint.h>
#include <console.h>
#include <numtostr.h>
#include <bizcat.h>
#include <color.h>

static const int charWidth = 8;
static const int charHeight = 16;

#pragma pack(push,1)
typedef struct {
	uint8_t b;
	uint8_t g;
	uint8_t r;
} VideoPixel;
#pragma pack(pop)

static VideoPixel* video;
static uint16_t videoX;
static uint16_t videoY;
static uint8_t depth;
static uint64_t currentCursor;
static uint8_t columns;
static uint8_t lines;
static uint64_t screenLength;
static uint64_t terminalID; // Terminal ID from 0 to N-1.

// cantidad de pixeles usados para separar entre terminales debe ser entre 2 y 16
#define SEPARATION_WIDTH 0
#define SCREEN_QUANTITY 1
//backups de los cursores para el cambio de terminal
static uint64_t cursors[SCREEN_QUANTITY];

static char buffer[64];

void generateSeparation();

//Inicializo lo necesario para el funcionamiento del driver
void initVideo() {
	//Tomo los datos de modo gráfico de memoria segun el manual de pure64
	video = (VideoPixel*)(uint64_t)(*(uint32_t *)0x5080);
	videoX = *(uint16_t *)0x5084;
	videoY = *(uint16_t *)0x5086;
	depth = *(uint8_t *)0x5088;
	columns = videoX / charWidth;
	lines = videoY / charHeight;
	screenLength = (videoX/SCREEN_QUANTITY) / charWidth - 2;
	for (int i = 0; i < SCREEN_QUANTITY; i++)
	{
		cursors[i] = 1 + i*(screenLength + 2);
	}
	currentCursor = cursors[0];
	resetCursor();
	generateSeparation();
}

static uint64_t getCursorX() {
	return currentCursor%columns;
}

static uint64_t getCursorY() {
	return currentCursor/columns;
}

uint64_t getCurrentTerminal() {
	return terminalID;
}

void switchTerminal() {
	cursors[terminalID] = currentCursor;
	terminalID = (terminalID+1)%SCREEN_QUANTITY;
	currentCursor = cursors[terminalID];
}

void increaseCursor() {
	if (currentCursor%(screenLength + 2) == screenLength) {
		currentCursor += columns - screenLength;
	}
	currentCursor++;
}

void decreaseCursor() {
	if (currentCursor%(screenLength + 2) == 1)
	{
		currentCursor -= columns - screenLength;
	}
	currentCursor--;
}

static void setPixel(uint64_t idx, Color color) {
	//Mapeo el struct Color a VideoPixel (no son iguales)
	video[idx].r = color.r;
	video[idx].g = color.g;
	video[idx].b = color.b;
}

static void scrollUp() {
	//Copio todo una linea mas arriba
	for(int y = 0; y < videoY - charHeight; y++) {
		for(int x = SEPARATION_WIDTH/2; x < videoX/SCREEN_QUANTITY - SEPARATION_WIDTH/2; x++) {
			unsigned int to = y*videoX + x + terminalID*videoX/SCREEN_QUANTITY;
			unsigned int from = (y + charHeight)*videoX + x + terminalID*videoX/SCREEN_QUANTITY;
			video[to] = video[from];
		}
	}

	//Limpio la ultima linea
	for(int y = 0; y < charHeight; y++) {
		for(int x = SEPARATION_WIDTH/2; x < videoX/SCREEN_QUANTITY - SEPARATION_WIDTH/2; x++) {
			unsigned int idx = (videoY-y-1)*videoX + x + terminalID*videoX/SCREEN_QUANTITY;
			setPixel(idx, Black);
		}
	}

	//Pongo el cursor al principio de la linea
	currentCursor = (lines - 1)*columns + terminalID*(screenLength + 2) + 1;
	// currentCursor = (lines-1)*columns;
}

//Imprime un caracter con un color de fondo y otro para la letra
void printcharc(char c, Color background, Color foreground) {
	if(c == 8) { //Si recibo el ascii de backspace borro
		if(currentCursor <= 1 + terminalID*videoX/SCREEN_QUANTITY/charWidth) return;
		decreaseCursor();
		setScreenPos(getCursorX(), getCursorY(), ' ', background, foreground);
		return;
	}
		
	if(currentCursor >= columns*lines) //Scrolleo si llego al final
		scrollUp();

	if(c == '\n') { //Si recibo \n voy a la linea siguiente
		newLine();
		return;
	}

	if(c == '\t') { 
		return;
	}

	//Seteo el caracter y sus colores y avanzo el cursor
	setScreenPos(getCursorX(), getCursorY(), c, background, foreground);
	increaseCursor();
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
	//Itero sobre todos los pixeles que conforman el caracter
	for(int y = 0; y < charHeight; y++) {
		for(int x = 0; x < charWidth; x++) {
			//Determino el indice del pixel
			uint64_t startPos = (topY*charHeight*videoX + topX*(charWidth));
			uint64_t idx = startPos + y * videoX + x;

			//Veo si el pixel forma parte de la letra o el fondo y lo escribo
			uint8_t isForegroundPixel = (bizcat_font_data[c*charHeight + y] >> x) & 1;
			Color c = isForegroundPixel ? foreground : background;
			setPixel(idx, c);
		}
	}
}

//Limpia la pantalla con un color de fondo
void clearTerminalColor(Color background) {
	for (int j = 0; j < videoY; j++)
	{	
		for(int i = SEPARATION_WIDTH/2; i < videoX/SCREEN_QUANTITY - SEPARATION_WIDTH/2 ; i++) {
			setPixel(j*videoX + i + terminalID*videoX/SCREEN_QUANTITY, background);
		}
	}
	resetCursor();
}

//limpia la terminal que se esta utilizando
void clearTerminal() {
	clearTerminalColor(Black);
}

//Nueva linea
void newLine() {
	currentCursor += columns - (currentCursor%(screenLength+2)) + 1;
	if(currentCursor >= columns*lines)
		scrollUp();
}

//Retorna la posicion actual del cursor
int getCursorPos() { return currentCursor; }

uint8_t getColumns() {
	return columns;
}

//Resetea el cursor
void resetCursor() {
	currentCursor = 1 + terminalID*(screenLength + 2);
}

void generateSeparation() {
	for (int i = 0; i < videoY; i++)
	{
		for (int j = 0; j < SEPARATION_WIDTH; j++)
		{
			if (j < SEPARATION_WIDTH/2){
				setPixel(i*videoX + j,White);
			} else {
				setPixel((i+1)*videoX - 1 - j%(SEPARATION_WIDTH/2), White);
			}
			for (int k = 1; k < SCREEN_QUANTITY; k++)
			{
				uint64_t idx = i*videoX + k*(videoX/SCREEN_QUANTITY) - SEPARATION_WIDTH/2 + j;
				setPixel(idx ,White);
			}
		}
	}
}