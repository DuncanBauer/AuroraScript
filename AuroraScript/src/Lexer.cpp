#include "common.h"

std::vector<Token> lex(std::string data)
{
	std::vector<Token> tokens;
	int index = 0;
	int length = data.length();

	while (index < length)
	{
		std::cout << "Next token: " << data[index] << '\n';
		std::cout << "Index: " << index << " < " << "Length: " << length << '\n';

		char c = data[index];
		if (c == '(') {
			tokens.push_back(Token::TOK_OPEN_PAREN);
		}
		else if (c == ')') {
			tokens.push_back(Token::TOK_CLOSE_PAREN);
		}
		else if (c == '{') {
			tokens.push_back(Token::TOK_OPEN_BRACE);
		}
		else if (c == '}') {
			tokens.push_back(Token::TOK_CLOSE_BRACE);
		}
		else if (c == '[') {
			tokens.push_back(Token::TOK_OPEN_BRACKET);
		}
		else if (c == ']') {
			tokens.push_back(Token::TOK_CLOSE_BRACKET);
		}
		else if (c == ',') {
			tokens.push_back(Token::TOK_COMMA);
		}
		else if (c == '.') {
			tokens.push_back(Token::TOK_DOT);
		}
		else if (c == '?') {
			tokens.push_back(Token::TOK_QUESTION);
		}
		else if (c == ':') {
			tokens.push_back(Token::TOK_COLON);
		}
		else if (c == ';') {
			tokens.push_back(Token::TOK_SEMICOLON);
		}
		else if (c == '"') {
			tokens.push_back(Token::TOK_DOUBLE_QUOTE);
		}
		else if (c == '\'') {
			tokens.push_back(Token::TOK_SINGLE_QUOTE);
		}
		else if (c == '`') {
			tokens.push_back(Token::TOK_BACK_TICK);
		}

		else if (c == '&') {
			char next = data[index + 1];
			if (next == '&') {
				tokens.push_back(Token::TOK_AND);
			}
			else if (next == '=') {
				tokens.push_back(Token::TOK_BITWISE_AND_EQUAL);
				index++;
			} 
			else {
				tokens.push_back(Token::TOK_BITWISE_AND);
				index++;
			}
		}
		else if (c == '|') {
			char next = data[index + 1];
			if (next == '|') {
				tokens.push_back(Token::TOK_OR);
			}
			else if (next == '=') {
				tokens.push_back(Token::TOK_BITWISE_OR_EQUAL);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_BITWISE_OR);
				index++;
			}
		}
		else if (c == '^') {
			char next = data[index + 1];
			if (next == '=') {
				tokens.push_back(Token::TOK_BITWISE_XOR_EQUAL);
				index++;
			}
			else if (next == '^') {
				tokens.push_back(Token::TOK_XOR);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_BITWISE_XOR);
			}
		}
		else if (c == '~') {
			char next = data[index + 1];
			if (next == '=') {
				tokens.push_back(Token::TOK_BITWISE_NOT_EQUAL);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_BITWISE_NOT);
			}
		}
		else if (c == '<') {
			char next = data[index + 1];
			if (next == '<') {
				index++;
				char next2 = data[index + 1];
				if (next2 == '=') {
					tokens.push_back(Token::TOK_BITWISE_SHIFT_LEFT_EQUAL);
					index++;
				}
				else {
					tokens.push_back(Token::TOK_BITWISE_SHIFT_LEFT);
				}
			}
			else if (next == '=') {
				tokens.push_back(Token::TOK_LESS_EQUAL);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_LESS);
			}
		}
		else if (c == '>') {
			char next = data[index + 1];
			if (next == '>') {
				index++;
				char next2 = data[index + 1];
				if (next2 == '=') {
					tokens.push_back(Token::TOK_BITWISE_SHIFT_RIGHT_EQUAL);
					index++;
				}
				else {
					tokens.push_back(Token::TOK_BITWISE_SHIFT_RIGHT);
				}
			}
			else if (next == '=') {
				tokens.push_back(Token::TOK_GREATER_EQUAL);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_GREATER);
			}
		}

		else if (c == '+') {
			char next = data[index + 1];
			if (next == '=') {
				tokens.push_back(Token::TOK_PLUS_EQUAL);
				index++;
			}
			else if (next == '+') {
				tokens.push_back(Token::TOK_INCREMENT);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_PLUS);
			}
		}
		else if (c == '-') {
			char next = data[index + 1];
			if (next == '=') {
				tokens.push_back(Token::TOK_MINUS_EQUAL);
				index++;
			}
			else if (next == '-') {
				tokens.push_back(Token::TOK_DECREMENT);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_MINUS);
			}
		}
		else if (c == '*') {
			char next = data[index + 1];
			if (next == '=') {
				tokens.push_back(Token::TOK_STAR_EQUAL);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_STAR);
			}
		}
		else if (c == '/') {
			char next = data[index + 1];
			if (next == '=') {
				tokens.push_back(Token::TOK_SLASH_EQUAL);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_SLASH);
			}
		}
		else if (c == '%') {
			char next = data[index + 1];
			if (next == '=') {
				tokens.push_back(Token::TOK_MOD_EQUAL);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_MOD);
			}
		}
		else if (c == '=') {
			char next = data[index + 1];
			if (next == '=') {
				index++;
				char next2 = data[index + 1];
				if (next2 == '=') {
					tokens.push_back(Token::TOK_STRICT_EQUAL);
					index++;
				}
				else {
					tokens.push_back(Token::TOK_LOOSE_EQUAL);
				}
			}
			else {
				tokens.push_back(Token::TOK_ASSIGN);
			}
		}
		else if (c == '!') {
			char next = data[index + 1];
			if (next == '=') {
				tokens.push_back(Token::TOK_NOT_EQUAL);
				index++;
			}
			else {
				tokens.push_back(Token::TOK_NOT);
			}
		}
		
		//else if (c == "class") {
		//	tokens.push_back(Token::TOK_CLASS);
		//}
		//else if (c == "function") {
		//	tokens.push_back(Token::TOK_FUNCTION);
		//}
		//else if (c == "return") {
		//	tokens.push_back(Token::TOK_RETURN);
		//}
		//else if (c == "if") {
		//	tokens.push_back(Token::TOK_IF);
		//}
		//else if (c == "do") {
		//	tokens.push_back(Token::TOK_DO);
		//}
		//else if (c == "else") {
		//	tokens.push_back(Token::TOK_ELSE);
		//}
		//else if (c == "while") {
		//	tokens.push_back(Token::TOK_WHILE);
		//}
		//else if (c == "for") {
		//	tokens.push_back(Token::TOK_FOR);
		//}
		//else if (c == "do") {
		//	tokens.push_back(Token::TOK_DO);
		//}
		//else if (c == "switch") {
		//	tokens.push_back(Token::TOK_SWITCH);
		//}
		//else if (c == "case") {
		//	tokens.push_back(Token::TOK_CASE);
		//}
		//else if (c == "break") {
		//	tokens.push_back(Token::TOK_BREAK);
		//}
		//else if (c == "continue") {
		//	tokens.push_back(Token::TOK_CONTINUE);
		//}
		//else if (c == "const") {
		//	tokens.push_back(Token::TOK_CONST);
		//}
		//else if (c == "true") {
		//	tokens.push_back(Token::TOK_TRUE);
		//}
		//else if (c == "false") {
		//	tokens.push_back(Token::TOK_FALSE);
		//}
		//else if (c == "null") {
		//	tokens.push_back(Token::TOK_NULL);
		//}

		index++;
	}

	return tokens;
}