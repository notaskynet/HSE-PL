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

double CalSub_U(int n);
double CalSub_V(int n);

double CalSub_U(int n) {
    if((n == 1) || (n == 2)) {
        return 0;
    } else {
        return (CalSub_U(n - 1) - CalSub_U(n - 2) * CalSub_V(n - 1) - CalSub_V(n - 2)) \
        / (1 + pow(CalSub_U(n - 1), 2) +  pow(CalSub_V(n - 1), 2));
    }
}


double CalSub_V(int n) {
    if((n == 1) || (n == 2)) {
        return 1;
    } else {
        return (CalSub_U(n - 1) - CalSub_V(n - 1)) \
        / (abs(CalSub_U(n - 2) + CalSub_V(n - 2)) + 2);
    }
}


int main() {
    double a;
    int n;

    getValue("%d", &n);
    a = CalSub_V(n);
    printf("%f\n", a);

    return 0;
}