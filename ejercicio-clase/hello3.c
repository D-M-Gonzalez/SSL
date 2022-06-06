int printf(const char * restrict s, ...);
int main(void){
 int i=42;
 prontf("La respuesta es %d\n");

 /*const char * s; //definicion de un puntero constante a un char s
 s  const char * //s es del tipo const char *
 *s const char //*s es del tipo const char
 *s = 'b' //*s si es igual a b no va a variar, siempre va a ser b
 s = c //Pero s si puede cambiar por c
 printf("hola")*/