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


int calculateTime(int m, int n, int delta) {
    return ceil((60.0f * m - 12.0f * n) / 11.0f) + delta;
}


int main() {
    int m, n, time;

    getValue("%d", &m);
    getValue("%d", &n);
    time = calculateTime(m, n, 0);
    if(time < 0) {
        time = calculateTime(m + 1, 0, 60 - n);
    }
    printf("%d\n", time);
    return 0;
}