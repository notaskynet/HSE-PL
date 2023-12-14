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
    double x1, x2, y1, y2, d;

    getValue("%le", &x1);
    getValue("%le", &y1);
    getValue("%le", &x2);
    getValue("%le", &y2);
    
    d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    
    printf("%f\n", d);

    return 0;
}