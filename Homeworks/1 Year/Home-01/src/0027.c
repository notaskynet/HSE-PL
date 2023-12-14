#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14

void getValue(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


double calculateAngle(double a, double b, double target) {
    return acos((a * a + b * b - target * target) / (2 * a * b)) * 180 / PI;
}


int main() {
    double angle1, angle2, angle3;
    double a, b, c;

    getValue("%le", &a);
    getValue("%le", &b);
    getValue("%le", &c);

    angle1 = calculateAngle(a, b, c);
    angle2 = calculateAngle(a, c, b);
    angle3 = calculateAngle(c, b, a);

    printf("%f\n", angle1);
    printf("%f\n", angle2);
    printf("%f\n", angle3);
    return 0;
}