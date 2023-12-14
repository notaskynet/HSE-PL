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
    double x, y, temp;

    getValue("%le", &x);
    getValue("%le", &y);

    if(x <= y) {
        x = 0;
    }
    printf("%f\n", x);
    printf("%f\n", y);

    return 0;
}