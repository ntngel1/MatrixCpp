/**
 * @brief Main header of matrix
 * 
 * @file Matrix.hpp
 * @author Kirill Shepelev
 * @date 2018-07-13
 */

#pragma once

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

namespace MatrixCpp {

template<class T>
using RawMatrix = std::vector<std::vector<T>>;

template <class T>
class Matrix {
public:
	Matrix(std::size_t rows = 0, std::size_t columns = 0, T defaultValue = T());
	Matrix(const RawMatrix<T>& rawMatrix);
	Matrix(const std::initializer_list<std::initializer_list<T>>& rawMatrixList);
	Matrix(const Matrix<T>& matrix);

	~Matrix();
	
	const RawMatrix<T>& getRawMatrix() const;
	
	std::size_t getRows() const;
	std::size_t getColumns() const;

	/**
	 * @brief Get the Diagonal Elements of Matrix
	 * 
	 * @return std::vector<T>* Elements
	 */
	std::vector<T>* getDiagonalElements() const;
	std::vector<T>* getRowElements(std::size_t row) const;
	std::vector<T>* getColumnElements(std::size_t column) const;

	void set(std::size_t row, std::size_t column, T value);
	   T get(std::size_t row, std::size_t column) const;
	
	bool isVector() const;
	bool isSquare() const;
	bool isNull() const;

	void transpose();

	//T getDeterminant() const;

	Matrix<T>& Square();

		  std::vector<T>& operator[](std::size_t row);
	const std::vector<T>& operator[](std::size_t row) const;

	Matrix<T>& operator+=(const Matrix<T>& rhs);
	Matrix<T>& operator-=(const Matrix<T>& rhs);
	Matrix<T>& operator*=(const Matrix<T>& rhs);
	Matrix<T>& operator*=(const T& value); // operand's type??
	Matrix<T>& operator/=(const T& value); // operand's type??

	friend Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs) {
		return lhs += rhs;
	}

	friend Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs) {
		return lhs -= rhs;
	}

	friend Matrix<T> operator*(Matrix<T> lhs, const Matrix<T>& rhs) {
		return lhs *= rhs;
	}

	friend Matrix<T> operator*(Matrix<T> lhs, const T& rhs) {
		return lhs *= rhs;
	}

	/**
	 * @brief Overloading for multiplying of matrix by some value
	 * @details Multiplies a matrix by some number
	 * 
	 * @param lhs Value
	 * @param rhs Matrix
	 * 
	 * @return Matrix<T> Multiplied matrix
	 */
	friend Matrix<T> operator*(T lhs, Matrix<T>& rhs) {
		return rhs *= lhs;
	}

	/**
	 * @brief Multiplies matrix by -1
	 * @details Multiplies each element of matrix by -1
	 * @return Matrix<T> Matrix with multiplied by -1 elements
	 */
	Matrix<T> operator-();


	static RawMatrix<T>& allocateRawMatrix(std::size_t rows, std::size_t columns);

private:
	std::size_t mRows;
	std::size_t mColumns;
	RawMatrix<T> mRawMatrix;

private:
	RawMatrix<T>* allocRawMatrix(std::size_t width, std::size_t height, T defaultValue = T()) const;
};

template<class T>
Matrix<T>::Matrix(std::size_t rows, std::size_t columns, T defaultValue) {
	this->mColumns = columns;
	this->mRows = rows;

	this->mRawMatrix = *allocRawMatrix(rows, columns, defaultValue);
}

template<class T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& rawMatrixList)
		  :Matrix(rawMatrixList.size(), rawMatrixList.begin()->size())
{
	std::size_t rows = rawMatrixList.size(), columns = rawMatrixList.begin()->size();
	for (std::size_t r = 0; r < rows; ++r) {
		for (std::size_t c = 0; c < columns; ++c) {
			mRawMatrix[r][c] = *((rawMatrixList.begin() + r)->begin() + c);
		}
	}
}

template<class T>
Matrix<T>::Matrix(const RawMatrix<T>& rawMatrix) {
	mRows = rawMatrix.size();
	mColumns = rawMatrix[0].size();
	
	mRawMatrix = *allocRawMatrix(mRows, mColumns);
	std::copy(rawMatrix.begin(), rawMatrix.end(), mRawMatrix.begin());
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& matrix) : Matrix(matrix.getRawMatrix()) 
{
	std::cout << "Copying constructor called" << std::endl;
}

template<class T>
Matrix<T>::~Matrix() 
{}

template<class T>
RawMatrix<T>& Matrix<T>::allocateRawMatrix(std::size_t rows, std::size_t columns) {
	RawMatrix<T>* matrix = new RawMatrix<T>();
	matrix->resize(rows);
	
	for (auto & row : *matrix) {
		row.resize(columns);
	}

	return *matrix;
}

template<class T>
const RawMatrix<T>& Matrix<T>::getRawMatrix() const {
	return mRawMatrix;
}

template<class T>
std::size_t Matrix<T>::getRows() const {
	return mRows;
}

template<class T>
std::size_t Matrix<T>::getColumns() const {
	return mColumns;
}

template<class T>
void Matrix<T>::set(std::size_t row, std::size_t column, T value) {
	mRawMatrix[row][column] = value;
}

template<class T>
T Matrix<T>::get(std::size_t row, std::size_t column) const {
	return mRawMatrix[row][column];
}

template<class T>
bool Matrix<T>::isVector() const {
	if (mColumns == 1 && mRows > 1)
		return true;
	else if (mRows == 1 && mColumns > 1)
		return true;
	else
		return false;
}

