#include <iostream>
#include <time.h>
#include "PentominoSolver.h"

int main()
{
	PentominoSolver solver(10, 6);
	int n;

	clock_t t = clock();
	n = solver.Solve();
	t = clock() - t;

	std::cout << n << " solutions" <<  std::endl;
	std::cout << "time:" << (double)t / CLOCKS_PER_SEC << " sec." << std::endl;
	system("pause");

	return 0;
}