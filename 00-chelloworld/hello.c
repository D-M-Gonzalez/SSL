#include <stdio.h>

int main(void) {
  FILE *output = fopen("output.txt","w");
  fprintf(output,"Hello World!");
  return 0;
}