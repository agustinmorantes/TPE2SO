# TPE2SO - Sistema Operativo x64

## Descripción del Proyecto
Este proyecto es un Sistema Operativo de 64 bits para la arquitectura Intel x86-64, desarrollado como parte de la materia Sistemas Operativos. El sistema cuenta con un kernel con preemptive multitasking, memory management avanzado y mecanismos de IPC (Inter-Process Communication).

## Características Implementadas

### Kernel
- **Preemptive Multitasking:** Scheduler que soporta múltiples procesos con diferentes niveles de prioridad (LOW, MEDIUM, HIGH) y ejecución en foreground o background.
- **Memory Management:** Soporte para dos memory managers diferentes:
  - Memory manager por defecto (basado en listas).
  - **Buddy Allocator**.
- **Syscalls:** Conjunto completo de syscalls para control de procesos, I/O, memoria y sincronización (ejecutadas vía `int 80h`).
- **Drivers:**
  - Driver de teclado.
  - Driver de video con soporte para múltiples terminales.
  - Driver de RTC.

### IPC y Sincronización
- **Pipes:** Soporte para pipes anónimos y FIFOs (named pipes) para la transmisión de datos entre procesos.
- **Semáforos:** Implementación de semáforos para la sincronización de procesos y manejo de recursos compartidos.
- **Redirección de I/O:** Capacidad de redirigir stdin y stdout de los procesos.

### Userland
- **Shell Interactiva:** Interfaz de línea de comandos con soporte para dos terminales (intercambiables usando la tecla `TAB`). Soporta ejecución de comandos en background agregando `&` y pipes entre comandos usando `|`.
- **Comandos del Sistema:**
  - `help`: Lista los comandos disponibles.
  - `ps`: Lista todos los procesos actuales con su estado, PID, prioridad, etc.
  - `kill [pid]`: Termina un proceso en ejecución.
  - `nice [pid] [priority]`: Cambia la prioridad de un proceso.
  - `block [pid]`: Bloquea o desbloquea un proceso.
  - `mem`: Muestra el estado actual de la memoria (total, libre, ocupada).
  - `sem`: Lista los semáforos activos.
  - `pipes`: Lista los pipes activos.
  - `cat`, `wc`, `filter`: Utilidades estándar para el procesamiento de texto.
  - `phylo`: Implementación visual del problema de los Filósofos Comensales.
- **Tests Integrados:** Batería de pruebas para el memory manager (`test_mm`), scheduler (`test_processes`), sincronización (`test_sync`) y prioridades (`test_prio`).

## Guía de Uso

### Prerrequisitos
- Docker (Recomendado para asegurar el entorno de compilación)
- QEMU (Para emulación)

### Compilación del Proyecto
La forma más sencilla de compilar el proyecto es utilizando el script provisto que ejecuta Docker:
```bash
./build.sh
```
Esto compilará el toolchain, el kernel y los módulos de userland en un entorno controlado.

Para compilar manualmente en un entorno local (requiere `gcc`, `nasm`, `make`):
```bash
make all      # Utiliza el memory manager por defecto
make buddy    # Utiliza el Buddy Allocator
```

### Ejecución del Sistema Operativo
Para lanzar el sistema operativo utilizando QEMU:
```bash
./run.sh
```
*(Nota: En sistemas Windows, se pueden utilizar los scripts `run.bat` o `open_qemu.bat`)*

## Estructura del Proyecto
- `/Bootloader`: Código fuente bootloader (Pure64 y BMFS).
- `/Kernel`: Lógica central del kernel (scheduler, memory manager, drivers, syscalls).
- `/Userland`: Aplicaciones de usuario, shell interactiva y tests.
- `/Toolchain`: Utilidades para el build (ModulePacker).
- `/Image`: Scripts y archivos necesarios para generar la imagen booteable.

## Autores
- **Mauro Sambartolomeo**
- **Agustín Morantes**
- **Juan Manuel Negro**
