#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void getValue(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


int main() {
    double x, y, z, max_side;

    getValue("%le", &x);
    getValue("%le", &y);
    getValue("%le", &z);

    max_side = max(x, max(y, z));
    if(max_side < (x + y + z - max_side)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}