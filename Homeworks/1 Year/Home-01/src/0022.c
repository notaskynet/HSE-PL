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
    double a, b, angle, S;

    getValue("%le", &a);
    getValue("%le", &b);
    getValue("%le", &angle);
    
    S = pow((a - b) / 2, 2) * tan(angle);
    printf("%f\n", S);

    return 0;
}