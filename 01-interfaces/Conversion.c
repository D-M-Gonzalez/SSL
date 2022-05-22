#include "Conversion.h"

double Celsius(double farh){
    return (5.0 / 9.0) * (farh - 32);
}
double Fahrenheit(double celsius){
    return 32 + (9.0 / 5.0 * celsius);
}