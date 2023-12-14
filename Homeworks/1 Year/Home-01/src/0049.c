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


void findRoots(double a, double b, double c, double D) {
    if (D > 0) {
        printf("%f\n", (-1 * b + sqrt(D)) / (2 * a));
        printf("%f\n", (-1 * b - sqrt(D)) / (2 * a));
    } else {
        printf("%f\n", (-1 * b) / (2 * a));
    }
}


int main() {
    double a, b, c, h, D;

    getValue("%le", &h);

    a = sqrt((abs(sin(8 * h)) + 17) / (1 - sin(4 * h) * cos(pow(h, 2) + 18)));
    b = 1 - sqrt( 3 / (3 + abs(tan(a * pow(h, 2)) - sin(a * h))));
    c = a * pow(h, 2) * sin(b * h) + b * pow(h, 3) * cos(a * h);

    D = b * b - 4 * a * c;
    if(D >= 0) {
        findRoots(a, b, c, D);
    } else {
        printf("NO\n");
    }

    return 0;
}