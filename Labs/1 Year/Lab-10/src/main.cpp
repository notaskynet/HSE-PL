#include <iostream>
#include "matrix.hpp"

int main() {
    Matrix<int> m1(3, 3);
    Matrix<int> m2(3, 3);
    Matrix<int> m3(3, 3);
    Matrix<int> A(3, 3);
    Matrix<int> b(3, 1);

    std::cout << "Введите первую матрицу\n";
    std::cin >> m1;

    std::cout << "Введите вторую матрицу\n";
    std::cin >> m2;

    // Проверка действий с матрицами
    std::cout << m1 + m2 << '\n';
    std::cout << m1 - m2 << '\n';
    std::cout << m1 * m2 << '\n';

    // Поверка действий с числами
    std::cout << m1 * 5 << '\n';
    std::cout << 5 * m1 << '\n';

    // Проверка  LU-разложения
    std::cin >> A;
    A.LU(&m1, &m2, &m3);

    std::cout << m1 << '\n';
    std::cout << m2 << '\n';

    // Проверка решения системы с помощью LU разложения
    std::cin >> b;
    std::cout << A.Solve(b);


}