#include <iostream>
#include "PentHandList.h"

int main()
{
	PentHandList plist(1, 10);
	PentHand p;

	while (plist.Next(&p))
	{
		std::cout << p.to_string() << std::endl;
	}

	system("pause");

	return 0;
}