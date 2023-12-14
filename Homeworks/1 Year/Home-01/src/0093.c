#include <stdlib.h>
#include <stdio.h>


void getValueINT(char format[], int *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


void getValueDOUBLE(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


double CalSub(int n, double q, double r, \
            double c, double d, double b) {
    if (n == 0) {
        return c;
    } else if (n == 1) {
        return d;
    } else {
        return q * CalSub(n - 1, q, r, c, d, b) + r * CalSub(n - 2, q, r, c, d, b) + b;
    }
}


int main() {
    double a, q, r, c, d, b;
    int n;

    getValueDOUBLE("%le", &q);
    getValueDOUBLE("%le", &r);
    getValueDOUBLE("%le", &c);
    getValueDOUBLE("%le", &d);
    getValueDOUBLE("%le", &b);
    getValueINT("%d", &n);
    a = CalSub(n, q, r, c, d, b);
    printf("%f\n", a);

    return 0;
}