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
		std::vector<std::pair<Token, std::string>> tokens = Tokenize(data);

		for (auto t : tokens) {
			std::cout << (int)t.first << ' ';
			std::cout << t.second << '\n';
		}

		std::cin.ignore(1000, '\n');
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}

}