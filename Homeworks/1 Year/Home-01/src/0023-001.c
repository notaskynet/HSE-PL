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


double calculateHeignt(double a, double b, double c, double main_side) {
    double p, h;

    p = (a + b + c) / 2;
    h = (2 / main_side) * sqrt(p * (p - a) * (p - b) * (p - c));

    return h;

}

int main() {
    double h_a, h_b, h_c;
    double a, b, c;

    getValue("%le", &a);
    getValue("%le", &b);
    getValue("%le", &c);
    
    h_a = calculateHeignt(a, b, c, a);
    h_b = calculateHeignt(a, b, c, b);
    h_c = calculateHeignt(a, b, c, c);
    printf("%f\n", h_a);
    printf("%f\n", h_b);
    printf("%f\n", h_c);

    return 0;
}