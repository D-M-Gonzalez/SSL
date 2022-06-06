# Fases de la traducción y errores

## Objetivos

    Este trabajo tiene como objetivo identificar las fases del proceso de traducción o
    Build y los posibles errores asociados a cada fase.
    Para lograr esa identificación se ejecutan las fases de traducción una a una, se
    detectan y corrigen errores, y se registran las conclusiones en readme.md.
    No es un trabajo de desarrollo; es más, el programa que usamos como ejemplo es
    simple, similar a hello.c pero con errores que se deben corregir. La complejidad
    está en la identificación y comprensión de las etapas y sus productos.

## Temas

- Fases de traducción.
- Preprocesamiento.
- Compilación.
- Ensamblado.
- Vinculación (Link).
- Errores en cada fase.


## Tareas

    1. La primera tarea es investigar las funcionalidades y opciones que su
    compilador presenta para limitar el inicio y fin de las fases de traducción.
    1. La siguiente tarea es poner en uso lo que se encontró. Para eso se debe
    transcribir al readme.md cada comando ejecutado y su resultado o error
    correspondiente a la siguiente secuencia de pasos. También en readme.md se
    vuelcan las conclusiones y se resuelven los puntos solicitados. Para claridad,
    mantener en readme.md la misma numeración de la secuencia de pasos

## Resolución

    Se parte de un archivo fuente que es corregido y refinado en sucesivos pasos.
    Es importante no saltearse pasos para mantener la correlación, ya que el estado
    dejado por el paso anterior es necesario para el siguiente.

### Preprocesador

### Escribir hello2.c, que es una variante de hello.c:

```c
#include <stdio.h>
int/*medio*/main(void){
    int i=42;
    prontf("La respuesta es %d\n");
```

--------------------------

### Preprocesar hello2.c, no compilar, y generar hello2.i. Analizar su contenido. ¿Qué conclusiones saca?

    El preprocesador se encargó de incluir todo el contenido de stdio y de remover los comentarios existentes en hello2.c. Luego su trabjao concluyó. No hubo errores en el medio.


### Escribir hello3.c, una nueva variante:

```c
int printf(const char * restrict s, ...);
int main(void){
 int i=42;
 prontf("La respuesta es %d\n");
```

### Investigar e indicar la semántica de la primera línea

    La primera línea es la declaración de la función printf, quien toma como parámetros al menos 1, que es un puntero constante a una variable del tipo char con nombre s. Hay que tener en cuenta en esta declaración, que lo constante es el puntero y no la variable s.

### Preprocesar hello3.c, no compilar, y generar hello3.i. Buscar diferencias entre hello3.c y hello3.i

```c
# 0 "hello3.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "hello3.c"
int printf(const char * restrict s, ...);
int main(void){
int i=42;
 prontf("La respuesta es %d\n");
```

    Al no incluir stdio vemos como el preprocesador tampoco lo incluye en el hello3.i.

## Compilación

### Compilar el resultado y generar hello3.s, no ensamblar.

    $ gcc -S hello3.i -o hello3.s
    hello3.c: In function 'main':
    hello3.c:4:2: warning: implicit declaration of function 'prontf'; did you mean 'printf'? [-Wimplicit-function-declaration]
    4 |  prontf("La respuesta es %d\n");
      |  ^~~~~~
      |  printf
    hello3.c:4:2: error: expected declaration or statement at end of input

    Vemos como gracias al error no nos dió un archivo de salida. El error en cuestión, es un error de sintaxis dentro de la declaración de la función main al faltarle la llave de cierre.

### Corregir solo los errores, no los warnings, en el nuevo archivo hello4.c y empezar de nuevo, generar hello4.s, no ensamblar.

```c
int printf(const char * restrict s, ...);//declaracion
int main(void){//declaracion y definicion
int i=42;//declaracion y definicion
 prontf("La respuesta es %d\n");//sentencia
}
```

```s
	.file	"hello4.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "La respuesta es %d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	movl	$42, -4(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	prontf
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (Rev10, Built by MSYS2 project) 11.2.0"
	.def	prontf;	.scl	2;	.type	32;	.endef
```

### Leer hello4.s, investigar sobrelenguajeensamblador,e indicar de forma sintética cual es el objetivo de ese código.

    El objetivo de hello4.s es cambiar el código de alta abstracción presente en hello4.i a código que la máquina puede entender. El código asembler ahora realiza lo mismo pero desde el punto de vista del manejo de memoria y del armado del callstack para poder realizar las operaciones en el orden que le indicamos en hello4.c

