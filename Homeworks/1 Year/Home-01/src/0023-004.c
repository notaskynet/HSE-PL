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
    double a, b, c;
    double r, R, p;

    getValue("%le", &a);
    getValue("%le", &b);
    getValue("%le", &c);
    
    p = (a + b + c) / 2;
    R = (a * b * c) / (4 * sqrt((p * (p - a) * (p - b) * (p - c))));
    r = sqrt((p - a) * (p - b) * (p - c) / p);
    
    printf("%f\n", R);
    printf("%f\n", r);

    return 0;
}