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


int checkRange(double *p_x) {
    double inf = 0.5, sup = 2.0;

    if((*p_x > inf) && (*p_x < sup)) {
        return 0;
    } else {
        return 1;
    }
}


int main() {
    double x, y;

    getValue("%le", &x);
    getValue("%le", &y);

    if((x < 0) && (y < 0)) {
        x = abs(x);
        y = abs(y);
    }
    else if(((x < 0) && (y >= 0)) || ((x >= 0) && (y < 0))) {
        x += 0.5;
        y += 0.5;
    }
    else if(!(checkRange(&x) || checkRange(&y))) {
        x /= 10;
        y /= 10;
    }

    if(checkRange(&x)) printf("%f", x);
    if(checkRange(&y)) printf("%f", y);

    return 0;
}