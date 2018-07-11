#include "./Matrix.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
	Matrix<int> matrix(3, 3);
	matrix.set(0, 0, 5);
	matrix.set(0, 1, 10);
	matrix.set(0, 2, 20);

	matrix.set(1, 0, 30);
	matrix.set(1, 1, 40);
	matrix.set(1, 2, 50);

	matrix.set(2, 0, 60);
	matrix.set(2, 1, 70);
	matrix.set(2, 2, 80);

	matrix.display();

/*	
	LUDecomposition<int> dec = matrix.getLUDecomposition();
	dec.L.display();
	std::cout << std::endl;
	dec.U.display();
	*/
	//ччччstd::cout << std::endl;
	//Matrix<int> another(10, 10);
	//matrix = another;
	//matrix.display();


	return 0;
}