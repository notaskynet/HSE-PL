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


int main() {
    int n, i, count, a, fac = 1;

    count = 0;
    getValue("%d", &n);
    for(i = 1; i < n + 1; i++) {
        getValue("%d", &a);
        fac *= i;
        if((pow(2, i) < a) && (a < fac)) {
            count++;
        }
    }
    printf("%d", count);

    return 0;
}