#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void getValue_INT(char format[], int *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


void getValue_DOUBLE(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


int main() {
    double x, y, z;
    int k, m;

    getValue_INT("%d", &k);
    getValue_INT("%d", &m);
    getValue_DOUBLE("%le", &x);
    getValue_DOUBLE("%le", &y);
    getValue_DOUBLE("%le", &z);

    if (k < m * m) {
        x = abs(x);
        y -= 0.5;
        z -= 0.5;
    }
    else if (k == m * m) {
        x -= 0.5;
        y = abs(y);
        z -= 0.5;
    }
    else {
        x -= 0.5;
        y -= 0.5;
        z = abs(z);
    }

    printf("%f\n", x);
    printf("%f\n", y);
    printf("%f\n", z);

    return 0;
}