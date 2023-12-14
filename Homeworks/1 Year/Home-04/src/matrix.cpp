#include "matrix.h"
#include <iostream>

#define EPS 0.0001f // Epsilon

Matrix::Matrix()
: row(0), col(0), data(NULL) {}

Matrix::Matrix(const Matrix& other)
: row(other.row), col(other.col) {
    try {
        data = new double* [row];
        for(size_t i = 0; i < row; ++i) {
            data[i] = new double [col];
            for(size_t j = 0; j < col; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    } catch (std::bad_alloc& ex) {
        std::cerr << "Bad allocation: " << ex.what() << std::endl;
    }
}

Matrix::Matrix(size_t row, size_t col)
    : row(row), col(col) {
    try {
        data = new double* [this->row];
        for(size_t i = 0; i < this->row; ++i) {
            data[i] = new double[this->col];
            for(size_t j = 0; j < this->col; ++j) {
                data[i][j] = 0.0f;
            }
        }
    } catch (std::bad_alloc& ex) {
        std::cerr << "Bad allocation: " << ex.what() << std::endl;
    }
}

Matrix::~Matrix() {
    for(size_t i = 0; i < row; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

// Get element from index
double &Matrix::at(size_t r, size_t c) {
    return data[r][c];
}

const double &Matrix::at(size_t r, size_t c) const {
    return data[r][c];
}

// Arethmetic operations
Matrix& Matrix::operator=(const Matrix& other) {
    try {
        for(size_t i = 0; i < row; ++i) {
            delete[] data[i];
        }
        delete[] data;

        row = other.row;
        col = other.col;
        data = new double* [row];
        for(size_t i = 0; i < row; ++i) {
            data[i] = new double[col];
            for(size_t j = 0; j < col; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    } catch (std::bad_alloc& ex) {
        std::cerr << "Bad allocation: " << ex.what() << std::endl;
    } return *this;
}

Matrix operator+(const Matrix& A, const Matrix& B) {
    Matrix C(A);

    try {
        if (!(A.row == B.row && A.col == B.col)) {
            throw std::invalid_argument("Different dimension!");
        }
        
        for(size_t i = 0; i < C.row; ++i) {
            for(size_t j = 0; j < C.col; ++j) {
                C.data[i][j] += B.at(i, j);
            }
        }
    } catch(std::invalid_argument const& ex) {
        std::cerr << "Invalid argument: " << ex.what() << std::endl;
    } return C;
}

Matrix operator-(const Matrix& A, const Matrix& B) {
    return A + (-1.0f) * B;
}

Matrix  operator*(const Matrix& A, const Matrix& B) {
    Matrix C(A.row, B.col);

    try {
        if (A.col != B.row) {
            throw std::logic_error("these matrix can`t be multiplied");
        }

        for(size_t i = 0; i < C.row; ++i) {
            for(size_t j = 0; j < C.col; ++j) {
                C.data[i][j] = 0;
                for(size_t k = 0; k < A.col; ++k) {
                    C.data[i][j] += A.at(i, k) * B.at(k, i);
                }
            }
        }
    } catch(std::invalid_argument const& ex) {
        std::cerr << "Invalid argument: " << ex.what() << std::endl;
    } return C;
}

Matrix  operator*(const double k, const Matrix& A) {
    Matrix B(A);

    for(size_t i = 0; i < B.row; ++i) {
        for(size_t j = 0; j < B.col; ++j) {
            B.data[i][j] *= k;
        }
    } return B;
}

Matrix  operator*(const Matrix& A, const double k) {
    return k * A;
}

// Input-Output
std::ostream& operator<<(std::ostream &out, Matrix A) {
    for(size_t i = 0; i < A.row; ++i) {
        for(size_t j = 0; j < A.col; ++j)
            out << A.data[i][j] << " ";
        out << std::endl;
    } return out;
}

std::istream& operator>>(std::istream& in, Matrix& A) {
    double temp;

    for(size_t i = 0; i < A.row; ++i) {
        for(size_t j = 0; j < A.col; ++j) {
            in >> temp;
            A.data[i][j] = temp;
        }
    } return in;
}


void Matrix::Transpose() {
    try {
        if (row != col)  throw std::invalid_argument("We can do it, but we can`t do it");
        
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j != i; ++j) {
                if (i != j) {
                    double temp = data[i][j];
                    data[i][j] = data[j][i];
                    data[j][i] = temp;
                }
            }
        }
    } catch(std::invalid_argument const& ex) {
        std::cerr << "Invalid argument: " << ex.what() << std::endl;
    }
}

// Extra
Matrix Matrix::Upper() const {
    Matrix R(*this); // Resault
    double temper;

    for(size_t i = 0; i < R.row; ++i) {
        for(size_t j = 0; j < R.col; ++j) {
            temper = 0.0f;
            
            size_t k = i;
            for(; k < R.row; ++k) {
                if(std::abs(R.data[k][j]) > EPS) {
                    temper = std::abs(R.data[k][j]);
                    // штука, которой будет обнулять столбцы
                    break;
                }
            }

            if(temper < EPS) { // dif == 0 -> We found nifiga
                for(size_t l = i + 1; l < R.row; ++l)
                    R.data[l][j] = 0.0f; // Обнуляем все елементы в коколонке
                    continue; // Пропускаем все шаги дальше
            }

            if(k != i) {
                for(size_t l = i; l < R.col; ++l) { std::swap(R.at(i, j), R.at(k, j)); }
            } 
            for(size_t l = i + 1; l < R.row; ++l) {
                double dif = -1 * R.data[k][j] / temper;
                R.data[l][j] = 0.0f;
                for(size_t p = j + 1; j < col; ++j) {
                    R.data[k][p] += dif * R.data[i][p];
                }
            }
        }
    } return R;
}

bool Matrix::is_triangular() const {
    if(row != col) {
        return false;
    }

    size_t i = 0, j = 0;
    while(i < row) { // j < col;
        for(size_t k = i + 1; k < row; ++k) {
            if (data[k][j] > EPS) return false;
        } ++i; ++j;
    } return true;
}
