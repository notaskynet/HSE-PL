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
    int n, i, count, a0, a1, a2;

    count = 0;
    getValue("%d", &n);
    getValue("%d", &a0);
    getValue("%d", &a1);
    for(i = 2; i < n; i++) {
        getValue("%d", &a2);
        if(2 * a1 < (a0 + a2)) {
            count++;
        }
        a0 = a1;
        a1 = a2;
    }
    printf("%d", count);

    return 0;
}