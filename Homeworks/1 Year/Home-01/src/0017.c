#include <stdio.h>
#include <stdlib.h>

#define PI 3.14


void getValue(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


int main() {
    double Square, R, r;

    r = 20.0f;
    getValue("%le", &R);
    Square =  PI * (R * R - r * r);
    printf("%f\n", Square);

    return 0;
}