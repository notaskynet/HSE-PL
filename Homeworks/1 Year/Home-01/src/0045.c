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
    double a, b, c, d;

    getValue("%le", &a);
    getValue("%le", &b);
    getValue("%le", &c);
    getValue("%le", &d);

    if((a <= b) && (b <= c) && (c <= d)) {
        a = d;
        b = d;
        c = d;
    } else if((a > c) && (c > b) && (b > d)) {
        a += 0;
    } else {
        a *= a;
        b *= b;
        c *= c;
        d *= d;
    }
    printf("%f\n", a);
    printf("%f\n", b);
    printf("%f\n", c);
    printf("%f\n", d);
    
    return 0;
}