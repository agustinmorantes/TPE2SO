include Makefile.inc

OBJECTS_DIR=./obj

SOURCES=$(wildcard [^_]*.c)
OBJECTS=$(SOURCES:%.c=$(OBJECTS_DIR)/%.o)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS_ASM=$(SOURCES_ASM:%.asm=$(OBJECTS_DIR)/%.o)

all: $(OBJECTS) $(OBJECTS_ASM)

# Ensamblado archivos ASM (primero creo el output path si no existe)
$(OBJECTS_DIR)/%.o : %.asm
	mkdir -p $(@D)
	$(ASM) $< -o $@ $(ASMFLAGS)

$(OBJECTS_DIR)/%.o : %.c
	mkdir -p $(@D)
	$(GCC) $< -o $@ $(GCCFLAGS)
    
clean:
	@rm -rf *.o $(OBJECTS_DIR)

.PHONY: all clean