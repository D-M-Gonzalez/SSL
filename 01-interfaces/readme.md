# Ejercicio Nº1 Sintaxis y Semántica de los Lenguajes

## Consigna

    Escriba un programa para imprimir la tabla correspondiente de
    Celsius a Fahrenheit

    Reescriba el programa de conversión de temperatura de la sección
    1.2 para que use una función de conversión.

## Objetivos

- Aplicar el uso de interfaces y módulos.
- Construir un programa formado por más de una unidad de traducción.
- Comprender el proceso de traducción o Build cuando intervienen varios archivos fuente.
- Aplicar el uso de Makefile.

## Herramientas

- Se utilizó MinGW version 6.3.0
- Se utilizó GCC como compilador version 11.2.0
- Se utilizó c18 como standar
- Se utilizó mingw32-make.exe para usar el Makefile

## ¿Cómo utilizar el programa?

1. Compilar con la línea mingw32-make.exe ConversionTest.exe
2. Ejecutar ConversionTest.exe
3. Si da OK, limpiar el directorio con mingw32-make.exe clean
4. Compilar el programa principal con mingw32-make.exe TablasDeConversion.exe
5. Ejecutar TablasDeConversion.exe
6. Ingresar con los dígitos 1 o 2 si se quieren imprimir una tabla de celsius a fahrenheit o biseversa
7. Ingresar el piso, el tope y el tamaño de los saltos de la tabla
8. Verificar los datos ingresados e ingresar 1 si son correctos, 0 si se quieren corregir o 2 para salir

## Datos del Alumno

- Github: D-M-Gonzalez
- Legajo: 137125-3
- Apellido: Gonzalez
- Nombre: Damian Martin


### 01-interfaces

    Se realiza un programa capaz de imprimir una tabla de conversión de temperaturas en ambos sentidos, con sus parámetros ingresados por consola.
    Ademas, se incluye un ejecutable para poder probar la función de conversión.

