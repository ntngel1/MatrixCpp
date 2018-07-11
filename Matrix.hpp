#include <cstdlib>
#include <cstring>
#include <iostream>

/*
	TODO: 
	* Iterator

	* Multiplying
	* Dividing
	* Substracting
	* Pow
	* Determinator
*/

template <class T>
class Matrix
{
public:
	Matrix(size_t width, size_t height) {
		this->mWidth = width;
		this->mHeight = height;

		this->mContainer = getContainer(width, height);
	}

	~Matrix() {
		freeContainer();
	}

	Matrix<T> copy() const {
		Matrix<T> copied = Matrix<T>(this->getWidth(), this->getHeight());

		for (size_t row = 0; row < mHeight; ++row) {
			for (size_t column = 0; column < mWidth; ++column) {
				T value = mContainer[row][column];
				copied.set(row, column, value);
			}
		}

		return copied;
	}

	void set(size_t row, size_t column, T value) {
		if (checkOutOfBounds(row, column)) {
			return;
		}

		mContainer[row][column] = value;
	} 

	T get(size_t row, size_t column) const {
		if (checkOutOfBounds(row, column))
			return T();

		return mContainer[row][column];
	}

	const T *const *const getRaw() const {
		return mContainer;
	}

	size_t getWidth() const {
		return mWidth;
	}

	size_t getHeight() const {
		return mHeight;
	}

	// TODO refactoring
	void display() const {
		size_t maxLength = 0;
		for (size_t row = 0; row < mHeight; ++row) {
			for (size_t column = 0; column < mWidth; ++column) {
				std::string str = std::to_string(this->get(row, column));
				if (str.length() > maxLength) {
					maxLength = str.length();
				}
			}
		}

		maxLength++;

		for (size_t row = 0; row < mHeight; ++row) {
			for (size_t column = 0; column < mWidth; ++column) {
				std::cout << mContainer[row][column];
				if (column == (mWidth - 1) && row == (mHeight - 1))
					continue;

				if (column != (mWidth - 1))
					std::cout << std::string(
						maxLength - std::to_string(this->get(row, column + 1)).length(),
						' '
						);

				if (column == (mWidth - 1))
					std::cout << std::string(
						maxLength - std::to_string(this->get(row + 1, 0)).length(),
						' '
						);
			}
			std::cout << std::endl;
		}
	}

	/* MATH OPERATIONS */

	bool isVector() const {
		if (mWidth == 1 && mHeight > 1)
			return true;
		else if (mHeight == 1 && mWidth > 1)
			return true;
		else
			return false;
	}

	bool isSquare() const {
		if (mWidth == mHeight)
			return true;
		else
			return false;
	}

	void transpose() {
		size_t width = this->getHeight(), height = this->getWidth();

		T** transposed = getContainer(width, height);

		for (size_t row = 0; row < height; ++row) {
			for (size_t column = 0; column < width; ++column) {
				transposed[row][column] = this->get(column, row);
			}
		}

		freeContainer();

		mContainer = transposed;
		this->mWidth = width;
		this->mHeight = height;
	}

	friend Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		size_t width = lhs.getWidth(), height = lhs.getHeight();

		Matrix<T> matrix = Matrix<T>(width, height);

		if (width != rhs.getWidth()) {
			return matrix;
		}
		if (height != rhs.getHeight()) {
			return matrix;
		}

		for (size_t row = 0; row < height; ++row) {
			for (size_t column = 0; column < width; ++column) {
				T result = lhs.get(row, column) + rhs.get(row, column);
				matrix.set(row, column, result);
			}
		}

		return matrix;
	}

	friend Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		size_t width = lhs.getWidth(), height = lhs.getHeight();

		Matrix<T> matrix = Matrix<T>(width, height);

		if (width != rhs.getWidth()) {
			return matrix;
		}
		if (height != rhs.getHeight()) {
			return matrix;
		}

		for (size_t row = 0; row < height; ++row) {
			for (size_t column = 0; column < width; ++column) {
				T result = lhs.get(row, column) - rhs.get(row, column);
				matrix.set(row, column, result);
			}
		}

		return matrix;
	}

	friend Matrix<T> operator*(const Matrix<T>& lhs, T rhs) {
		size_t width = lhs.getWidth(), height = lhs.getHeight();

		Matrix<T> matrix = Matrix<T>(width, height);

		for (size_t row = 0; row < height; ++row) {
			for (size_t column = 0; column < width; ++column) {
				T result = lhs.get(row, column) * rhs;
				matrix.set(row, column, result);
			}
		}

		return matrix;
	}

	friend Matrix<T>& operator*(T lhs, const Matrix<T>& rhs) {
		return rhs->Matrix::operator*(rhs, lhs);
	}

	friend Matrix<T> operator/(const Matrix<T>& lhs, T rhs) {
		size_t width = lhs.getWidth(), height = lhs.getHeight();

		Matrix<T> matrix = Matrix<T>(width, height);

		for (size_t row = 0; row < height; ++row) {
			for (size_t column = 0; column < width; ++column) {
				T result = lhs.get(row, column) / rhs;
				matrix.set(row, column, result);
			}
		}

		return matrix;
	}

	Matrix<T> operator-() const {
		size_t width = getWidth(), height = getHeight();

		Matrix<T> inversed = Matrix<T>(getWidth(), getHeight());

		for (size_t row = 0; row < height; ++row) {
			for (size_t column = 0; column < width; ++column) {
				T inversedValue = get(row, column) * -1;
				inversed.set(row, column, inversedValue);
			}
		}

		return inversed;
	}

	Matrix<T>& operator=(const Matrix<T>& matrix) {
		if (this == &matrix)
			return *this;

		for (size_t row = 0; row < mHeight; ++row) {
			for (size_t column = 0; column < mWidth; ++column) {
				mContainer[row][column] = matrix.get(row, column);
			}
		}

		return *this;
	}
	
private:
	size_t mWidth;
	size_t mHeight;
	T** mContainer;

private:
	T** getContainer(size_t width, size_t height) const
	{
		T** container = new T*[height];

		for (size_t i = 0; i < height; ++i) {
			container[i] = new T[width];
		}

		
		for (size_t row = 0; row < height; ++row) {
			for (size_t column = 0; column < width; ++column) {
				container[row][column] = 0;
			}
		}

		return container;
	}

	bool checkOutOfBounds(size_t row, size_t column) const {
		if (row > mHeight - 1) {
			return true;
		}

		if (column > mWidth - 1) {
			return true;
		}

		return false;
	}

	void freeContainer() {
		for (size_t i = 0; i < mHeight; ++i) {
			delete[] mContainer[i];
		}

		delete[] mContainer;
	}
};