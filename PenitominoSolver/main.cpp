#include <iostream>
#include "PentHand.h"

int main()
{
	PentHand *p = new PentHand[PentHand::Shape::NumOfShapes];
	int i;
	for (i = 0; i < PentHand::Shape::NumOfShapes; i++)
	{
		p[i].Set(1, 10, (PentHand::Shape)i);
		std::cout << p[i].to_string() << std::endl;
		p[i] = p[i].Shift(2);
		std::cout << p[i].to_string() << std::endl;
		std::cout << p[i].IsSorted() << std::endl;
	}

	system("pause");

	return 0;
}