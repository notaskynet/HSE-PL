#include <iostream>

#ifndef Matrix_h
#define Matrix_h 20221202L

class Matrix {
    size_t row;
    size_t col;
    double **data;
public:
    Matrix();
    Matrix(const Matrix&);
    Matrix(size_t, size_t);
    ~Matrix();
    
    double& at(size_t, size_t);
    const double& at(size_t, size_t) const ;

    Matrix& operator=(const Matrix&);

    friend Matrix operator+(const Matrix&, const Matrix&);
    friend Matrix operator-(const Matrix&, const Matrix&);
    friend Matrix operator*(const Matrix&, const Matrix&);
    friend Matrix operator*(const double, const Matrix&);
    friend Matrix operator*(const Matrix&, const double);

    friend std::ostream& operator<<(std::ostream&, Matrix);
    friend std::istream& operator>>(std::istream&, Matrix&);

    void Transpose();
    Matrix Upper() const;
    bool is_triangular() const;
};

#endif /*Matrix_h*/

