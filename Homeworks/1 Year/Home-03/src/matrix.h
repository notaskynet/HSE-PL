#ifndef Matrix_h
#define Matrix_h 20221115L

#include <cstddef>
#ifndef Matrix

class Matrix {
    size_t rows;
    size_t cols;
    double *data;

public:
    Matrix();
    Matrix(const Matrix&);
    Matrix(size_t, size_t);
    ~Matrix();

    void print() const;
    static void print(const Matrix&);

    double& at(size_t, size_t);
    const double& at(size_t, size_t) const ;

    Matrix add(const Matrix&, const Matrix&);
    Matrix mul(const Matrix&, const Matrix&);
    Matrix mul(double, const Matrix&);

    void mul(double);
    void Transpose();
};

#endif /*Matrix_h*/
