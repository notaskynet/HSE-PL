#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void getValue(char format[], long long int *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


void calc_A(int i, double *a, double *b);
void calc_B(int i, double *a, double *b);


void calc_A(int i, double *a, double *b) {
    if (a[i] == -1) {
        if(b[i - 1] == -1) {
            calc_B(i - 1, a, b);
        }
        if(a[i - 1] == -1) {
            calc_A(i - 1, a,b);
        }
        a[i] = 3 * b[i - 1] + 2 * a[i - 1];
    }
}


void calc_B(int i, double *a, double *b) {
    if (b[i] == -1) {
        if(b[i - 1] == -1) {
            calc_B(i - 1, a, b);
        }
        if(a[i - 1] == -1) {
            calc_A(i - 1, a, b);
        }
        b[i] = 2 * a[i - 1] + b[i - 1];
    }
}


int main() {
    double *a, *b;
    double sum;
    long long int n, i, fac;

    sum = 0; fac = 1;
    getValue("%lld", &n);
    a = malloc(sizeof(double) * (n + 1));
    b = malloc(sizeof(double) * (n + 1));

    a[1] = 1; b[1] = 1;
    for(i = 2; i < n + 1; i++) {
        a[i] = -1; b[i] = -1;
    }
    for(i = 2; i < n + 1; i++) {
        calc_A(i, a, b);
        calc_B(i, a, b);
    }
    for(i = 1; i < n + 1; i++) {
        fac *= i;
        sum += pow(2, i) / ((1 + pow(a[i], 2) + + pow(b[i], 2)) * fac);
    }
    printf("%f\n", sum);
    free(a);
    free(b);

    return 0;
}