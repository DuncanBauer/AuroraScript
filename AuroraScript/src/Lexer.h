#pragma once

#include "Tokens.h"

#include <string>
#include <vector>

class Lexer {
	public:
		Lexer() {}
		Lexer(std::string _data) : data(_data) {}
		std::vector<std::pair<Token, std::string>> Tokenize();
		std::vector<std::pair<Token, std::string>> Tokenize(std::string _data);

	private:
		void FindToken(auto match);
		std::string GetMasterRegex();
		
	private:
		std::string data;
		std::vector<std::pair<Token, std::string>> tokens;
	
		void Advance();
		void SkipWhitespace();
		void SkipLineComment();
		void SkipBlockComment();
		void Skipstring();
		void SkipNumber();
		void SkipIdentifier();
		void SkipOperator();
		void SkipChar();
};