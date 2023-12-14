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


double calculateBisector(double a, double b, double c) {
    double e, d, bis;

    e = c * a / (a + b);
    d = c * b / (a + b);
    bis = sqrt(a * b - e * d);

    return bis;

}

int main() {
    double b_a, b_b, b_c;
    double a, b, c;

    getValue("%le", &a);
    getValue("%le", &b);
    getValue("%le", &c);
    
    b_a = calculateBisector(b, c, a);
    b_b = calculateBisector(a, c, b);
    b_c = calculateBisector(a, b, c);
    printf("%f\n", b_a);
    printf("%f\n", b_b);
    printf("%f\n", b_c);

    return 0;
}