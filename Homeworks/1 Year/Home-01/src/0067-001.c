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
    int n, count;

    count = 0;
    getValue("%d", &n);
    while(n != 0) {
        count++;
        n /= 10;
    }

    printf("%d", count);

    return 0;
}