### Ensamblar hello4.s en hello4.o, no vincular.

    Podemos ver como se generó hello4.o y vemos que su resultado es estrictamente numérico, utilizando la llamada a od para poder traduccir el archivo objeto.

```
$ od -t x1 hello4.o
0000000 64 86 07 00 00 00 00 00 00 02 00 00 14 00 00 00
0000020 00 00 04 00 2e 74 65 78 74 00 00 00 00 00 00 00
0000040 00 00 00 00 30 00 00 00 2c 01 00 00 c4 01 00 00
0000060 00 00 00 00 03 00 00 00 20 00 50 60 2e 64 61 74
0000100 61 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000120 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000140 40 00 50 c0 2e 62 73 73 00 00 00 00 00 00 00 00
0000160 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000200 00 00 00 00 00 00 00 00 80 00 50 c0 2e 72 64 61
0000220 74 61 00 00 00 00 00 00 00 00 00 00 20 00 00 00
0000240 5c 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0000260 40 00 50 40 2e 78 64 61 74 61 00 00 00 00 00 00
0000300 00 00 00 00 0c 00 00 00 7c 01 00 00 00 00 00 00
0000320 00 00 00 00 00 00 00 00 40 00 30 40 2e 70 64 61
0000340 74 61 00 00 00 00 00 00 00 00 00 00 0c 00 00 00
0000360 88 01 00 00 e2 01 00 00 00 00 00 00 03 00 00 00
0000400 40 00 30 40 2f 34 00 00 00 00 00 00 00 00 00 00
0000420 00 00 00 00 30 00 00 00 94 01 00 00 00 00 00 00
0000440 00 00 00 00 00 00 00 00 40 00 50 40 55 48 89 e5
0000460 48 83 ec 30 e8 00 00 00 00 c7 45 fc 2a 00 00 00
0000500 48 8d 05 00 00 00 00 48 89 c1 e8 00 00 00 00 b8
0000520 00 00 00 00 48 83 c4 30 5d c3 90 90 4c 61 20 72
0000540 65 73 70 75 65 73 74 61 20 65 73 20 25 64 0a 00
0000560 00 00 00 00 00 00 00 00 00 00 00 00 01 08 03 05
0000600 08 52 04 03 01 50 00 00 00 00 00 00 2e 00 00 00
0000620 00 00 00 00 47 43 43 3a 20 28 52 65 76 31 30 2c
0000640 20 42 75 69 6c 74 20 62 79 20 4d 53 59 53 32 20
0000660 70 72 6f 6a 65 63 74 29 20 31 31 2e 32 2e 30 00
0000700 00 00 00 00 09 00 00 00 12 00 00 00 04 00 17 00
0000720 00 00 0a 00 00 00 04 00 1f 00 00 00 13 00 00 00
0000740 04 00 00 00 00 00 04 00 00 00 03 00 04 00 00 00
0000760 04 00 00 00 03 00 08 00 00 00 0c 00 00 00 03 00
0001000 2e 66 69 6c 65 00 00 00 00 00 00 00 fe ff 00 00
0001020 67 01 68 65 6c 6c 6f 34 2e 63 00 00 00 00 00 00
0001040 00 00 00 00 6d 61 69 6e 00 00 00 00 00 00 00 00
0001060 01 00 20 00 02 01 00 00 00 00 00 00 00 00 00 00
0001100 00 00 00 00 00 00 00 00 2e 74 65 78 74 00 00 00
0001120 00 00 00 00 01 00 00 00 03 01 2e 00 00 00 03 00
0001140 00 00 00 00 00 00 00 00 00 00 00 00 2e 64 61 74
0001160 61 00 00 00 00 00 00 00 02 00 00 00 03 01 00 00
0001200 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0001220 2e 62 73 73 00 00 00 00 00 00 00 00 03 00 00 00
0001240 03 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0001260 00 00 00 00 2e 72 64 61 74 61 00 00 00 00 00 00
0001300 04 00 00 00 03 01 14 00 00 00 00 00 00 00 00 00
0001320 00 00 00 00 00 00 00 00 2e 78 64 61 74 61 00 00
0001340 00 00 00 00 05 00 00 00 03 01 0c 00 00 00 00 00
0001360 00 00 00 00 00 00 00 00 00 00 00 00 2e 70 64 61
0001400 74 61 00 00 00 00 00 00 06 00 00 00 03 01 0c 00
0001420 00 00 03 00 00 00 00 00 00 00 00 00 00 00 00 00
0001440 00 00 00 00 0f 00 00 00 00 00 00 00 07 00 00 00
0001460 03 01 2c 00 00 00 00 00 00 00 00 00 00 00 00 00
0001500 00 00 00 00 5f 5f 6d 61 69 6e 00 00 00 00 00 00
0001520 00 00 20 00 02 00 70 72 6f 6e 74 66 00 00 00 00
0001540 00 00 00 00 20 00 02 00 1a 00 00 00 2e 72 64 61
0001560 74 61 24 7a 7a 7a 00 2e 72 64 61 74 61 24 7a 7a
0001600 7a 00
0001602
```

    En este archivo vemos la representación de los datos en formato hexadecimal bit por bit.

