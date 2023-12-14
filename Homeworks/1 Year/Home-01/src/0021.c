#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14
#define EQUAL c * pow(x1, 3) + d * pow(x2, 2)

void getValue(char format[], double *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


int main() {
    double part1, part2, part3; // Части, на которые мы разбили выражение
    double D, x1, x2, rez; // Вспомогательные переменные
    double c, d;

    getValue("%le", &c);
    getValue("%le", &d);

    D = 9 + 4 * abs(c * d);
    x1 = (3 + sqrt(D)) / 2;
    x2 = (3 - sqrt(D)) / 2;
    part1 = pow(sin(abs(EQUAL - c * d)), 3);
    part2 = sqrt(pow(EQUAL - x1, 2) + PI);
    part3 = tan(EQUAL - x1);
    rez = abs(part1/part2) + part3;

    printf("%f\n", rez);
    return 0;
}