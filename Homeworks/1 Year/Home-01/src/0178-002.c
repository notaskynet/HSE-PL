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
    int i, n, temp, count;

    count = 0;
    getValue("%d", &n);
    for(i = 0; i < n; i++) {
        getValue("%d", &temp);
        if((temp % 3 == 0) && (temp % 5 != 0)) {
            count++;
        }
    }
    printf("%d", count);

    return 0;
}