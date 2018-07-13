/**
 * @brief Main header of matrix
 * 
 * @file Matrix.hpp
 * @author Kirill Shepelev
 * @date 2018-07-13
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

template<class T>
struct LUDecomposition;

template<class T>
using RawMatrix = std::vector<std::vector<T>>;

template <class T>
class Matrix
{
public:
	Matrix(size_t rows = 0, size_t columns = 0, T defaultValue = T());
	Matrix(const RawMatrix<T>& rawMatrix);
	Matrix(const std::initializer_list<std::initializer_list<T>>& rawMatrixList);
	Matrix(const Matrix<T>& matrix);

	~Matrix();
	
	const RawMatrix<T>& getRawMatrix() const;
	
	size_t getRows() const;
	size_t getColumns() const;

	void set(size_t row, size_t column, T value);
	   T get(size_t row, size_t column) const;
	
	bool isVector() const;
	bool isSquare() const;
	bool isNull() const;

	void transpose();

	/**
	 * @brief Get the Diagonal Elements of Matrix
	 * 
	 * @return std::vector<T>* Elements
	 */
	std::vector<T>* getDiagonalElements() const;
	std::vector<T>* getRowElements(size_t row) const;
	std::vector<T>* getColumnElements(size_t column) const;

	LUDecomposition<T>* getLUDecomposition() const;
	T getDeterminant() const;

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



private:
	size_t mRows;
	size_t mColumns;
	RawMatrix<T> mRawMatrix;

private:
	RawMatrix<T>* allocRawMatrix(size_t width, size_t height, T defaultValue = T()) const;
};

template<class T>
Matrix<T>::Matrix(size_t rows, size_t columns, T defaultValue) {
	this->mColumns = columns;
	this->mRows = rows;

	this->mRawMatrix = *allocRawMatrix(rows, columns, defaultValue);
}

template<class T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& rawMatrixList)
		  :Matrix(rawMatrixList.size(), rawMatrixList.begin()->size())
{
	size_t rows = rawMatrixList.size(), columns = rawMatrixList.begin()->size();
	for (size_t r = 0; r < rows; ++r) {
		for (size_t c = 0; c < columns; ++c) {
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
const RawMatrix<T>& Matrix<T>::getRawMatrix() const {
	return mRawMatrix;
}

template<class T>
size_t Matrix<T>::getRows() const {
	return mRows;
}

template<class T>
size_t Matrix<T>::getColumns() const {
	return mColumns;
}

template<class T>
void Matrix<T>::set(size_t row, size_t column, T value) {
	mRawMatrix[row][column] = value;
}

template<class T>
T Matrix<T>::get(size_t row, size_t column) const {
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
	size_t rows = getColumns(), columns = getRows();
	RawMatrix<T> transposed = *allocRawMatrix(rows, columns);

	for (size_t row = 0; row < rows; ++row) {
		for (size_t column = 0; column < columns; ++column) {
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
	
	size_t elements = getRows();
	std::vector<T>* diagonal = new std::vector<T>();
	diagonal->reserve(elements);

	for (size_t i = 0; i < elements; ++i)
		diagonal->push_back(mRawMatrix[i][i]);

	return diagonal;
}

template<class T>
std::vector<T>* Matrix<T>::getRowElements(size_t row) const {
	if (row > mRows - 1)
		return new std::vector<T>(0);

	std::vector<T>* elements = new std::vector<T>();
	elements->reserve(mColumns);

	for (size_t column = 0; column < mColumns; ++column) {
		elements->push_back(mRawMatrix[row][column]);
	}

	return elements;
}

template<class T>
std::vector<T>* Matrix<T>::getColumnElements(size_t column) const {
	if (column > mColumns - 1)
		return new std::vector<T>();

	std::vector<T>* elements = new std::vector<T>();
	elements->reserve(mRows);

	for (size_t row = 0; row < mRows; ++row) {
		elements->push_back(mRawMatrix[row][column]);
	}

	return elements;
}

template<class T>
LUDecomposition<T>* Matrix<T>::getLUDecomposition() const {
	if (!isSquare())
		return new LUDecomposition<T>();

	size_t n = mRows;
	RawMatrix<T> lower = *allocRawMatrix(n, n);
	RawMatrix<T> upper = *allocRawMatrix(n, n);

	for (size_t i = 0; i < n; ++i) {

		// Upper Triangular
		for (size_t k = i; k < n; ++k) {

			// Summation of L(i, j) * U(j, k)
			int sum = 0;
			for (size_t j = 0; j < i; ++j)
				sum += (lower[i][j] * upper[j][k]);

			// Evaluating U(i, k)
			upper[i][k] = get(i, k) - sum;
		}

		// Lower Triangular
		for (size_t k = i; k < n; ++k) {
			if (i == k)
				lower[i][i] = 1; // Diagonal as 1
			else {
				// Summation of L(k, j) * U(j, i)
				int sum = 0;
				for (size_t j = 0; j < i; ++j)
					sum += (lower[k][j] * upper[j][i]);

				// Evaluating L(k, i)
				lower[k][i] = (get(k, i) - sum) / upper[i][i];
			}
		}
	}

	LUDecomposition<T>* decomposition = new LUDecomposition<T>(n);
	decomposition->L = new Matrix<T>(lower);
	decomposition->U = new Matrix<T>(upper);

	return decomposition;
}

template<class T>
Matrix<T>& Matrix<T>::Square() {
	Matrix<T>* matrix = new Matrix<T>(*this);

	*matrix *= *this;

	return *matrix;
}

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
	size_t rows = mRows, columns = mColumns;

	if (rows != rhs.getRows()) {
		return *this;
	}
	if (columns != rhs.getColumns()) {
		return *this;
	}

	for (size_t row = 0; row < rows; ++row) {
		for (size_t column = 0; column < columns; ++column) {
			mRawMatrix[row][column] += rhs.get(row, column);
		}
	}

	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
	size_t rows = mRows, columns = mColumns;

	if (rows != rhs.getRows()) {
		return *this;
	}
	if (columns != rhs.getColumns()) {
		return *this;
	}

	for (size_t row = 0; row < rows; ++row) {
		for (size_t column = 0; column < columns; ++column) {
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

	for (size_t row = 0; row < mRows; ++row) {
		for (size_t column = 0; column < mColumns; ++column) {
			double result = 0; // Maybe need to change type?
			for (size_t r = 0; r < mColumns; ++r) {
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
	size_t rows = mRows, columns = mColumns;

	for (auto & i : mRawMatrix) {
		for (T & el : i) {
			el *= value;
		}
	}

	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator/=(const T& value) {
	size_t rows = mRows, columns = mColumns;

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

	for (size_t r = 0; r < mRows; ++r) {
		for (size_t c = 0; c < mColumns; ++c) {
			matrix.set(r, c, -get(r, c));
		}
	}

	return matrix;
}


template<class T>
RawMatrix<T>* Matrix<T>::allocRawMatrix(size_t rows, size_t columns, T defaultValue) const {
	RawMatrix<T>* rawMatrix = new RawMatrix<T>(rows);

	for (auto & r : *rawMatrix) {
		r = std::vector<T>(columns);
		for (auto & el : r) {
			el = defaultValue;
		}
	}

	return rawMatrix;
}


/*
	TODO:
	* Move it to another file
*/
template <class T>
struct LUDecomposition {
	Matrix<T>* L;
	Matrix<T>* U;
	size_t size;
	bool isEmpty;

	LUDecomposition(size_t n) {
		size = n;

		if (size != 0)
			isEmpty = false;
	}

	LUDecomposition() {
		size = 0;
		isEmpty = true;
	}
};