## Vinculación

### Vincular hello4.o con la biblioteca estándar y generar el ejecutable.

    $ gcc hello4.o
    C:/msys64/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/11.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: hello4.o:hello4.c:(.text+0x1f): undefined reference to `prontf'
    collect2.exe: error: ld returned 1 exit status

    Encontramos un error de vinculación, debido a que prontf no está declarado en ningún lado que el vinculador pueda encontrar.

### Corregir en hello5.c y generar el ejecutable. Solo corregir lo necesario para que vincule.

```c
int printf(const char * restrict s, ...);//declaracion
int main(void){//declaracion y definicion
int i=42;//declaracion y definicion
 printf("La respuesta es %d\n");//sentencia
}
```

### Ejecutar y analizar el resultado

    Se logra el ejecutable cambiando la sentencia prontf por printf pero el mismo devuelve La respuesta es 461338208. Este bug sucede debido a que no le indicamos a printf de donde tomar el valor.

### Corregir en hello6.c y empezar de nuevo; verificar que funciona como se espera.

```c
int printf(const char * restrict s, ...);//declaracion
int main(void){//declaracion y definicion
int i=42;//declaracion y definicion
 printf("La respuesta es %d\n",i);//sentencia
}
```

    Se corrige la referencia a la variable. y el resultado es el correcto: La respuesta es 42

## Remoción de prototipo

###  Escribir hello7.c, una nueva variante:


```c
int main(void){
int i=42;
 printf("La respuesta es %d\n",i);
}
```

### Explicar porqué funciona.

```c
hello7.c: In function 'main':
hello7.c:3:2: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
    3 |  printf("La respuesta es %d\n",i);
      |  ^~~~~~
