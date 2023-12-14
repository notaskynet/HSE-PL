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


double calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}


int main() {
    double x1, x2, x3, y1, y2, y3;
    double a, b, c, P;

    getValue("%le", &x1);
    getValue("%le", &y1);
    getValue("%le", &x2);
    getValue("%le", &y2);
    getValue("%le", &x3);
    getValue("%le", &y3);
    
    a = calculateDistance(x1, y1, x2, y2);
    b = calculateDistance(x2, y2, x3, y3);
    c = calculateDistance(x1, y1, x3, y3);

    P = a + b + c;
    printf("%f\n", P);

    return 0;
}