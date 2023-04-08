#include "Lexer.h"
#include "Parser.h"

#include <iostream>
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


		std::cout << "Token Count: " << tokens.size() << '\n';
		for (auto t : tokens) {
			//if (t.first == Token::TOK_NEW_LINE) continue;
			std::cout << (int)t.first << ' ';
			std::cout << t.second << '\n';
		}

		std::cin.ignore(1000, '\n');

		Parser parser(tokens);
		std::unique_ptr<ProgramNode> ast = parser.Parse();
		std::cout << "AST Size: " << ast->statements.size() << std::endl;
		
		for (int i = 0; i < ast->statements.size(); i++) {
			ast->statements[i]->Print();
		}
		
		std::cin.ignore(1000, '\n');
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}
}