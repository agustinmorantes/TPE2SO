Manual de usuario
==================
Manual de usuario para nuestro TPE

## Uso de terminal
La pantalla contiene en todo momento 2 terminales. Para cambiar entre ellas utilice la tecla TAB del teclado.
Solo se puede cambiar de terminales cuando está activo el prompt de la shell (cuando es posible ejecutar comandos) por decisión de diseño.
Si se encuentra ejecutando un comando que requiere input de entrada estándar y presiona TAB, verá que no se cambia la terminal.

Una vez que figura el prompt (`>`), puede interactuar con el sistema escribiendo comandos con sus argumentos e ingresándolos con la tecla ENTER.
Ejemplo: `>printmem abcdef`

A continuación se listan los comandos implementados y su uso.

## Comandos
- `help`
- `lscmd`
- `clear`
- `greet`
- `time`
- `printmem`
- `inforeg`
- `printcpufeatures`
- `divbyzero`
- `invalidopcode`
- `roots`
- `suma`

### `help`
Lista todos los comandos disponibles

---

### `lscmd`
Lista todos los comandos disponibles

---

### `clear`
Limpia la terminal actual

---

### `greet`
Un simple programa que utiliza scanf y printf para hacer un saludo personalizado

---

### `time`
Muestra la fecha y la hora en pantalla

---

### `printmem`
Muestra en pantalla 32bytes a partir de la posición de memoria recibida por parametro.
Muestra cada byte como 2 digitos hexadecimales, cada byte separado por un espacio.
El parámetro tiene que ser hexadecimal válido sin prefijo `0x` ni sufijo `h` y ser una posición de memoria válida 
Ejemplo: `printmem abcdef`

---

### `inforeg`
Muestra el valor de los registros al momento de ejecutar el comando

---

### `printcpufeatures`
Muestra los features que posee el cpu

---

### `divbyzero`
Programa ejemplo que realiza una división por cero.

---

### `invalidopcode`
Programa ejemplo que ejecuta una instrucción de procesador inválida

---

### `roots`
Recibe 3 números a,b y c por entrada estándar (scanf) y, utilizando el FPU calcula las raíces de la cuadrática asociada.
Ejemplo de uso:
```
>roots
Inserte los parámetros de la cuadrática (a, b, c): 1 3 2
Las raíces son: -1.0 y -2.0
```

---

### `suma`
Recibe 2 números por entrada estándar (scanf) y muestra en pantalla el resultado de la suma (printf)

---

