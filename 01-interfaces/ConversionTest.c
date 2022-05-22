#include<assert.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "Conversion.h"

bool testDoubles(double a, double b, double precision);

int main(void){
    double ctf = Fahrenheit(0.0);
    double ftc = Celsius(0.0);

    assert(testDoubles(ctf,32.0,0.1) == true);
    puts("Celsius to fahrenheit is OK");
    assert(testDoubles(ftc,-17.78,0.1) == true);
    puts("Fahrenheit to celsius is OK");
}

bool testDoubles(double a, double b, double precision){
    return abs(a - b) < precision;
}

