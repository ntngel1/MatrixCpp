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
#include <tuple>

namespace MatrixCpp {

template<typename T>
using RawMatrix = std::vector<std::vector<T>>;

template <typename T>
class Matrix {
public:
	/**
	 * @brief Construct a new Matrix object
	 * 
	 * @param rows Number of rows of matrix
	 * @param columns Number of columns of matrix
	 * @param defaultValue Default value to initialize elements of matrix
	 */
	Matrix(std::size_t rows = 0, std::size_t columns = 0, T defaultValue = T());
	/**
	 * @brief Construct a new Matrix object from RawMatrix
	 * 
	 * @param rawMatrix RawMatrix
	 */
	Matrix(const RawMatrix<T>& rawMatrix);

	/**
	 * @brief Construct a new Matrix object
	 * 
	 * @param rawMatrixList Initializer list
	 */
	Matrix(const std::initializer_list<std::initializer_list<T>>& rawMatrixList);

	/**
	 * @brief Copy constructor
	 * 
	 * @param matrix Matrix to copy
	 */
	Matrix(const Matrix<T>& matrix);

	/**
	 * @brief Destroy the Matrix object
	 * 
	 */
	~Matrix();
	
	/**
	 * @brief Get the RawMatrix of matrix
	 * 
	 * @return const RawMatrix<T>& RawMatrix of matrix
	 */
	const RawMatrix<T>& getRawMatrix() const;
	
	/**
	 * @brief Get number of rows in matrix
	 * 
	 * @return std::size_t Number of rows
	 */
	std::size_t getRows() const;

	/**
	 * @brief Get number of columns in matrix
	 * 
	 * @return std::size_t Number of columns
	 */
	std::size_t getColumns() const;

	/**
	 * @brief Get the Diagonal Elements of Matrix
	 * 
	 * @return std::vector<T>& Elements
	 */
	std::vector<T>& getDiagonalElements() const;

	/**
	 * @brief Get elements of specific row
	 * 
	 * @param row Specific row
	 * @return std::vector<T>& All elements of row
	 */
	std::vector<T>& getRowElements(std::size_t row) const;

	/**
	 * @brief Get elements of specific column
	 * 
	 * @param column Specific column
	 * @return std::vector<T>& All elements if column
	 */
	std::vector<T>& getColumnElements(std::size_t column) const;

	/**
	 * @brief Set specific element to some value
	 * 
	 * @param row Row of element
	 * @param column Column of element
	 * @param value Value
	 */
	void set(std::size_t row, std::size_t column, T value);

	/**
	 * @brief Get specific element value
	 * 
	 * @param row Row of element
	 * @param column Column of element
	 * @return T Value of element
	 */
	T get(std::size_t row, std::size_t column) const;
	
	/**
	 * @brief Checks: is vector the matrix or not
	 * 
	 * @return true if the matrix is a vector
	 * @return false if the matrix isn't a vector
	 */
	bool isVector() const;

	/**
	 * @brief Checks: is square the matrix or not
	 * 
	 * @return true if the matrix is square
	 * @return false if the matrix isn't square
	 */
	bool isSquare() const;

	/**
	 * @brief Checks: is null the matrix or not
	 * 
	 * @return true if the matrix is null
	 * @return false if the matrix isn't null
	 */
	bool isNull() const;

	/**
	 * @brief Transposes the matrix
	 * 
	 */
	void transpose();

	//T getDeterminant() const;

	/**
	 * @brief Squares the matrix (matrix ^ 2)
	 * 
	 * @return Matrix<T>& Matrix in square
	 */
	Matrix<T>& Square();

	/**
	 * @brief Overloading of operator [] to access some row of matrix
	 * 
	 * @param row Specific row
	 * @return std::vector<T>& All elements in this row
	 */
	std::vector<T>& operator[](std::size_t row);

	/**
	 * @brief Overloading of operator [] to access some row of matrix (read only)
	 * 
	 * @param row Specific row
	 * @return const std::vector<T>& All elements in this row
	 */
	const std::vector<T>& operator[](std::size_t row) const;

	Matrix<T>& operator+=(const Matrix<T>& rhs);
	Matrix<T>& operator-=(const Matrix<T>& rhs);
	Matrix<T>& operator*=(const Matrix<T>& rhs);
	Matrix<T>& operator*=(const T& value);
	Matrix<T>& operator/=(const T& value);

	/**
	 * @brief Overloading for operator +
	 * 
	 * @param lhs Left matrix
	 * @param rhs Right matrix
	 * @return Matrix<T> Result
	 */
	friend Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs) {
		return lhs += rhs;
	}

	/**
	 * @brief Overloading for operator -
	 * 
	 * @param lhs Left matrix
	 * @param rhs Right matrix
	 * @return Matrix<T> Result
	 */
	friend Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs) {
		return lhs -= rhs;
	}

	/**
	 * @brief Overloading for operator * (multiplying matrix by matrix)
	 * 
	 * @param lhs Left matrix
	 * @param rhs Right matrix
	 * @return Matrix<T> Multiplied matrix
	 */
	friend Matrix<T> operator*(Matrix<T> lhs, const Matrix<T>& rhs) {
		return lhs *= rhs;
	}

	/**
	 * @brief Overloading for operator * (multiplying matrix by number)
	 * 
	 * @param lhs Matrix to multiply
	 * @param rhs Number to multiply
	 * @return Matrix<T> Multiplied matrix
	 */
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

	/**
	 * @brief Static method for easy allocating RawMatrix (used just by some algorithms)
	 * 
	 * @param rows Number of rows od matrix
	 * @param columns Number of columns of matrix
	 * @return RawMatrix<T>& new RawMatrix
	 */
	static RawMatrix<T>& allocateRawMatrix(std::size_t rows, std::size_t columns);

