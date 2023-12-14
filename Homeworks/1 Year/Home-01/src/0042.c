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
    double x, y, p_sum, mul;

    getValue("%le", &x);
    getValue("%le", &y);
    
    p_sum = (x + y) / 2;
    mul = 2 * x * y;
    if(x < y) {
        x = p_sum;
        y = mul;
    } else {
        x = mul;
        y = p_sum;
    }
    
    printf("%f\n", x);
    printf("%f\n", y);

    return 0;
}