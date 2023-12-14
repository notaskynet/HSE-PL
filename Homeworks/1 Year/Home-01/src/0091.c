#include <stdlib.h>
#include <stdio.h>


void getValue(char format[], int *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


double CalSub(int n) {
    if(n == 0) {
        return 1;
    } else {
        return n * CalSub(n - 1) + 1 / n;
    }
}


int main() {
    double a;
    int n;

    getValue("%d", &n);
    a = CalSub(n);
    printf("%f\n", a);

    return 0;
}