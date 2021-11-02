include Makefile.inc

KERNEL=kernel.bin

# Directorios Include
INCLUDE_DIRS=include interruptions/include drivers/include memoryManager/include pipe/include
INCLUDES=$(addprefix -I ,$(INCLUDE_DIRS))

# Codigo .c y .asm
SOURCES=$(wildcard *.c) $(wildcard interruptions/*.c) $(wildcard drivers/*.c) $(wildcard memoryManager/*.c) $(wildcard pipe/*.c)
SOURCES_ASM=$(wildcard asm/*.asm) $(wildcard interruptions/asm/*.asm) $(wildcard drivers/asm/*.asm)

GCCDEFS=

# Carpeta y archivos objeto 
OBJECTS_DIR=./obj
OBJECTS=$(SOURCES:%.c=$(OBJECTS_DIR)/%.o)
OBJECTS_ASM=$(SOURCES_ASM:%.asm=$(OBJECTS_DIR)/%.o)

LOADERSRC=loader.asm
LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

# Archivos a linkeditar
ALL_OBJECTS= $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM)

# Regla "make all"
all: $(KERNEL)

# Regla "make buddy"
buddy: GCCDEFS=-DBUDDY
buddy: $(KERNEL)

# Linkedición
$(KERNEL): $(STATICLIBS) $(ALL_OBJECTS)
	$(LD) $(LDFLAGS) -T kernel.ld -o $@ $^
# configuracion de gdb
	$(LD) $(LDFLAGS) -T kernel.ld --oformat=elf64-x86-64 -o kernel.elf $^

# Compilación archivos C (primero creo el output path si no existe)
$(OBJECTS_DIR)/%.o: %.c
	mkdir -p $(@D) 
	$(GCC) $(GCCFLAGS) $(GCCDEFS) $(INCLUDES) -c $< -o $@

# Ensamblado archivos ASM (primero creo el output path si no existe)
$(OBJECTS_DIR)/%.o : %.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

# Elimino el output
clean:
	rm -rf $(ALL_OBJECTS) *.bin *.elf $(OBJECTS_DIR)

.PHONY: all clean buddy