private:
	std::size_t mRows;
	std::size_t mColumns;
	RawMatrix<T> mRawMatrix;

private:
	RawMatrix<T>* allocRawMatrix(std::size_t width, std::size_t height, T defaultValue = T()) const;
};

template<typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t columns, T defaultValue) {
	this->mColumns = columns;
	this->mRows = rows;

	this->mRawMatrix = *allocRawMatrix(rows, columns, defaultValue);
}

template<typename T>
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

template<typename T>
Matrix<T>::Matrix(const RawMatrix<T>& rawMatrix) {
	mRows = rawMatrix.size();
	mColumns = rawMatrix[0].size();
	
	mRawMatrix = *allocRawMatrix(mRows, mColumns);
	std::copy(rawMatrix.begin(), rawMatrix.end(), mRawMatrix.begin());
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix) : Matrix(matrix.getRawMatrix()) 
{
	std::cout << "Copying constructor called" << std::endl;
}

template<typename T>
Matrix<T>::~Matrix() 
{}

template<typename T>
RawMatrix<T>& Matrix<T>::allocateRawMatrix(std::size_t rows, std::size_t columns) {
	RawMatrix<T>* matrix = new RawMatrix<T>();
	matrix->resize(rows);
	
	for (auto & row : *matrix) {
		row.resize(columns);
	}

	return *matrix;
}

template<typename T>
const RawMatrix<T>& Matrix<T>::getRawMatrix() const {
	return mRawMatrix;
}

template<typename T>
std::size_t Matrix<T>::getRows() const {
	return mRows;
}

template<typename T>
std::size_t Matrix<T>::getColumns() const {
	return mColumns;
}

template<typename T>
void Matrix<T>::set(std::size_t row, std::size_t column, T value) {
	mRawMatrix[row][column] = value;
}

template<typename T>
T Matrix<T>::get(std::size_t row, std::size_t column) const {
	return mRawMatrix[row][column];
}

template<typename T>
bool Matrix<T>::isVector() const {
	if (mColumns == 1 && mRows > 1)
		return true;
	else if (mRows == 1 && mColumns > 1)
		return true;
	else
		return false;
}

template<typename T>
bool Matrix<T>::isSquare() const {
	if (mColumns == mRows)
		return true;
	else
		return false;
}

template<typename T>
bool Matrix<T>::isNull() const {
	for (auto & r : mRawMatrix) {
		for (auto & el : r) {
			if (el != 0)
				return false;
		}
	}

	return true;
}

template<typename T>
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

template<typename T>
std::vector<T>& Matrix<T>::getDiagonalElements() const {
	if (!isSquare())
		return *(new std::vector<T>(0));
	
	std::size_t elements = getRows();
	std::vector<T>* diagonal = new std::vector<T>();
	diagonal->reserve(elements);

	for (std::size_t i = 0; i < elements; ++i)
		diagonal->push_back(mRawMatrix[i][i]);

	return *diagonal;
}

template<typename T>
std::vector<T>& Matrix<T>::getRowElements(std::size_t row) const {
	if (row > mRows - 1)
		return *(new std::vector<T>());

	std::vector<T>* elements = new std::vector<T>();
	elements->reserve(mColumns);

	for (std::size_t column = 0; column < mColumns; ++column) {
		elements->push_back(mRawMatrix[row][column]);
	}

	return *elements;
}

template<typename T>
std::vector<T>& Matrix<T>::getColumnElements(std::size_t column) const {
	if (column > mColumns - 1)
		return *(new std::vector<T>());

	std::vector<T>* elements = new std::vector<T>();
	elements->reserve(mRows);

	for (std::size_t row = 0; row < mRows; ++row) {
		elements->push_back(mRawMatrix[row][column]);
	}

	return *elements;
}

template<typename T>
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
template<typename T>
std::vector<T>& Matrix<T>::operator[](std::size_t row) {
	return mRawMatrix[row];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](std::size_t row) const {
	return mRawMatrix[row];
}

template<typename T>
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

template<typename T>
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

template<typename T>
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

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T& value) {
	std::size_t rows = mRows, columns = mColumns;

	for (auto & i : mRawMatrix) {
		for (T & el : i) {
			el *= value;
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator/=(const T& value) {
	std::size_t rows = mRows, columns = mColumns;

	for (auto & i : mRawMatrix) {
		for (T & el : i) {
			el /= value;
		}
	}
	
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-() {
	Matrix<T> matrix(*this);

	for (std::size_t r = 0; r < mRows; ++r) {
		for (std::size_t c = 0; c < mColumns; ++c) {
			matrix.set(r, c, -get(r, c));
		}
	}

	return matrix;
}

template<typename T>
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

template<typename T>
bool operator==(Matrix<T> const& lhs, Matrix<T> const& rhs) {
	if (!(lhs.getRows() == rhs.getRows() && lhs.getColumns() == rhs.getColumns()))
		return false;

	std::size_t rows = lhs.getRows(), columns = lhs.getColumns();

	for (std::size_t row = 0; row < rows; ++row) {
		for (std::size_t column = 0; column < columns; ++column) {
			if (lhs.get(row, column) != rhs.get(row, column))
				return false;
		}
	}

	return true;
}

}