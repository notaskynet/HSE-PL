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
    if((n == 1) || (n == 2)) {
        return 0;
    } else if (n = 3){
        return 1.5f;
    } else {
        return ((n + 1) / (n * n + 1)) * CalSub(n - 1)\
        - CalSub(n - 2) * CalSub(n - 3);
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