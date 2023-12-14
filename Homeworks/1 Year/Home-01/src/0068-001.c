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
    int n, n1, n2;

    getValue("%d", &n);
    n1 = n;
    while(n != 0) {
        n2 = 10 * n2 + n % 10;
        n /= 10;
    }
    if(n1 == n2) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}