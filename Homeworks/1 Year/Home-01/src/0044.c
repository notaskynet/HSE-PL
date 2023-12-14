#include <stdlib.h>
#include <stdio.h>


void getValue(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


int main() {
    double x, y, z;
    double *p_min;

    getValue("%le", &x);
    getValue("%le", &y);
    getValue("%le", &z);

    if ((x + y + z) < 1.0) {
        if ((x < y) && (x < z)) x = (y + z) / 2;
        else if ((y < x) && (y < z)) y = (x + z) / 2;
        else z = (y + z) / 2;
    } else {
        if (x < y) x = (y + z) / 2;
        else y = (x + z) / 2;
    }

    printf("%f\n", x);
    printf("%f\n", y);
    printf("%f\n", z);

    return 0;
}