hello7.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
  +++ |+#include <stdio.h>
    1 | int main(void){
hello7.c:3:2: warning: incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
    3 |  printf("La respuesta es %d\n",i);
      |  ^~~~~~
hello7.c:3:2: note: include '<stdio.h>' or provide a declaration of 'printf'
```

    Esto funciona porque como dice el warning, printf es conocido por el vinculador y sabe donde buscarlo en nuestra PC por mas que no este incluido por el preprocesador.

## Compilación Separada: Contratos y Módulos

### Escribir studio1.c (sí, studio1, no stdio) y hello8.c.

    La unidad de traducción studio1.c tiene una implementación de la
    función prontf, que es solo un wrappwer1
    de la función estándar printf:

```c
void prontf(const char* s, int i){
 printf("La respuesta es %d\n", i);
}

```

    La unidad de traducción hello8.c, muy similar a hello4.c, invoca a
    prontf, pero no incluye ningún header.

```c
int main(void){
int i=42;
 prontf("La respuesta es %d\n", i);
}
```

### Investigar como en su entorno de desarrollo puede generar un programa ejecutable que se base en las dos unidades de traducción (i.e., archivos fuente, archivos con extensión .c). Luego generar ese ejecutable y probarlo.

```c
main.c: In function ‘main’:
main.c:3:2: warning: implicit declaration of function ‘prontf’ [-Wimplicit-function-declaration]
    3 |  prontf("La respuesta es %d\n", i);
      |  ^~~~~~
studio1.c: In function ‘prontf’:
studio1.c:2:2: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
    2 |  printf("La respuesta es %d\n", i);
      |  ^~~~~~
studio1.c:2:2: warning: incompatible implicit declaration of built-in function ‘printf’
studio1.c:1:1: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
  +++ |+#include <stdio.h>
    1 | void prontf(const char* s, int i){
La respuesta es 42
```

    El entorno de desarrollo puede hacerlo debido a que se encuentran en la misma carpeta. El mismo busca entre los archivos alguna declaración que coincida con la faltante y la incluye de encontrarla. Sin embargo, el compilador nos avisa con un warning que la función no fué declarada ni que se inlcuyó un header para identificar cual es la función a la que estamos llamando.

### Responder ¿qué ocurre si eliminamos o agregamos argumentos a la invocación de prontf? Justifique.

```c
int main(void){
int i=42;
int c=55;
 prontf("La respuesta es %d\n y %d\n", i, c);
}
```

```c
main.c: In function ‘main’:
main.c:4:2: warning: implicit declaration of function ‘prontf’ [-Wimplicit-function-declaration]
    4 |  prontf("La respuesta es %d\n y %d\n", i, c);
      |  ^~~~~~
studio1.c: In function ‘prontf’:
studio1.c:2:2: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
    2 |  printf("La respuesta es %d\n", i);
      |  ^~~~~~
studio1.c:2:2: warning: incompatible implicit declaration of built-in function ‘printf’
studio1.c:1:1: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
  +++ |+#include <stdio.h>
    1 | void prontf(const char* s, int i){
La respuesta es 42
```

    El resultado es el mismo. En la declaración de printf que utilizamos en studio1.c hemos indicado que solamente se le pasan 2 argumentos, la cadena de caracteres y un int, por lo que no podremos agregar argumentos adicionales.

### Revisitar el punto anterior, esta vez utilizando un contrato de interfaz en un archivo header.

### Escribir el contrato en studio.h.

```c
#ifndef _STUDIO_H_INCULDED_
#define _STUDIO_H_INCULDED_
void prontf(const char*, int);
#endif
```

### Escribir hello9.c, un cliente que sí incluye el contrato.

```c
#include "studio.h" // Interfaz que importa
int main(void){
int i=42;
 prontf("La respuesta es %d\n", i);
}
```

### Escribir studio2.c, el proveedor que sí incluye el contrato.

```c
#include "studio.h" // Interfaz que exporta
#include <stdio.h> // Interfaz que importa
void prontf(const char* s, int i){
 printf("La respuesta es %d\n", i);
}
```

### Responder: ¿Qué ventaja da incluir el contrato en los clientes y en el proveedor.

    El contrato es quien indica en el preprocesador quienes son los archivos específicos donde buscar nuestra declaración y ademas le indica al vinculador cómo tiene que utilizar esa declaración.
    La ventaja es poder evitar errores por tener varias funciones con el mismo nombre declaradas dentro de nuestra ruta, o poder reemplazar declaraciones existentes por nuestras, ya que somos nosotros quienes controlamos por medio del contrato, la función a llamar.

## Crédito extra

### Investigue sobre bibliotecas. ¿Qué son? ¿Se puden distribuir? ¿Son portables? ¿Cuáles son sus ventajas y desventajas?. Desarrolle y utilice la biblioteca studio.

- Se le llama biblioteca al conjunto archivos .c y .h que contiene los contratos establecidos para utilizar funciones, clases, u otros datos en los .c.
- Las mismas ofrecen una solución para la reutilización de código, pudiendo transportarse a diferentes programas tan solo copiando el conjunto e incluyendo el header correspondiente en nuestro archivo a desarrollar.
- Las bibliotecas al ser portables se pueden distribuir y utilizar libremente.
- Su principal ventaja es el fácil acceso a código que ya existe y que suele ser muy utilizado, además de evitar tener que re-escribir estecódigo en varios archivos en el caso de que sea utilizado repetidas veces dentro de los mismos en nuestro programa.
- Su desventaja es que la inclusión conlleva un aumento del tamaño de programa, por lo que su uso debe ser justificado.

---------------------------------------

## Desarrollo de POW2, una función de potencia

### studio2.c

```c
#include "studio.h" // Interfaz que exporta
#include <stdio.h> // Interfaz que importa
void prontf(const char* s, int i){
 printf("La respuesta es %d\n", i);
}

int pow2(int base, int expn){
    int result = base;
    for(int i=0; i<expn; i++){
        result = result * base;
    }
    return result;
}
```

### studio.h

```c
#ifndef _STUDIO_H_INCULDED_
#define _STUDIO_H_INCULDED_
void prontf(const char*, int);
int pow2(int,int);
#endif
```

### hello10.c

```c
#include "studio.h" // Interfaz que importa
int main(void){
int i=4;
 pow2(i,4);
 prontf("La respuesta es %d\n", i);
}
```

    La respuesta es 1024