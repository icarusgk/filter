#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int a = 27;
    int b = 28;
    int c = 28;

    float result = (float) (a + b + c) / (float) 3; 

    int avg = round(result);
    printf("Average: %i\n", avg);
}