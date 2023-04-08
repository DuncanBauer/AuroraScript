#include "Parser.h"
#include "Tokens.h"

#include <iostream>

std::unique_ptr<ASTNode> Parser::Parse() {
	std::cout << __FUNCTION__ << std::endl;

	return ParseProgram();
}

std::unique_ptr<ASTNode> Parser::ParseProgram() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	auto node = std::make_unique<ProgramNode>();
	while (!IsAtEnd())
	{
		auto statement = ParseStatement();
		if (statement) {
			node->statements.push_back(std::move(statement));
		}
	}
	return node;
}

std::unique_ptr<ASTNode> Parser::ParseStatement() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	switch (m_tokens[m_currentToken].first) {
		case Token::TOK_NEW_LINE:
			ConsumeToken();
			m_currentLine++;
			break;
		case Token::TOK_BOOL:
		case Token::TOK_NUMBER:
		case Token::TOK_STRING:
			return ParseVariableDeclarationStatement();
		default:
			return ParseExpression();
	};
}

std::unique_ptr<ASTNode> Parser::ParseAssignmentStatement() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	if (IsAtEnd()) {
		std::cout << "Unexpected end of input on line " << m_currentLine << std::endl;
		return nullptr;
	}

	auto retVal = std::make_unique<AssignmentStatementNode>();
	retVal->left = ParseExpression();

	return retVal;
}

std::unique_ptr<ASTNode> Parser::ParseVariableDeclarationStatement() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	if (IsAtEnd()) {
		std::cout << "Unexpected end of input on line " << m_currentLine << std::endl;
		return nullptr;
	}
	
	auto retVal = std::make_unique<VariableDeclarationStatementNode>();

	DataType type = DataType::BOOL;
	switch (m_tokens[m_currentToken].first) {
		case Token::TOK_BOOL:
			type = DataType::BOOL;
			break;
		case Token::TOK_NUMBER:
			type = DataType::NUMBER;
			break;
		case Token::TOK_STRING:
			type = DataType::STRING;
			break;
	};
	retVal->dataType = type;
	
	ConsumeToken();
	if (IsAtEnd()) {
		std::cout << "Unexpected end of input on line " << m_currentLine << std::endl;
		return nullptr;
	}
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	if (m_tokens[m_currentToken].first != Token::TOK_IDENTIFIER) {
		std::cout << "Expected identifier on line " << m_currentLine << std::endl;

		while (m_currentToken < m_tokens.size() && m_tokens[m_currentToken].first != Token::TOK_NEW_LINE) {
			ConsumeToken();
		}
		return nullptr;
	}

	auto identifier = std::make_unique<IdentifierNode>(m_tokens[m_currentToken].second);
	retVal->identifier = std::move(identifier);

	ConsumeToken();
	if (IsAtEnd()) {
		return retVal;
	}
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	// Switch on the next token to see if we have an assignment, another variable, or a newline
	switch (m_tokens[m_currentToken].first) {
		case Token::TOK_ASSIGN:
			ConsumeToken();
			if (IsAtEnd()) {
				std::cout << "Unexpected end of input. Expected value on line " << m_currentLine << "." << std::endl;
				return retVal;
			}

			if (type == DataType::BOOL) {
				if (m_tokens[m_currentToken].first == Token::TOK_TRUE || m_tokens[m_currentToken].first == Token::TOK_FALSE) {
					retVal->value = std::make_unique<BoolNode>();
				}
			}

			if (type == DataType::NUMBER) {
				if (m_tokens[m_currentToken].first == Token::TOK_NUMBER_LIT) {
					retVal->value = std::make_unique<BoolNode>();
				}
			}

			if (type == DataType::STRING) {
				if (m_tokens[m_currentToken].first == Token::TOK_STRING_LIT) {
					retVal->value = std::make_unique<BoolNode>();
				}
			}

			break;
		case Token::TOK_NEW_LINE:
			ConsumeToken();
			m_currentLine++;
			break;
		default:
			std::cout << "Unexpected token on line " << m_currentLine << std::endl;
	};

	return retVal;
}

std::unique_ptr<ASTNode> Parser::ParseExpression() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	if (IsAtEnd()) {
		std::cout << "Unexpected end of input on line " << m_currentLine << std::endl;
		return nullptr;
	}

	return ParseAdditiveExpression();
}

std::unique_ptr<ASTNode> Parser::ParseAdditiveExpression() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	if (IsAtEnd()) {
		std::cout << "Unexpected end of input on line " << m_currentLine << std::endl;
		return nullptr;
	}

	auto retVal = std::make_unique<AdditiveExpressionNode>();
	retVal->left = ParseMultiplicativeExpression();

	return retVal;
}

std::unique_ptr<ASTNode> Parser::ParseMultiplicativeExpression() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	if (IsAtEnd()) {
		std::cout << "Unexpected end of input on line " << m_currentLine << std::endl;
		return nullptr;
	}

	auto retVal = std::make_unique<MultiplicativeExpressionNode>();
	retVal->left = ParseUnaryExpression();

	return retVal;
}

