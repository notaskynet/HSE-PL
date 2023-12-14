#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void getValue(char format[], int *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


void calc_x(int i, double *x, double *y);
void calc_y(int i, double *x, double *y);


void calc_x(int i, double *x, double *y) {
    if (x[i] == -1) {
        if(x[i - 1] == -1) {
            calc_x(i - 1, x, y);
        }
        x[i] = 0.3f * x[i - 1];
    }
}


void calc_y(int i, double *x, double *y) {
    if (y[i] == -1) {
        if(x[i - 1] == -1) {
            calc_x(i - 1, x, y);
        }
        if(y[i - 1] == -1) {
            calc_y(i - 1, x, y);
        }
        y[i] = x[i - 1] + y[i - 1];
    }
}


int main() {
    double *x, *y;
    double sum;
    int n, i;

    sum = 0;
    getValue("%d", &n);
    x = malloc(sizeof(double) * (n + 1));
    y = malloc(sizeof(double) * (n + 1));

    x[1] = 1; y[1] = 1;
    for(i = 2; i < n + 1; i++) {
        x[i] = -1; y[i] = -1;
    }
    for(i = 2; i < n + 1; i++) {
        calc_y(i, x, y);
        calc_x(i, x, y);
    }
    for(i = 1; i < n + 1; i++) {
        sum += x[i] / (1 + abs(y[i]));
    }
    printf("%f\n", sum);
    free(x);
    free(y);

    return 0;
}