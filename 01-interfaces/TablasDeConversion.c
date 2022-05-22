#include <stdio.h>
#include "Conversion.h"

struct inputs{
    int lower;
    int upper;
    int steps;
};

struct inputs conversionInputs(char* selection);
void PrintFilaCTF(int row);
void PrintFilaFTC(int row);
void PrintFilas(struct inputs values,void(*f)());
void PrintTablaCelsius(struct inputs values);
void PrintTablaFahrenheit(struct inputs values);

void (*CTFTable) (int)=PrintFilaCTF;
void (*FTCTable) (int)=PrintFilaFTC;

int main(void){

    struct inputs celsiusToFahr;
    struct inputs fahrToCelsius;
    int selection = 0;
    int confirm = 0;

    printf("Type 1 to print a Celsius to Fahrenheit table or 2 to print a Fahrenheit to Celsius one: ");
    scanf("%d",&selection);
    printf("\n");

    switch (selection)
    {
    case 1:
        while ( confirm != 1 && confirm != 2 ){
            celsiusToFahr = conversionInputs("celsius");
            printf("You entered:\n%d lower table limit\n%d upper table limit\n%d table steps\nType 0 to retry\nType 1 to accept and continue\nType 2 to leave\nInput: ",celsiusToFahr.lower,celsiusToFahr.upper,celsiusToFahr.steps);
            scanf("%d",&confirm);
            printf("\n");
        }
        switch (confirm)
            {
            case 1:
                PrintTablaCelsius(celsiusToFahr);
                break;
            case 2:
                printf("Function aborted by the user");
                break;
            default:
                printf("Invalid input number");
                break;
            }
        break;
    case 2:
        while ( confirm != 1 && confirm != 2 ){
            fahrToCelsius = conversionInputs("fahrenheit");
            printf("You entered:\n%d lower table limit\n%d upper table limit\n%d table steps\nType 0 to retry\nType 1 to accept and continue\nType 2 to leave\nInput: ",celsiusToFahr.lower,celsiusToFahr.upper,celsiusToFahr.steps);
            scanf("%d",&confirm);
            printf("\n");

        }
        switch (confirm)
            {
            case 1:
                PrintTablaFahrenheit(fahrToCelsius);
                break;
            case 2:
                printf("Function aborted by the user");
                break;
            default:
                printf("Invalid input number");
                break;
            }
        break;
    default:
        printf("Invalid selection\n");
        printf("\n");
        break;
    }
}

struct inputs conversionInputs(char* selection){
    struct inputs values = {.lower = 0,.upper = 0,.steps = 0};

    printf( "Enter lower %s limit: ",selection);
    scanf("%d",&values.lower);
    printf("\n");
    printf( "Enter upper %s limit: ",selection);
    scanf("%d",&values.upper);
    printf("\n");
    printf( "Enter steps for %s table: ",selection);
    scanf("%d",&values.steps);
    printf("\n");

    return values;
}

void PrintFilaFTC(int row){
    printf("%3d %6.1f\n", row, Celsius(row) ); 
}

void PrintFilaCTF(int row){
    printf("%3d %6.1f\n", row, Fahrenheit(row) ); 
}

void PrintFilas(struct inputs values,void(*f)()){
    for(int row = values.lower; row <= values.upper; row = row + values.steps)
    f(row);
}

void PrintTablaCelsius(struct inputs values){
    printf("Celsius Fahrenheit\n");
    PrintFilas(values,CTFTable);
}

void PrintTablaFahrenheit(struct inputs values){
    printf("Fahrenheit Celsius\n");
    PrintFilas(values,FTCTable);
}