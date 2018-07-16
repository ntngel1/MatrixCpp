/**
 * @brief Determinant header
 * 
 * @file Determinant.hpp
 * @author Kirill Shepelev
 * @date 2018-07-16
 */

#pragma once

#include "Matrix.hpp"
#include "LUDecomposition.hpp"

#include <numeric>

namespace MatrixCpp {

template<typename T>
class Determinant {
public:
    /**
     * @brief Construct a new empty Determinant object
     * 
     */
    Determinant();

    /**
     * @brief Construct a new Determinant object with computing a determinant of given matrix
     * 
     * @param matrix Matrix
     */
    Determinant(const Matrix<T>& matrix);

    /**
     * @brief Destroy the Determinant object
     * 
     */
    ~Determinant();

    /**
     * @brief Compute determinant for given matrix
     * 
     * @param matrix Matrix
     * @return true if determinant was successfully computed
     * @return false if determinant wasn't computed
     */
    bool computeDeterminant(const Matrix<T>& matrix);

    /**
     * @brief Checks: is determinant for matrix was computed
     * 
     * @return true if determinant wasn't computed
     * @return false if determinant was computed
     */
    bool isEmpty();

    /**
     * @brief Get the determinant
     * 
     * @return T determinant
     */
    T getDeterminant();

private:
    /**
     * @brief Empty flag
     * 
     */
    bool empty;

    /**
     * @brief Determinant
     * 
     */
    T determinant;
};

template<typename T>
Determinant<T>::Determinant() {
    empty = true;
    determinant = 0;
}

template<typename T>
Determinant<T>::Determinant(const Matrix<T>& matrix) {
    computeDeterminant(matrix);
}

template<typename T>
Determinant<T>::~Determinant() {

}

template<typename T>
bool Determinant<T>::computeDeterminant(const Matrix<T>& matrix) {
    LUDecomposition<T> decomposition(matrix);

    if (decomposition.isEmpty()) {
        empty = true;
        determinant = 0;
        return false;
    }

    std::vector<T> LDiag = decomposition.getL()->getDiagonalElements();
    std::vector<T> UDiag = decomposition.getU()->getDiagonalElements();
    determinant = std::accumulate(LDiag.begin(), LDiag.end(), 1, std::multiplies<T>());
    determinant = std::accumulate(UDiag.begin(), UDiag.end(), determinant, std::multiplies<T>());

    empty = false;

    return !empty;
}

template<typename T>
bool Determinant<T>::isEmpty() {
    return empty;
}

template<typename T>
T Determinant<T>::getDeterminant() {
    return determinant;
}

}