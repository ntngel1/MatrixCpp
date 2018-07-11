# MatrixCpp
Really lightweight and simple single-file library to work with matrices. 

## Usage

```cpp
Matrix<int> m(3, 4); // init new matrix with size 3x4 (3 rows by 4 columns)

m.set(0, 0, 10); // set an element at position (0, 0) to value 10

int value = m.get(0, 0); // get an value at position (0, 0)
std::cout << value << std::endl; // will output "10"
```
