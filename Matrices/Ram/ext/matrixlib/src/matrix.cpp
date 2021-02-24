#include <iostream>
#include <string.h>
#include <math.h>
#include "matrix.h"

namespace CustomMatrix {

Matrix::Matrix(int rows, int cols, bool is_random) {
    _rows = rows;
    _cols = cols;
    if (is_random) {
        _matrix = allocate_random_matrix(10);
        // Calculate internal values  like determinant, transpose, adj
        init_matrix();
    }
    else {
        _matrix = allocate_empty_matrix();
    }
}

Matrix::Matrix(int rows, int cols, float* matrix) {
    _rows = rows;
    _cols = cols;
    _matrix = allocate_empty_matrix();
    memcpy(_matrix, matrix, rows*cols*sizeof(matrix[0]));
    // Calculate internal values  like determinant, transpose, adj
    init_matrix();
}

Matrix::Matrix(const Matrix& m) {
    // By default the compiler creates a copy constructor which performs
    // a shallow copy, meaning it will reference the same internal variables
    std::cout << "Calling copy constructor" << std::endl;
    _cols = m._cols;
    _rows = m._rows;
    _matrix = allocate_empty_matrix();
    memcpy(_matrix, m._matrix, _rows*_cols*sizeof(m._matrix[0]));
    std::cout << "_matrix addr is: " << _matrix << std::endl;
    std::cout << "m._matrix addr is: " << m._matrix << std::endl;
    init_matrix();
}

Matrix::~Matrix() {
    std::cout << "Calling ~IMatrix()" << std::endl;
    delete[] _matrix;
    delete[] _matrix_transpose;
    delete[] _matrix_adj;
    delete[] _matrix_inv;
    delete[] _matrix_cofactor;
}

void Matrix::init_matrix() {
    std::cout << "INIT matrix " << __LINE__ << std::endl;
    matrixType[REGULAR] = "REGULAR MATRIX";
    matrixType[TRANSPOSE] = "TRANSPOSE MATRIX";
    matrixType[COFACTOR] = "COFACTOR MATRIX";
    matrixType[ADJ] = "ADJUGATE MATRIX";
    matrixType[INVERSE] = "INVERSE MATRIX";

    _matrix_transpose = transpose(_matrix);

    // We can only get determinants for square matrices
    if (_rows == _cols) {
      _det = calc_determinant(_matrix, _cols);
      std::cout << "Det is : " << _det << std::endl;
      calc_cofactor();
      calc_adjugate();
      calc_inverse();
    }
    else {
      std::cout << "Cannot get determinant, adjugate, cofactor matrix \
                    and inverse for non-square matrices " << __LINE__ << std::endl;
    }
}

float* Matrix::allocate_empty_matrix() {
    float* m = new float[_rows*_cols];
    memset(m, 0, sizeof(m[0]) * _rows * _cols);
    return m;
}

float* Matrix::allocate_random_matrix(int maxNumber) {
    float* m = allocate_empty_matrix();

    for (int i = 0; i < _rows*_cols; ++i) {
        m[i] = rand() % maxNumber;
    }

    return m;
}

float* Matrix::transpose(float* matrix) {
    float* output = allocate_empty_matrix();
    int tIndex = 0;

    for (int i = 0, j = 0; i < _rows*_cols; ++i) {
        if (i > 0 && (i%_cols == 0)) {
            ++j;
        }
        tIndex = _cols * (i % _cols) + j;
        output[i] = matrix[tIndex];
    }
    return output;
}

float Matrix::calc_determinant(float* m, int cols) {
    int res = 0;

    if (cols == 2) {
        return (m[0] * m[3] - m[1] * m[2]);
    }
    else {
        float* submatrix = NULL;
        for (int i = 0; i < cols; ++i) {
            submatrix = get_submatrix(m, cols, i);
            res += m[i] * pow(-1, i) * calc_determinant(submatrix, cols-1);
            delete[] submatrix;
        }
    }

    return res;
}

float* Matrix::get_submatrix(float* matrix, int cols, int pos) {
    // ToDo: Evaluate 2x2 scenario
    const int submatrix_size = (cols-1)*(cols-1);
    float* submatrix = new float[submatrix_size];
    int rowNumber = pos/cols;   // Will skip all numbers associated with this row
    int currRow = 0;

    for (int j = 0, i = 0; j < cols * cols; ++j) {
        // Calculate current row
        currRow = j/cols;
        // This if condition matches the number of row, skip all columns
        // associated with that row
        if (currRow == rowNumber) {
            j = j + cols - 1;
            continue;
        }
        // Match the number of column, skip
        if ((abs(j-pos))%cols == 0) continue;
        submatrix[i++] = matrix[j];
        //std::cout << "submatrix val: " << matrix[j] << std::endl;
    }
    return submatrix;
}

float Matrix::get_determinant() const {
    return _det;
}

void Matrix::calc_cofactor() {
    float* submatrix = NULL;
    _matrix_cofactor = allocate_empty_matrix();
    // Each cofactor is equal of the corresponding submatrix determinant
    for (int i = 0; i < _rows*_cols; ++i) {
        submatrix = get_submatrix(_matrix, _cols, i);
        _matrix_cofactor[i] = pow(-1, i) * calc_determinant(submatrix, _cols-1);
        delete[] submatrix;
    }
}

void Matrix::calc_adjugate() {
    _matrix_adj = transpose(_matrix_cofactor);
}

void Matrix::calc_inverse() {
    if (_det != 0) {
        _matrix_inv = allocate_empty_matrix();
        for (int i = 0; i < _cols*_rows; ++i) {
            _matrix_inv[i] = _matrix_adj[i]/_det;
        }
    }
}

float* Matrix::get_raw_matrix(eMatrixType type) const {
    float* pMatrix = NULL;
    std::string str;
    switch (type) {
        case REGULAR: 
             return _matrix;
        case TRANSPOSE: 
             return _matrix_transpose;
        case COFACTOR: 
             return _matrix_cofactor;
        case ADJ:
             return _matrix_adj;
        case INVERSE: 
             return _matrix_inv;
        default: {
            std::cout << "type " << type << " is not valid";
            return NULL;
        }
    }

    return pMatrix;
}

int Matrix::get_cols() const {
    return _cols;
}

int Matrix::get_rows() const {
    return _rows;
}

IMatrixPtr Matrix::add(const IMatrixPtr& m) {

    if (m->get_cols() != _cols || m->get_rows() != _rows) {
        std::cout << "Cannot sum these matrices, number of cols or rows don't match" << std::endl;
        return NULL;
    }
    float* matrix = new float[_rows*m->get_cols()];

    for (int i = 0; i < _rows*_cols; ++i) {
        // C = A + B
        matrix[i] = _matrix[i] + m->get_raw_matrix(REGULAR)[i];
    }

    IMatrixPtr c = std::make_shared<Matrix>(_rows, _cols, matrix);

    return c;
}

IMatrixPtr Matrix::substract(const IMatrixPtr& m) {
    if (m->get_cols() != _cols || m->get_rows() != _rows) {
        std::cout << "Cannot substract these matrices, number of cols or rows don't match" << std::endl;
        return NULL;
    }

    float* matrix = new float[_rows*m->get_cols()];

    for (int i = 0; i < _rows*_cols; ++i) {
        // C = A - B
        matrix[i] = _matrix[i] - m->get_raw_matrix(REGULAR)[i];
    }

    IMatrixPtr c = std::make_shared<Matrix>(_rows, _cols, matrix);

    return c;
}

IMatrixPtr Matrix::multiply(const IMatrixPtr& m) {
    if (this->_cols != m->get_rows()) {
        std::cout << "Cannot multiply these matrices" << std::endl;
        return NULL;
    }

    float* matrix = get_product(m->get_raw_matrix(REGULAR), m->get_cols());
    IMatrixPtr c = std::make_shared<Matrix>(_rows, m->get_cols(), matrix);

    return c;
}

float* Matrix::get_product(float* b, int bcols) {
    // if n = j; A[m,n]*B[j,k] = C[m,k]  // Number of rows of the first matrix and number of columns of the second matrix
    float* matrix = new float[_rows*bcols];

    // Cij = sum(Aik + Bkj) = sum(A1k + Bk1); let the row of the first matrix fixed and the cols of the second matrix fixed
    // For loop to change matrix index
    std::cout << "value of B rows: " << bcols << std::endl;
    int aIndex = 0;
    int bIndex = 0;
    for (int i = 0, k = 0, h =0; i < this->_rows * bcols; ++i) {
        // For loop for sum and multiplication, sum and mul for the number of cols of A, multiply the first row of A by the first col of B
        if (i > 0 && i%bcols == 0) {
            ++k;
        }
        if (i > 0 && i%bcols == 0) {
            ++h;
        }
        for (int j = 0; j < this->_cols; ++j) {
            aIndex = j + k*this->_cols;
            bIndex = j*bcols + i%bcols;
            matrix[i] += _matrix[aIndex] * b[bIndex];
//            std::cout << "Product of C element is: " << this->getRegularMatrix()[aIndex] << " * " << m.getRegularMatrix()[bIndex] << std::endl;
//            std::cout << "value of C is: " << c->getRegularMatrix()[i] << std::endl;
        }
    }

    return matrix;
}

IMatrixPtr Matrix::divide(const IMatrixPtr& m) {
    // If B is inverstible C = A/B  ->   C = A*inv(B)
    if (calc_determinant(m->get_raw_matrix(REGULAR), m->get_cols()) == 0) {
        std::cout << "B is not invertible, A/B does not exist" << std::endl;
        return NULL;
    }

    float* matrix = get_product(m->get_raw_matrix(INVERSE), m->get_cols());

    IMatrixPtr c = std::make_shared<Matrix>(m->get_rows(), m->get_cols(), matrix);

    return c;
}

void Matrix::print(Matrix::eMatrixType type) const {
    float* pMatrix = NULL;
    std::string str;
    switch (type) {
        case REGULAR: pMatrix = _matrix;
             str = matrixType.at(REGULAR);
             break;
        case TRANSPOSE: pMatrix = _matrix_transpose;
             str = matrixType.at(TRANSPOSE);
             break;
        case COFACTOR: pMatrix = _matrix_cofactor;
             str = matrixType.at(COFACTOR);
             break;
        case ADJ: pMatrix = _matrix_adj;
             str = matrixType.at(ADJ);
             break;
        default: pMatrix = _matrix_inv;
                 str = matrixType.at(INVERSE);
    }

    if (!pMatrix) {
        std::cout << "Selected type to print is invalid" << std::endl;
        return;
    }

    std::cout << "------------- Printing " << str << " -------------" << "\n\n";
    for (int i = 0; i < _rows*_cols; ++i) {
        if (i > 0 && i%_cols == 0) std::cout << std::endl;
        std::cout << pMatrix[i] << "   ";
    }
    std::cout << "\n\n";
}

IMatrixPtr Matrix::rotate(eRotate rotation) {
    return NULL;
}

float Matrix::operator()(int row, int col) {
    return 0.0f;
}

}
