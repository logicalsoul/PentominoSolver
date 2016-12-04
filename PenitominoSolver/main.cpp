#include <iostream>
#include "PentominoSolver.h"

int main()
{
	PentominoSolver solver(10, 6);

	std::cout << solver.Solve() << std::endl;
	system("pause");

	return 0;
}