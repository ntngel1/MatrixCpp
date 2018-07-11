# MatrixCpp
Really lightweight and simple single-file library to work with matrices. 

## Usage

```cpp
Matrix<int> m(3, 4); // init new matrix with size 3x4 (3 rows by 4 columns)

m.set(0, 0, 10); // set an element at position (0, 0) to value 10

int value = m.get(0, 0); // get an value at position (0, 0)
std::cout << value << std::endl; // will output "10"
```

Multiplying and dividing a matrix by some value:

```cpp
Matrix<int> m(3, 3);

m.set(0, 0, 5);
m.set(2, 2, 6);

/*   Matrix:

	5 | 0 | 0
	0 | 0 | 0
    0 | 0 | 6
*/

m = m * 2; // multiplying a matrix by two

/*   Matrix:

   10 | 0 |  0
	0 | 0 |  0
	0 | 0 | 12

*/

m = m / 2; // dividing a matrix by two

/*   Matrix:

	5 | 0 | 0
	0 | 0 | 0
    0 | 0 | 6
*/
```