#include "common.h"
#include <fstream>
#include <sstream>

int main(int argc, char** argv)
{
	try
	{
		std::ifstream file("test.as");
		std::stringstream buf;
	
		buf << file.rdbuf();
		file.close();

		std::string data = buf.str();
		std::cout << data << '\n';

		std::vector<Token> tokens = lex(data);
		for(Token t : tokens)
			std::cout << (int)t << ' ';
		std::cout << '\n';

		std::cin.ignore(1000, '\n');
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}

}