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


double calc(int i, double *values, size_t arr_size) {
    if(values[i] != -1) {
        return values[i];
    } else {
        values[i] = calc(i - 2, values, arr_size) +
                    calc(i - 1, values, arr_size) / pow(2, i - 1);
        return values[i];
    }
}


int main() {
    double *a;
    double mul;
    int n, i;

    mul = 1;
    getValue("%d", &n);
    a = malloc(sizeof(double) * (n + 1));

    a[0] = 1;
    a[1] = 1;
    for(i = 2; i < n + 1; i++) {
        a[i] = -1;
    }
    for(i = 2; i < n + 1; i++) {
        a[i] = calc(i, a, n + 1);
    }
    for(i = 0; i < n + 1; i++) {
        mul *= a[i];
    }
    printf("%f\n", mul);
    free(a);

    return 0;
}