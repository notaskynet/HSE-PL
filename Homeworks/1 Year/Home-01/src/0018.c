#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void getValue(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


int main() {
    double a, b, c, R;

    getValue("%le", &a);
    getValue("%le", &b);
    getValue("%le", &c);
    getValue("%le", &R);
    printf("%f\n", 2 * R * sin(a));
    printf("%f\n", 2 * R * sin(b));
    printf("%f\n", 2 * R * sin(c));
    return 0;
}