#include <stdlib.h>
#include <stdio.h>


void getValue(char format[], int *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


int GCD(int m, int n) {
    while((n != 0) && (m != 0)) {
        if (m > n) {
            m = m % n;
        } else {
            n = n % m;
        }
    }
    return m + n;
}


int main() {
    int m, n, d;

    getValue("%d", &m);
    getValue("%d", &n);
    d = GCD(m, n);
    printf("%d\n", m / d);
    printf("%d\n", n / d);
}