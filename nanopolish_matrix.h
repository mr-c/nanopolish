//---------------------------------------------------------
// Copyright 2015 Ontario Institute for Cancer Research
// Written by Jared Simpson (jared.simpson@oicr.on.ca)
//---------------------------------------------------------
//
// nanopolish_matrix -- matrix manipulation functions
//
#ifndef NANOPOLISH_MATRIX_H
#define NANOPOLISH_MATRIX_H

//
// Template Matrix for POD types
//
template<typename T>
struct Matrix
{
    T* cells;
    uint32_t n_rows;
    uint32_t n_cols;
};

typedef Matrix<double> DoubleMatrix;
typedef Matrix<uint32_t> UInt32Matrix;

//
template<typename T>
void allocate_matrix(Matrix<T>& matrix, uint32_t n_rows, uint32_t n_cols)
{
    matrix.n_rows = n_rows;
    matrix.n_cols = n_cols;
    
    uint32_t N = matrix.n_rows * matrix.n_cols;
    matrix.cells = (T*)malloc(N * sizeof(T));
    memset(matrix.cells, 0, N * sizeof(T));
}

//
template<typename T>
void free_matrix(Matrix<T>& matrix)
{
    assert(matrix.cells != NULL);
    free(matrix.cells);
    matrix.cells = NULL;
}

//
template<typename T>
inline uint32_t cell(const Matrix<T>& matrix, uint32_t row, uint32_t col)
{
    return row * matrix.n_cols + col;
}

//
template<typename T, typename U>
inline void set(Matrix<T>& matrix, uint32_t row, uint32_t col, U v)
{
    uint32_t c = cell(matrix, row, col);
    matrix.cells[c] = v;
}

// 
template<typename T>
inline T get(const Matrix<T>& matrix, uint32_t row, uint32_t col)
{
    uint32_t c = cell(matrix, row, col);
    return matrix.cells[c];
}

//
void print_matrix(const DoubleMatrix& matrix, bool do_exp = false)
{
    for(uint32_t i = 0; i < matrix.n_rows; ++i) {
        for(uint32_t j = 0; j < matrix.n_cols; ++j) {
            uint32_t c = cell(matrix, i, j);
            double v = matrix.cells[c];
            if(do_exp)
                v = exp(v);
            printf("%.3lf\t", v);
        }
        printf("\n");
    }
}

#endif