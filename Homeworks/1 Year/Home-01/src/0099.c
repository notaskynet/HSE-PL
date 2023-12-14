#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NULL_VALUE 0.00000001

void getValueINT(char format[], long long int *valueAdd) {
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


void calc_A(long long int i, double *a, double *b);
void calc_B(long long int i, double *a, double *b);


void calc_A(long long int i, double *a, double *b) {
    if (a[i] == NULL_VALUE) {
        if(b[i - 1] == NULL_VALUE) {
            calc_B(i - 1, a, b);
        }
        if(a[i - 1] == NULL_VALUE) {
            calc_A(i - 1, a, b);
        }
        a[i] = 2 * b[i - 1] + a[i - 1];
    }
}


void calc_B(long long int i, double *a, double *b) {
    if (b[i] == NULL_VALUE) {
        if(b[i - 1] == NULL_VALUE) {
            calc_B(i - 1, a, b);
        }
        if(a[i - 1] == NULL_VALUE) {
            calc_A(i - 1, a, b);
        }
        b[i] = 2 * pow(a[i - 1], 2) + b[i - 1];
    }
}


int main() {
    long long int n, i;
    double sum, u, v, fac;
    double *a, *b;

    sum = 0.0f; fac = 1.0f;
    getValueINT("%lld", &n);
    getValueDOUBLE("%le", &u);
    getValueDOUBLE("%le", &v);
    a = malloc(sizeof(double) * (n + 1));
    b = malloc(sizeof(double) * (n + 1));

    a[1] = u; b[1] = v;
    for(i = 2; i < n + 1; i++) {
        a[i] = NULL_VALUE;
        b[i] = NULL_VALUE;
    }
    for(i = 2; i < n + 1; i++) {
        calc_A(i, a, b);
        calc_B(i, a, b);
    }
    for(i = 1; i < n + 1; i++) {
        fac *= (double) (i + 1);
        sum += (a[i] * b[i]) / fac;
    }
    printf("%f\n", sum);
    free(a);
    free(b);

    return 0;
}