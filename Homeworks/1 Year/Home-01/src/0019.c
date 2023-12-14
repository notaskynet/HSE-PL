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
    double v1, v2, a1, a2, s;
    double a, b, D, t;

    getValue("%le", &v1);
    getValue("%le", &v2);
    getValue("%le", &a1);
    getValue("%le", &a2);
    getValue("%le", &s);
    a = (a1 + a2) / 2;
    b = v1 + v2;
    D = b * b + 4 * a * s;
    t = (b + sqrt(D)) / (2 * b);
    printf("%f\n", t);

    return 0;
}