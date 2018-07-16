#pragma once

#include "Matrix.hpp"
#include "LUDecomposition.hpp"

#include <numeric>

namespace MatrixCpp {

template<typename T>
class Determinant {
public:
    Determinant();
    Determinant(const Matrix<T>& matrix);

    ~Determinant();

    bool computeDeterminant(const Matrix<T>& matrix);

    bool isEmpty();
    T getDeterminant();

private:
    bool empty;
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