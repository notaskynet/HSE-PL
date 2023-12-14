#include <stdlib.h>
#include <stdio.h>


void getValue(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


void foo(double *p_x) {
    if(*p_x > 0) {
        (*p_x) *= (*p_x);
    }
}


int main() {
    double x, y, z;

    getValue("%le", &x);
    getValue("%le", &y);
    getValue("%le", &z);

    foo(&x);
    foo(&y);
    foo(&z);

    printf("%f", x);
    printf("%f", y);
    printf("%f", z);

    return 0;
}