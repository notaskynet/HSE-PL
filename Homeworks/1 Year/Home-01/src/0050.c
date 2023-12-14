#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define DELTA 0.0001


void getValue(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}



int main() {
    double a1, b1, c1, a2, b2, c2, x, y;

    getValue("%le", &a1);
    getValue("%le", &b1);
    getValue("%le", &c1);
    getValue("%le", &a2);
    getValue("%le", &b2);
    getValue("%le", &c2);

    if(abs(a1 * b2 - a2 * b1) >= DELTA) {
        x = (c2 * b1 - c1 * b2) / (a1 * b2 - a2 * b1);
        y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
        printf("%f\n", x);
        printf("%f\n", y);
    } else {
        printf("NO\n");
    }

    return 0;
}