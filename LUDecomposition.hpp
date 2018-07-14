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
 * @brief Class to work with decomposition of matrix
 * 
 * @tparam Type of square matrice's elements
 */
template<class T>
class LUDecomposition {
public:
    /**
     * @brief Construct a new empty LUDecomposition object
     * 
     */
    LUDecomposition();

    /**
     * @brief Construct a new LUDecomposition object with decomposition of given matrix
     * 
     * @param Matrix to get decomposition
     */
	LUDecomposition(const Matrix<T>& matrix);

    /**
     * @brief Destroy the LUDecomposition object
     * 
     */
    ~LUDecomposition();

    /**
     * @brief Decomposes given matrix
     * 
     * @param Matrix to get decomposition
     * @return true if decomposition was successfully gotten
     * @return false if decomposition wasn't gotten
     */
    bool decompose(const Matrix<T>& matrix);

    /**
     * @brief Get shared_ptr to L-matrix of decomposition
     * 
     * @return std::shared_ptr<Matrix<T>>
     */
    std::shared_ptr<Matrix<T>> getL() const;

    /**
     * @brief Get shared_ptr to U-matrix of decomposition
     * 
     * @return std::shared_ptr<Matrix<T>> 
     */
    std::shared_ptr<Matrix<T>> getU() const;

    /**
     * @brief Get the size of L and U matrices (Size x Size)
     * 
     * @return std::size_t 
     */
    std::size_t getSize() const;

    /**
     * @brief Check is decomposition empty or not (empty when given matrix isn't square)
     * 
     * @return true if decomposition is empty
     * @return false if decomposition isn't empty
     */
    bool isEmpty() const;

private:
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
     * @brief Size of the matrix (as matrix is square, this size is rows' size and columns' size)
     * 
     */
    std::size_t size;

    /**
     * @brief Sets to true, if decomposition wasn't gotten
     * 
     */
	bool empty;
};

template<class T>
LUDecomposition<T>::LUDecomposition() {
    empty = true;
    size = 0;
}

template<class T>
LUDecomposition<T>::LUDecomposition(const Matrix<T>& matrix) {
    decompose(matrix);
}

template<class T>
LUDecomposition<T>::~LUDecomposition() {

}

template<class T>
bool LUDecomposition<T>::decompose(const Matrix<T>& matrix) {
    if (!matrix.isSquare()) {
        size = 0;
        empty = true;
        return !empty;
    }

    size = matrix.getRows();
    empty = false;

    RawMatrix<T> lower = Matrix<T>::allocateRawMatrix(size, size);
    RawMatrix<T> upper = Matrix<T>::allocateRawMatrix(size, size);

    for (std::size_t i = 0; i < size; ++i) {

        // Upper Triangular
        for (std::size_t k = i; k < size; ++k) {

            // Summation of L(i, j) * U(j, k)
            int sum = 0;
            for (std::size_t j = 0; j < i; ++j)
                sum += (lower[i][j] * upper[j][k]);

            // Evaluating U(i, k)
            upper[i][k] = matrix.get(i, k) - sum;
        }

        // Lower Triangular
        for (std::size_t k = i; k < size; ++k) {
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

    return !empty;
}

template<class T>
std::shared_ptr<Matrix<T>> LUDecomposition<T>::getL() const {
    return L;
}

template<class T>
std::shared_ptr<Matrix<T>> LUDecomposition<T>::getU() const {
    return U;
}

template<class T>
std::size_t LUDecomposition<T>::getSize() const {
    return size;
}

template<class T>
bool LUDecomposition<T>::isEmpty() const {
    return empty;
}

}