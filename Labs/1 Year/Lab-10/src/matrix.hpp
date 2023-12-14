#ifndef _MATRIX_ 
#define _MATRIX_ 27022023l

#include <iostream>
#include <cstring>


// Вспомогательные функции

template<typename T>
void swap(T &a, T&b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void swap(T* arr1, T* arr2, size_t size)
{
    T* tmp = new T[size];
    memcpy(tmp,  arr1, size*sizeof(T));
    memcpy(arr1, arr2, size*sizeof(T));
    memcpy(arr2, tmp,  size*sizeof(T));
    delete[] tmp;
}


template<typename T>
class Matrix
{
    size_t rows;
    size_t cols;
    T**    data;

    // -- Private methods

    static size_t findMaxval(const Matrix& matrix, size_t start_col)
    {
        size_t max_row = start_col; // col == row;

        for(size_t i = start_col + 1; i < matrix.rows; ++i ) {
            if(matrix(i, start_col) > matrix(max_row, start_col))
                max_row = i;
        }
        return max_row;
    }

public:
    
    // -- Member function --

    Matrix( const Matrix &other )
    {
        rows = other.rows;
        cols = other.cols;
        data = new T*[rows];

        for(size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for(size_t j = 0; j < cols; ++j)
                data[i][j] = other.data[i][j];
        }
    }

    Matrix( size_t rows_, size_t cols_, T val = T() )
    {
        rows = rows_;
        cols = cols_;
        data = new T*[rows];

        for(size_t i = 0; i < rows; ++i)
        {
            data[i] = new T[cols];
            for(size_t j = 0; j < cols; ++j)
                data[i][j] = val;
        }
    }


    ~Matrix()
    {
        for(size_t i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;
    }

    Matrix& operator=( const Matrix &other )
    {
        if(data != NULL)
        {
            for(size_t i = 0; i < rows; ++i)
                delete[] data[i];
            delete[] data;
        }

        rows = other.rows;
        cols = other.cols;
        data = new T*[rows];

        for(size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            memcpy(data[i], other.data[i], cols);
        }

        return *this;
    }

    // -- Element access 
    
    T& at( size_t r, size_t c )
    { return data[r][c]; }

    const T& at( size_t r, size_t c ) const
    { return data[r][c]; }

    T& operator()( size_t r, size_t c )
    { return data[r][c]; }

    const T& operator()( size_t r, size_t c ) const
    { return data[r][c]; }


    // -- Arethmetic operators

    friend Matrix<T> operator+( const Matrix<T>& lhs, const Matrix<T>& rhs )
    {
        if(lhs.rows != rhs.rows || lhs.cols != rhs.cols)
            throw std::invalid_argument("Sum of matrices with different sizes is forbidden\n");

        Matrix<T> res(lhs);

        for(size_t i = 0; i < res.rows; ++i)
        {
            for(size_t j = 0; j < res.cols; ++j)
                res(i, j) += rhs(i, j);
        }
        return res;
    }

    friend Matrix<T> operator+( const Matrix<T>& matrix, const T& num )
    {
        Matrix<T> res(matrix);

        for(size_t i = 0; i < res.rows; ++i)
        {
            for(size_t j = 0; j < res.cols; ++j)
                res(i, j) += num;
        }
        return res;
    }

    friend Matrix<T> operator+(  const T& num, const Matrix<T>& matrix )
    { return matrix + num; }

    friend Matrix<T> operator-( const Matrix<T>& lhs, const Matrix<T>& rhs )
    {
        if(lhs.rows != rhs.rows || lhs.cols != rhs.cols)
            throw std::invalid_argument("Sub of matrices with different sizes is forbidden\n");

        Matrix<T> res(lhs);

        for(size_t i = 0; i < res.rows; ++i)
        {
            for(size_t j = 0; j < res.cols; ++j)
                res(i, j) -= rhs(i, j);
        }
        return res;
    }

    friend Matrix<T> operator-( const Matrix<T>& matrix, const T& num )
    {
        Matrix<T> res(matrix);

        for(size_t i = 0; i < res.rows; ++i)
        {
            for(size_t j = 0; j < res.cols; ++j)
                res(i, j) -= num;
        }
        return res;
    }

    friend Matrix<T> operator*( const Matrix<T>& lhs, const Matrix<T>& rhs )
    {
        if(lhs.rows != rhs.cols)
            throw std::invalid_argument("Mul of unsuitable matrices is forbidden\n");
        
        Matrix<T> res(lhs.cols, rhs.rows); // При инициализации все ячейки равны T()
        
        for(size_t i = 0; i < res.rows; ++i)
        {
            for(size_t j = 0; j < res.cols; ++j)
            {
                for(size_t k = 0; k < lhs.cols; ++k)
                    res(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
        return res;
    }

    friend Matrix<T> operator*( const Matrix<T>& matrix, const T& num )
    {
        Matrix<T> res(matrix);

        for(size_t i = 0; i < res.rows; ++i)
        {
            for(size_t j = 0; j < res.cols; ++j)
                res(i, j) -= num;
        }
        return res;
    }

    friend Matrix<T> operator*( const T& num, const Matrix<T>& matrix )
    { return matrix * num; }

    // -- Input/Output stream operators

    friend std::ostream& operator<<( std::ostream& out, const Matrix<T>& matrix ) {
        for(size_t i = 0; i < matrix.rows; ++i)
        {
            for(size_t j = 0; j < matrix.cols; ++j)
                out << matrix(i, j) << " \n"[j == matrix.cols - 1];
        }
        return out;
    }


    friend std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {
        for(size_t i = 0; i < matrix.rows; ++i)
        {
            for(size_t j = 0; j < matrix.cols; ++j)
                in >> matrix(i, j);
        }
        return in;
    }

    // -- Matrix transpose

    void Transpose()
    {
        Matrix<T> *tmp = new Matrix(*this);
        swap(rows, cols);

        for(size_t i = 0; i < rows; ++i)
        {   
            for(size_t j = 0; j < cols; ++j)
                this->data[j][i] = tmp->data[i][j];
        }
        delete tmp;
    }

    // -- Factorization(LUP) - хотя больше похоже на...


    void LU(Matrix<T> *u, Matrix<T> *l, Matrix<T> *m) const
    {
        if( this->cols != this->rows
         || (l->rows != this->rows && l->cols != this->cols)
         || (u->rows != this->rows && u->cols != this->cols)
         || (m->rows != this->rows && m->cols != this->cols))
            throw std::logic_error("Count rows of right and count cols of left are not the same\n");
        
        Matrix<T> res(*this);
        size_t max_row;

        // Инициализация матриц
        for(size_t i = 0; i < m->rows; ++i)
        {
            for(size_t j = 0; j < m->cols; j++)
            {
                (*m)(i, j) = (j == i);
                (*l)(i, j) = (j == i);
                (*u)(i, j) = 0;
            }
        }

        // Сначала создаётся матрица P, а потом L и U

        // Ищется строка с максимальным элементом от i до n по столбцу
        for (size_t i = 0; i < this->rows; i++)
        {
            max_row = findMaxval(res, i);
            if(max_row != i)
            {
                swap(res.data[max_row],  res.data[i] ); // Переставляются строки i и строка с максимальным элементом
                swap(m->data[max_row], m->data[i] ); // Та же операция для перестановочной матрицы
            }
        }

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                if(i <= j)
                {
                    T sum = 0;
                    for(size_t k = 0; k < i; ++k)
                        sum += l->at(i,k) * u->at(k,j);
                    u->at(i,j) = res(i, j) - sum;
                }
                else if (i > j)
                {
                    T sum = 0;
                    for(size_t k = 0; k < j; ++k)
                        sum += l->at(i,k) * u->at(k,j);
                    l->at(i,j) = (res(i, j) - sum) / u->at(j,j);

                }
            }
        }
    }

    Matrix<T>& M() const
    {
        Matrix<T> *M = new Matrix<T>(*this);
        Matrix<T> L(*this);
        Matrix<T> U(*this);
        this->LU(&U,&L,M);
        return *M;
    }

    Matrix<T>& L() const
    {
        Matrix<T> M (*this);
        Matrix<T> *L = new Matrix<T>(*this);
        Matrix<T> U(*this);
        this->LU(&U,L,&M);
        return *L;
    }
    Matrix<T>& U() const
    {
        Matrix<T> M(*this);
        Matrix<T> L(*this);
        Matrix<T> *U = new Matrix<T>(*this);
        this->LU(U,&L,&M);
        return *U;
    }

    // -- Linear Equasion Solver

    Matrix<T> Solve(const Matrix<T>& b) const
    {
        // Делаем PLU разложение
        Matrix<T> P(*this);
        Matrix<T> L(*this);
        Matrix<T> U(*this);
        this->LU(&U, &L, &P);

        Matrix<T> b_permuted(P * b);

        Matrix<T> y(b_permuted.rows, 1);
        for(size_t i = 0; i < y.rows; ++i)
        {
            T tmp = b_permuted(i, 0);
            for(size_t j = 0; j < (i - 1); ++j)
                tmp -= L(i,j) * y(j,0);
            y(i,0) = tmp / L(i,i);
        }
        
        Matrix<T> *x = new Matrix<T>(y.rows, 1);
        for(size_t i = x->rows - 1; i >= 0; --i)
        {
            T tmp = b_permuted(i, 0);
            for(size_t j = i + 1; j < x->rows; ++j)
                tmp -= U(i,j) * x->at(j,0);
            x->at(i,0) = tmp / U(i,i);
        }
        return *x;
    }
};

#endif
