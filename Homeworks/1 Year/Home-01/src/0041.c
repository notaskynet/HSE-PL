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


int checkRange(double *p_x) {
    double inf = 1.0, sup = 3.0;

    if((*p_x > inf) && (*p_x < sup)) {
        return 0;
    } else {
        return 1;
    }
}


int main() {
    double x, y, z;

    getValue("%le", &x);
    getValue("%le", &y);
    getValue("%le", &z);

    if(checkRange(&x)) printf("%f", x);
    if(checkRange(&y)) printf("%f", y);
    if(checkRange(&z)) printf("%f", z);

    return 0;
}