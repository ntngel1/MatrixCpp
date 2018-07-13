/**
 * @brief LU Decomposition header
 * 
 * @file LUDecomposition.hpp
 * @author Kirill Shepelev
 * @date 2018-07-13
 */

#pragma once

#include "Matrix.hpp"

namespace MatrixCpp {

/**
 * @brief Struct to work with decomposition of matrix
 * 
 * @tparam Type of square matrice's elements
 */
template<class T>
struct LUDecomposition {
    /**
     * @brief Size of the matrix (as matrix is square, this size is rows' size and columns' size)
     * 
     */
    std::size_t size;

    /**
     * @brief Sets to true, if decomposition wasn't gotten
     * 
     */
	bool isEmpty;
    
    /**
     * @brief Shared-ptr to L-matrix of decomposition
     * 
     */
	std::shared_ptr<Matrix<T>> L;

    /**
     * @brief Shared-ptr to U-matrix of decomposition
     * 
     */
	std::shared_ptr<Matrix<T>> U;

    /**
     * @brief Construct a new empty LUDecomposition object
     * 
     */
    LUDecomposition() {
        isEmpty = true;
        size = 0;
    }

    /**
     * @brief Construct a new LUDecomposition object with decomposition of given matrix
     * 
     * @param Matrix to get decomposition
     */
	LUDecomposition(const Matrix<T>& matrix) {
        decompose(matrix);
	}

    /**
     * @brief Decomposes given matrix
     * 
     * @param Matrix to get decomposition
     * @return true if decomposition was successfully gotten
     * @return false if decomposition wasn't gotten
     */
    bool decompose(const Matrix<T>& matrix) {
        if (!matrix.isSquare()) {
            size = 0;
            isEmpty = true;
            return !isEmpty;
        }

        size = matrix.getRows();
        isEmpty = false;

        RawMatrix<T> lower = Matrix<T>::allocateRawMatrix(size, size);
        RawMatrix<T> upper = Matrix<T>::allocateRawMatrix(size, size);

        for (size_t i = 0; i < size; ++i) {

            // Upper Triangular
            for (size_t k = i; k < size; ++k) {

                // Summation of L(i, j) * U(j, k)
                int sum = 0;
                for (size_t j = 0; j < i; ++j)
                    sum += (lower[i][j] * upper[j][k]);

                // Evaluating U(i, k)
                upper[i][k] = matrix.get(i, k) - sum;
            }

            // Lower Triangular
            for (size_t k = i; k < size; ++k) {
                if (i == k)
                    lower[i][i] = 1; // Diagonal as 1
                else {
                    // Summation of L(k, j) * U(j, i)
                    int sum = 0;
                    for (size_t j = 0; j < i; ++j)
                        sum += (lower[k][j] * upper[j][i]);

                    // Evaluating L(k, i)
                    lower[k][i] = (matrix.get(k, i) - sum) / upper[i][i];
                }
            }
        }

        L = std::make_shared<Matrix<T>>(lower);
        U = std::make_shared<Matrix<T>>(upper);

        return !isEmpty;
    }
};

}