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


void check(int sum) {
    int i;

    for(i = 1; i < 76; i++) {
        if(i * i == sum) {
            printf("YES\n");
            return;
        }
    }
    printf("NO\n");
}


int main() {
    int n, sum;

    sum = 0;
    getValue("%d", &n);
    while(n != 0) {
        sum += n % 10;
        n /= 10;
    }

    sum *= pow(sum, 2);
    check(sum);

    return 0;
}