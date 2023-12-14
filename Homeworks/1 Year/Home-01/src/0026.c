#include <stdio.h>
#include <stdlib.h>


void getValue(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


int main() {
    double R, PHI;

    R = 13.7;
    getValue("%le", &PHI);
    printf("%f\n", PHI * R * R);
    return 0;
}