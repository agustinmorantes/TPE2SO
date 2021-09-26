include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
OBJECTS_DIR=./obj

SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS_ASM=$(SOURCES_ASM:%.asm=$(OBJECTS_DIR)/%.o)


all: $(MODULE)

$(MODULE): $(SOURCES) $(OBJECTS_ASM)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld -I include/ _loader.c $(SOURCES) $(OBJECTS_ASM) -o ../$(MODULE)
# configuracion de gdb
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld -Wl,--oformat=elf64-x86-64 _loader.c $(SOURCES) $(OBJECTS_ASM) -o ../0000-sampleCodeModule.elf

# Ensamblado archivos ASM (primero creo el output path si no existe)
$(OBJECTS_DIR)/%.o : %.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) $< -o $@

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@
	
clean:
	rm -rf *.o $(OBJECTS_DIR)

.PHONY: all clean print
