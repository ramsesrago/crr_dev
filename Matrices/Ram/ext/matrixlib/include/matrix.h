#ifndef MATRIX_H
#define MATRIX_H

#include <map>
#include <string.h>

#include "matrix_interface.h"

namespace CustomMatrix {

class Matrix : public IMatrix {

public:
    Matrix(int rows, int cols, bool is_random = true);
    Matrix(int rows, int cols, float* matrix);

    // Copy constructor
    Matrix(const Matrix& m);

    // Destructor
    ~Matrix();

    typedef std::map<eMatrixType, std::string> MatrixType;

    IMatrixPtr add(const IMatrixPtr& m) override;
    IMatrixPtr substract(const IMatrixPtr& m) override;
    IMatrixPtr multiply(const IMatrixPtr& m) override;
    IMatrixPtr divide(const IMatrixPtr& m) override;
    IMatrixPtr rotate(eRotate rotation) override;

    float operator()(int row, int col) override;
    float* get_1d_raw_matrix(eMatrixType type) const override;
    float** get_2d_raw_matrix(eMatrixType type) const override;
    float get_determinant() const override;
    int get_cols() const override;
    int get_rows() const override;
    void print(eMatrixType type) const override;

private:
    void init_matrix();
    void calc_adjugate();
    void calc_cofactor();
    void calc_inverse();
    float calc_determinant(float* m, int cols);
    float* allocate_empty_matrix();
    float* allocate_random_matrix(int maxNumber);
    float* transpose(float* matrix);
    float* get_submatrix(float* matrix, int pos, int cols);
    float* get_product(float* b, int cols);

    float* _matrix;
    float* _matrix_transpose;
    float* _matrix_adj;
    float* _matrix_inv;
    float* _matrix_cofactor;
    float _det;
    int _rows;
    int _cols;

    MatrixType matrixType;
};

}
#endif // MATRIX_H