std::unique_ptr<ASTNode> Parser::ParseUnaryExpression() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	if (IsAtEnd()) {
		std::cout << "Unexpected end of input on line " << m_currentLine << std::endl;
		return nullptr;
	}

	auto retVal = std::make_unique<UnaryExpressionNode>();
	retVal->expr = ParsePostfixExpression();

	return retVal;
}

std::unique_ptr<ASTNode> Parser::ParsePostfixExpression() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	if (IsAtEnd()) {
		std::cout << "Unexpected end of input on line " << m_currentLine << std::endl;
		return nullptr;
	}

	auto retVal = std::make_unique<PostfixExpressionNode>();
	retVal->expr = ParsePrimaryExpression();

	return retVal;
}

std::unique_ptr<ASTNode> Parser::ParsePrimaryExpression() {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "Token " << m_currentToken << ": " << m_tokens[m_currentToken].second << std::endl;

	if (IsAtEnd()) {
		std::cout << "Unexpected end of input on line " << m_currentLine << std::endl;
		return nullptr;
	}

	auto retVal = std::make_unique<PrimaryExpressionNode>();
	auto token = m_tokens[m_currentToken];
	switch (token.first) {
		case Token::TOK_IDENTIFIER:
			ConsumeToken();
			retVal->expr = std::make_unique<IdentifierNode>(token.second);
			break;
		case Token::TOK_NUMBER_LIT:
			ConsumeToken();
			retVal->expr = std::make_unique<NumberNode>(std::stod(token.second));
			break;
		case Token::TOK_STRING_LIT:
			ConsumeToken();
			retVal->expr = std::make_unique<StringNode>(token.second);
			break;
		case Token::TOK_TRUE:
			ConsumeToken();
			retVal->expr = std::make_unique<BoolNode>(true);
			break;
		case Token::TOK_FALSE:
			ConsumeToken();
			retVal->expr = std::make_unique<BoolNode>(false);
			break;
		case Token::TOK_OPEN_PAREN:
			ConsumeToken();
			retVal->expr = ParseExpression();

			if (m_tokens[m_currentToken].first == Token::TOK_CLOSE_PAREN) {
				ConsumeToken();
			} else {
				std::cout << "Expected ')' on line " << m_currentLine << std::endl;
			}
			break;
		default:
			std::cout << "Unexpected token on line " << m_currentLine << std::endl;
	}

	return retVal;
}



