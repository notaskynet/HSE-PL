#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#include "Matrix.h"


Matrix::Matrix()
    :rows(0), cols(0), data(NULL) {}


Matrix::Matrix(const Matrix& source)
    :rows(source.rows), cols(source.cols)
    {
        size_t pos = 0;

        try {
            data = new double[rows * cols];
        } catch (...) {
            std::cerr << "Error allocating memory" << std::endl;
        }

        for(size_t i = 0; i < rows; ++i)
        {
            for(size_t j = 0; j < cols; ++j)
                data[pos] = source.data[pos];
        }
    }


Matrix::Matrix(size_t source_rows, size_t source_cols)
    :rows(source_rows), cols(source_cols)
    {
        size_t pos = 0;

        try {
            data = new double[rows * cols];
        } catch (...) {
            std::cerr << "Error allocating memory" << std::endl;
        }

        for(size_t i = 0; i < rows; ++i)
            for(size_t j = 0; j < cols; ++j) {
                data[pos] = 0.0f;
                ++pos;
            }
    }

Matrix:: ~Matrix() {
    delete[] data;
    data = NULL;
}


size_t calcWidth(const double *values, const size_t size) {
    
    /* В этой функции путем считывания в поток ввода строк чисел типа double
    будет считаться длина максимального символа для красивого вывода на экран символов*/

    size_t max_width = 0;
    size_t temp;

    std::ostringstream s;
    for(size_t i = 0; i < size; ++i) {
        s << values[i];
        temp = s.str().length();
        max_width = std::max(max_width, temp);
    }
    return max_width;
}


void Matrix::print() const  {
    size_t width = calcWidth(data, rows * cols); // Считаем самый длинный элемент
    size_t pos = 0;

    std::setw( width );
    for(size_t i = 0; i < rows; ++i) {
        for(size_t j = 0; j < cols; ++j)
            std::cout << data[ pos++ ] << " ";
        std::cout << std::endl;
    }
}

void Matrix::print(const Matrix& matrix) {
    size_t width = calcWidth(matrix.data, matrix.rows * matrix.cols); // Считаем самый длинный элемент
    size_t pos = 0;

    std::setw( width );
    for(size_t i = 0; i < matrix.rows; ++i) {
        for(size_t j = 0; j < matrix.cols; ++j) {
            std::cout << matrix.data[ pos++ ] << " ";
        }
        std::cout << std::endl;
    }
}

double& Matrix::at(size_t rows, size_t cols) {
    if(rows > this->rows || cols > this->cols) {
        std::cerr << "Wrong row or col" << std::endl;
    }
    return data[rows * ( this->cols ) + cols];
}


const double& Matrix::at(size_t rows, size_t cols) const {
    if(rows > this->rows || cols > this->cols) {
        std::cerr << "Wrong row or col" << std::endl;
    }
    return data[rows * ( this->cols ) + cols];
}


Matrix Matrix::add(const Matrix &matrix1, const Matrix &matrix2) {
    
    if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
        throw std::logic_error("Diffent dimension!");
    }

    Matrix result(matrix1.rows, matrix1.cols);
    size_t pos = 0;

    for(size_t i = 0; i < result.rows; ++i) {
        for(size_t j = 0; j < result.cols; ++j) {
            result.data[pos] = matrix1.data[pos] + matrix2.data[pos];
            ++pos;
        }
    }

    return result;
}


Matrix Matrix::mul(const Matrix& matrix1, const Matrix& matrix2) {
    
    if (matrix1.cols != matrix2.rows) {
        throw std::logic_error("The number of columns of the first matrix does not \n \
        match the number of rows of the second matrix!"); //Так можно делать иключения
    }

    Matrix result(matrix1.rows, matrix2.cols);
    size_t common = matrix1.cols; // = matrix2.rows;
    size_t pos1 = 0, pos2 = 0, pos = 0;

    for(size_t i = 0; i < result.rows; ++i) {
        for(size_t j = 0; j < result.cols; ++j) {

            result.data[ pos ] = 0;
            pos1 = i * matrix1.rows;
            pos2 = j;

            for(size_t k = 0; k < common; ++k) {
                result.data[ pos++ ] += matrix1.data[ pos1++ ] * matrix2.data[ pos2 ];
                pos2 += matrix2.cols;
            }
        }
    }
    return result;
}


Matrix Matrix::mul(double a, const Matrix& matrix) {
    Matrix result(matrix.rows, matrix.cols);
    size_t pos = 0;

    for(size_t i = 0; i < matrix.rows; ++i) {
        for(size_t j = 0; j < matrix.cols; ++j) {
            result.data[pos] = a * matrix.data[pos];
            ++pos;
        }
    }
    return result;
}


void Matrix::mul(double a) {
    size_t pos = 0;

    for(size_t i = 0; i < rows; ++i) {
        for(size_t j = 0; j < cols; ++j) {
            data[pos++] *= a;
        }
    }
}


void Matrix::Transpose() {

    if (rows == cols) {
        throw std::logic_error("Transpose is defined for square matrices only!");
    }

    for(size_t i = 0; i < rows; ++i)
        for(size_t j = 0; j < cols; ++j) {
            if(i != j) {
                std::swap(data[i * rows + j], data[j * rows + i]);
            }
        }
}