template<class T>
bool Matrix<T>::isSquare() const {
	if (mColumns == mRows)
		return true;
	else
		return false;
}

template<class T>
bool Matrix<T>::isNull() const {
	for (auto & r : mRawMatrix) {
		for (auto & el : r) {
			if (el != 0)
				return false;
		}
	}

	return true;
}

template<class T>
void Matrix<T>::transpose() {
	std::size_t rows = getColumns(), columns = getRows();
	RawMatrix<T> transposed = *allocRawMatrix(rows, columns);

	for (std::size_t row = 0; row < rows; ++row) {
		for (std::size_t column = 0; column < columns; ++column) {
			transposed[row][column] = mRawMatrix[column][row];
		}
	}

	mRawMatrix = transposed;
	mColumns = columns;
	mRows = rows;
}

template<class T>
std::vector<T>* Matrix<T>::getDiagonalElements() const {
	if (!isSquare())
		return new std::vector<T>(0);
	
	std::size_t elements = getRows();
	std::vector<T>* diagonal = new std::vector<T>();
	diagonal->reserve(elements);

	for (std::size_t i = 0; i < elements; ++i)
		diagonal->push_back(mRawMatrix[i][i]);

	return diagonal;
}

template<class T>
std::vector<T>* Matrix<T>::getRowElements(std::size_t row) const {
	if (row > mRows - 1)
		return new std::vector<T>(0);

	std::vector<T>* elements = new std::vector<T>();
	elements->reserve(mColumns);

	for (std::size_t column = 0; column < mColumns; ++column) {
		elements->push_back(mRawMatrix[row][column]);
	}

	return elements;
}

template<class T>
std::vector<T>* Matrix<T>::getColumnElements(std::size_t column) const {
	if (column > mColumns - 1)
		return new std::vector<T>();

	std::vector<T>* elements = new std::vector<T>();
	elements->reserve(mRows);

	for (std::size_t row = 0; row < mRows; ++row) {
		elements->push_back(mRawMatrix[row][column]);
	}

	return elements;
}

template<class T>
Matrix<T>& Matrix<T>::Square() {
	Matrix<T>* matrix = new Matrix<T>(*this);

	*matrix *= *this;

	return *matrix;
}
/*
template<class T>
T Matrix<T>::getDeterminant() const {
	LUDecomposition<T>* decomposition = getLUDecomposition();

	T determinant = 1;

	if (decomposition->isEmpty)
		return 0;
	
	std::vector<T>* LDiagonal = decomposition->L->getDiagonalElements();
	std::vector<T>* UDiagonal = decomposition->U->getDiagonalElements();

	for (auto & d : *LDiagonal) {
		determinant *= d;
	}

	for (auto & d : *UDiagonal) {
		determinant *= d;
	}

	return determinant;
}
*/
template<class T>
std::vector<T>& Matrix<T>::operator[](std::size_t row) {
	return mRawMatrix[row];
}

template<class T>
const std::vector<T>& Matrix<T>::operator[](std::size_t row) const {
	return mRawMatrix[row];
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
	std::size_t rows = mRows, columns = mColumns;

	if (rows != rhs.getRows()) {
		return *this;
	}
	if (columns != rhs.getColumns()) {
		return *this;
	}

	for (std::size_t row = 0; row < rows; ++row) {
		for (std::size_t column = 0; column < columns; ++column) {
			mRawMatrix[row][column] += rhs.get(row, column);
		}
	}

	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
	std::size_t rows = mRows, columns = mColumns;

	if (rows != rhs.getRows()) {
		return *this;
	}
	if (columns != rhs.getColumns()) {
		return *this;
	}

	for (std::size_t row = 0; row < rows; ++row) {
		for (std::size_t column = 0; column < columns; ++column) {
			mRawMatrix[row][column] -= rhs.get(row, column);
		}
	}

	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
	if (mColumns != rhs.getRows())
		return *this;

	RawMatrix<T> matrix = *allocRawMatrix(mRows, mColumns);

	for (std::size_t row = 0; row < mRows; ++row) {
		for (std::size_t column = 0; column < mColumns; ++column) {
			double result = 0; // Maybe need to change type?
			for (std::size_t r = 0; r < mColumns; ++r) {
				result += get(row, r) * rhs.get(r, column);
			}
			matrix[row][column] = result;
		}
	}

	mRawMatrix = matrix;

	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const T& value) {
	std::size_t rows = mRows, columns = mColumns;

	for (auto & i : mRawMatrix) {
		for (T & el : i) {
			el *= value;
		}
	}

	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator/=(const T& value) {
	std::size_t rows = mRows, columns = mColumns;

	for (auto & i : mRawMatrix) {
		for (T & el : i) {
			el /= value;
		}
	}
	
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator-() {
	Matrix<T> matrix(*this);

	for (std::size_t r = 0; r < mRows; ++r) {
		for (std::size_t c = 0; c < mColumns; ++c) {
			matrix.set(r, c, -get(r, c));
		}
	}

	return matrix;
}

template<class T>
RawMatrix<T>* Matrix<T>::allocRawMatrix(std::size_t rows, std::size_t columns, T defaultValue) const {
	RawMatrix<T>* rawMatrix = new RawMatrix<T>(rows);

	for (auto & r : *rawMatrix) {
		r = std::vector<T>(columns);
		for (auto & el : r) {
			el = defaultValue;
		}
	}

	return rawMatrix;
}

}