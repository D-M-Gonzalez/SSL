#include "studio.h" // Interfaz que exporta
#include <stdio.h> // Interfaz que importa
void prontf(const char* s, int i){
 printf("La respuesta es %d\n", i);
}

int pow2(int base, int expn){
    int result = 1;
    for(int i=0; i<expn; i++){
        result = result * base;
    }
    return result;
}