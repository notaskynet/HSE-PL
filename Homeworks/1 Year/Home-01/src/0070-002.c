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


int mod(int m, int base) {
    if(m < 0) {
        return base + m % base;
    } else {
        return m % base;
    }
}


int calculateTime(int m, int n, int delta) {
    int time;
    
    time = ceil((60.0f * m - 12.0f * n) / 11.0f) + delta;
    if(time < 0) {
        time = calculateTime(m + 1, 0, 60 - n);
    }
    return time;
}


int main() {
    int m, n, time1, time2;

    getValue("%d", &m);
    getValue("%d", &n);
    time1 = calculateTime(mod(m - 4, 12), n, 0);
    time2 = calculateTime(mod(m + 4, 12), n, 0);
    printf("%d\n", min(time1, time2));
    return 0;
}