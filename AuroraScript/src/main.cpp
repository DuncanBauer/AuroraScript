#include "common.h"

#include "Lexer.h"
#include "Parser.h"

#include <fstream>
#include <sstream>

int main(int argc, char** argv)
{
	try
	{
		std::ifstream file("test2.as");
		std::stringstream buf;
	
		buf << file.rdbuf();
		file.close();

		std::string data = buf.str();
		Lexer lexer;
		std::vector<std::pair<Token, std::string>> tokens = lexer.Tokenize(data);

		for (auto t : tokens) {
			//if (t.first == Token::TOK_NEW_LINE) continue;
			std::cout << (int)t.first << ' ';
			std::cout << t.second << '\n';
		}

		std::cin.ignore(1000, '\n');

		Parser parser(tokens);
		auto ast = parser.Parse();
		
		std::cin.ignore(1000, '\n');
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}

}