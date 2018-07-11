#include <cstdlib>
#include <cstring>
#include <iostream>

/*
	TODO: 
	* MOVE TO VECTOR!!!!!!!!

	* Iterator

	* Multiplying
	* Dividing
	* Substracting
	* Pow
	* Determinator
*/

template <class T>
struct LUDecomposition;

template <class T>
class Matrix
{
public:
	Matrix() {
		this->mWidth = 0;
		this->mHeight = 0;
	}

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

	static Matrix<T> from(T** container, size_t width, size_t height) {
		Matrix<T> matrix(width, height);
		matrix.mContainer = container;

		return matrix;
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

	LUDecomposition<T> getLUDecomposition() {
		/* I don't understand anything here :D I just copied this from this resource: 
		   https://www.geeksforgeeks.org/doolittle-algorithm-lu-decomposition
		   Thanks for this :)
		*/

		if (!isSquare())
			return LUDecomposition<T>();

		size_t n = getWidth();
		T** lower = getContainer(n, n);
		T** upper = getContainer(n, n);

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

    	LUDecomposition<T> decomposition(n);
    	decomposition.L = from(lower, n, n);
    	decomposition.U = from(upper, n, n);

    	return decomposition;
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

		mWidth = matrix.getWidth();
		mHeight = matrix.getHeight();

		freeContainer();
		mContainer = getContainer(mWidth, mHeight);

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

template <class T>
struct LUDecomposition {
	Matrix<T> L;
	Matrix<T> U;
	size_t size;

	LUDecomposition() {
		size = 0;
	}

	LUDecomposition(size_t n) {
		L = Matrix<T>(n, n);
		U = Matrix<T>(n, n);
		size = n;
	}
};