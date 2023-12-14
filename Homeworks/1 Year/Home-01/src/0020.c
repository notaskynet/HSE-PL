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
    double a, d, n, S;

    getValue("%le", &a);
    getValue("%le", &d);
    getValue("%le", &n);
    S = (2 * a + (n - 1) * d) * n / 2;
    printf("%f\n", S);

    return 0;
}