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
    int temp, n, i, sum;

    sum = 0;
    getValue("%d", &n);
    for(i = 1; i <= n; i++) {
        temp = pow(i, 3) - 3 * i * pow(n, 2) + n;
        if((temp % 3 == 0) && ((temp / 3) % 2 != 0)) {
            sum += temp;
        }
    }
    printf("%d\n", sum);
    return 0;
}