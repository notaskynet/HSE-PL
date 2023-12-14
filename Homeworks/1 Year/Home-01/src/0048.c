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


void findRoots(double a, double b, double c, double D) {
    if (D > 0) {
        printf("%f\n", (-1 * b + sqrt(D)) / (2 * a));
        printf("%f\n", (-1 * b - sqrt(D)) / (2 * a));
    } else {
        printf("%f\n", (-1 * b) / (2 * a));
    }
}


int main() {
    double a, b, c, D;

    getValue("%le", &a);
    getValue("%le", &b);
    getValue("%le", &c);

    D = b * b - 4 * a * c;
    if(D >= 0) {
        findRoots(a, b, c, D);
    } else {
        printf("NO\n");
    }

    return 0;
}