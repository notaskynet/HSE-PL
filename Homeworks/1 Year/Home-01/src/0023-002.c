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


double calculateMedian(double a, double b, double c) {
    double p, m;

    p = (a + b + c) / 2;
    m = 1 / 2 * sqrt(2 * a * a - 2 * b * b - c * c);

    return m;

}

int main() {
    double m_a, m_b, m_c;
    double a, b, c;

    getValue("%le", &a);
    getValue("%le", &b);
    getValue("%le", &c);
    
    m_a = calculateMedian(b, c, a);
    m_b = calculateMedian(a, c, b);
    m_c = calculateMedian(a, b, c);
    printf("%f\n", m_a);
    printf("%f\n", m_b);
    printf("%f\n", m_c);

    return 0;
}