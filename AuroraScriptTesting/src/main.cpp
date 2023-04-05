#include <iostream>

int main(int argc, char** argv)
{
	try
	{	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}

	std::cin.ignore(1000, '\n');
}