#pragma once

#include "Matrix.hpp"
#include "LUDecomposition.hpp"

namespace Matrix {

template<typename T>
class Determinant {
public:

    Determinant();
    Determinant(const Matrix<T>& matrix);

    ~Determinant();

    bool computeDeterminant(const Matrix<T>& matrix);

    std::size_t getSize();
    bool isEmpty();
    T getDeterminant();

private:
    std::size_t size;
    bool empty;
    T determinant;

};

}