std::string TokenToString(Token token) {
	switch (token) {
	case Token::TOK_IDENTIFIER:
		return "TOK_IDENTIFIER";
	case Token::TOK_STRING_LIT:
		return "TOK_STRING_LIT";
	case Token::TOK_NUMBER_LIT:
		return "TOK_NUMBER_LIT";
	case Token::TOK_TRUE:
		return "TOK_TRUE";
	case Token::TOK_FALSE:
		return "TOK_FALSE";
	case Token::TOK_NULL:
		return "TOK_NULL";
	case Token::TOK_NEW_LINE:
		return "TOK_NEW_LINE";
	case Token::TOK_TAB:
		return "TOK_TAB";
	case Token::TOK_SPACE:
		return "TOK_SPACE";
	case Token::TOK_CLASS:
		return "TOK_CLASS";
	case Token::TOK_FUNCTION:
		return "TOK_FUNCTION";
	case Token::TOK_RETURN:
		return "TOK_RETURN";
	case Token::TOK_IF:
		return "TOK_IF";
	case Token::TOK_ELSE:
		return "TOK_ELSE";
	case Token::TOK_DO:
		return "TOK_DO";
	case Token::TOK_WHILE:
		return "TOK_WHILE";
	case Token::TOK_FOR:
		return "TOK_FOR";
	case Token::TOK_SWITCH:
		return "TOK_SWITCH";
	case Token::TOK_CASE:
		return "TOK_CASE";
	case Token::TOK_END:
		return "TOK_END";
	case Token::TOK_BREAK:
		return "TOK_BREAK";
	case Token::TOK_CONTINUE:
		return "TOK_CONTINUE";
	case Token::TOK_CONST:
		return "TOK_CONST";
	case Token::TOK_SELF:
		return "TOK_SELF";
	case Token::TOK_SUPER:
		return "TOK_SUPER";
	case Token::TOK_NEW:
		return "TOK_NEW";
	case Token::TOK_IMPORT:
		return "TOK_IMPORT";
	case Token::TOK_AS:
		return "TOK_AS";
	case Token::TOK_ENUM:
		return "TOK_ENUM";
	case Token::TOK_TRY:
		return "TOK_TRY";
	case Token::TOK_CATCH:
		return "TOK_CATCH";
	case Token::TOK_EOF:
		return "TOK_EOF";
	case Token::TOK_VOID:
		return "TOK_VOID";
	case Token::TOK_BOOL:
		return "TOK_BOOL";
	case Token::TOK_NUMBER:
		return "TOK_NUMBER";
	case Token::TOK_STRING:
		return "TOK_STRING";
	case Token::TOK_LINE_COMMENT:
		return "TOK_LINE_COMMENT";
	case Token::TOK_BLOCK_COMMENT:
		return "TOK_BLOCK_COMMENT";
	case Token::TOK_OPEN_PAREN:
		return "TOK_OPEN_PAREN";
	case Token::TOK_CLOSE_PAREN:
		return "TOK_CLOSE_PAREN";
	case Token::TOK_OPEN_BRACE:
		return "TOK_OPEN_BRACE";
	case Token::TOK_CLOSE_BRACE:
		return "TOK_CLOSE_BRACE";
	case Token::TOK_OPEN_BRACKET:
		return "TOK_OPEN_BRACKET";
	case Token::TOK_CLOSE_BRACKET:
		return "TOK_CLOSE_BRACKET";
	case Token::TOK_COMMA:
		return "TOK_COMMA";
	case Token::TOK_DOT:
		return "TOK_DOT";
	case Token::TOK_QUESTION:
		return "TOK_QUESTION";
	case Token::TOK_COLON:
		return "TOK_COLON";
	case Token::TOK_SEMICOLON:
		return "TOK_SEMICOLON";
	case Token::TOK_DOUBLE_QUOTE:
		return "TOK_DOUBLE_QUOTE";
	case Token::TOK_SINGLE_QUOTE:
		return "TOK_SINGLE_QUOTE";
	case Token::TOK_BACK_TICK:
		return "TOK_BACK_TICK";
	case Token::TOK_BITWISE_AND:
		return "TOK_BITWISE_AND";
	case Token::TOK_BITWISE_OR:
		return "TOK_BITWISE_OR";
	case Token::TOK_BITWISE_XOR:
		return "TOK_BITWISE_XOR";
	case Token::TOK_BITWISE_NOT:
		return "TOK_BITWISE_NOT";
	case Token::TOK_BITWISE_AND_ASSIGN:
		return "TOK_BITWISE_AND_ASSIGN";
	case Token::TOK_BITWISE_OR_ASSIGN:
		return "TOK_BITWISE_OR_ASSIGN";
	case Token::TOK_BITWISE_XOR_ASSIGN:
		return "TOK_BITWISE_XOR_ASSIGN";
	case Token::TOK_BITWISE_NOT_ASSIGN:
		return "TOK_BITWISE_NOT_ASSIGN";
	case Token::TOK_AND:
		return "TOK_AND";
	case Token::TOK_OR:
		return "TOK_OR";
	case Token::TOK_XOR:
		return "TOK_XOR";
	case Token::TOK_NOT:
		return "TOK_NOT";
	case Token::TOK_ASSIGN:
		return "TOK_ASSIGN";
	case Token::TOK_LOOSE_EQUAL:
		return "TOK_LOOSE_EQUAL";
	case Token::TOK_STRICT_EQUAL:
		return "TOK_STRICT_EQUAL";
	case Token::TOK_NOT_EQUAL:
		return "TOK_NOT_EQUAL";
	case Token::TOK_LESS:
		return "TOK_LESS";
	case Token::TOK_GREATER:
		return "TOK_GREATER";
	case Token::TOK_LESS_EQUAL:
		return "TOK_LESS_EQUAL";
	case Token::TOK_GREATER_EQUAL:
		return "TOK_GREATER_EQUAL";
	case Token::TOK_BITWISE_SHIFT_LEFT:
		return "TOK_BITWISE_SHIFT_LEFT";
	case Token::TOK_BITWISE_SHIFT_RIGHT:
		return "TOK_BITWISE_SHIFT_RIGHT";
	case Token::TOK_BITWISE_SHIFT_LEFT_ASSIGN:
		return "TOK_BITWISE_SHIFT_LEFT_ASSIGN";
	case Token::TOK_BITWISE_SHIFT_RIGHT_ASSIGN:
		return "TOK_BITWISE_SHIFT_RIGHT_ASSIGN";
	case Token::TOK_PLUS:
		return "TOK_PLUS";
	case Token::TOK_MINUS:
		return "TOK_MINUS";
	case Token::TOK_STAR:
		return "TOK_STAR";
	case Token::TOK_SLASH:
		return "TOK_SLASH";
	case Token::TOK_MOD:
		return "TOK_MOD";
	case Token::TOK_PLUS_ASSIGN:
		return "TOK_PLUS_ASSIGN";
	case Token::TOK_MINUS_ASSIGN:
		return "TOK_MINUS_ASSIGN";
	case Token::TOK_STAR_ASSIGN:
		return "TOK_STAR_ASSIGN";
	case Token::TOK_SLASH_ASSIGN:
		return "TOK_SLASH_ASSIGN";
	case Token::TOK_MOD_ASSIGN:
		return "TOK_MOD_ASSIGN";
	case Token::TOK_INCREMENT:
		return "TOK_INCREMEMNT";
	case Token::TOK_DECREMENT:
		return "TOK_DECREMENT";
	default:
		break;
	};
	return "TOK_UNKNOWN";
}