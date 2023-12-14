
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14f

void getValue(char format[], int *valueAdd) {
    int err_check;

    err_check = scanf(format, valueAdd);
    if(1 != err_check) {
        exit(1);
    }
}


int calculateTime(int m, int n, int delta) {
    return ceil((60.0f * m - 12.0f * n) / 11.0f) + delta;
}


int main() {
    double phi_hours, phi_mins, time;
    int hours, mins; 

    getValue("%le", &phi_hours);
    
    time = phi_hours / (2.0f * PI) * 12;
    hours = (int) time;
    mins = ceil((time - (double) hours) * 60.0f);
    phi_mins = (mins / 60.0f) * 2 * PI;

    printf("%f\n", phi_mins);
    printf("%d\n", hours);
    printf("%d\n", mins);

    return 0;
}