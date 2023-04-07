#include "Parser.h"

#include <iostream>

std::unique_ptr<ASTNode> Parser::Parse()
{
	std::cout << "Parsing..." << std::endl;
	return ParseProgram();
}

std::unique_ptr<ProgramNode> Parser::ParseProgram()
{
	std::cout << __FUNCTION__ << std::endl;
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

//std::unique_ptr<BlockNode> Parser::ParseBlock()
//{
//	std::cout << __FUNCTION__ << std::endl;
//	if (m_tokens[m_currentToken].first != Token::TOK_OPEN_BRACE) {
//		std::cout << "Expected '{' on line " << m_currentLine << std::endl;
//		return nullptr;
//	}
//	
//	ConsumeToken();
//	auto node = std::make_unique<BlockNode>();
//	while (m_tokens[m_currentToken].first != Token::TOK_CLOSE_BRACE && !IsAtEnd()) {
//		auto statement = ParseStatement();
//		if (statement) {
//			node->statements.push_back(std::move(statement));
//		}
//		ConsumeToken();
//	}
//
//	if (!IsAtEnd() && m_tokens[m_currentToken].first != Token::TOK_CLOSE_BRACE) {
//		std::cout << "Expected '}' on line " << m_currentLine << std::endl;
//		return nullptr;
//	}
//	ConsumeToken();
//
//	return node;
//}

std::unique_ptr<StatementNode> Parser::ParseStatement()
{
	std::cout << __FUNCTION__ << std::endl;
	auto statement = std::make_unique<StatementNode>();

	std::pair<Token, std::string> tokenType = m_tokens[m_currentToken];
	switch (tokenType.first) {
		//case Token::TOK_IF: 
		//	statement = ParseIfStatement();
		//	break;
		//case Token::TOK_RETURN: 
		//	statement = ParseReturnStatement();
		//	break;
		case Token::TOK_BOOL: 
		case Token::TOK_NUMBER:
		case Token::TOK_STRING:
			statement = ParseVarStatement();
			break;
		default:
			break;
	}
	ConsumeToken();
	return statement;
}

//std::unique_ptr<IfStatementNode> Parser::ParseIfStatement()
//{
//	std::cout << __FUNCTION__ << std::endl;
//	ConsumeToken();
//	if (m_tokens[m_currentToken].first != Token::TOK_OPEN_PAREN) {
//		std::cout << "Expected '(' after 'if' on line " << m_currentLine << std::endl;
//	} else {
//		ConsumeToken();
//	}
//
//	auto condition = ParseExpression();
//	if (!condition) {
//		std::cout << "Expected expression after '(' on line " << m_currentLine << std::endl;
//	} else {
//		ConsumeToken();
//	}
//
//	if (m_tokens[m_currentToken].first != Token::TOK_CLOSE_PAREN) {
//		std::cout << "Expected ')' after expression on line " << m_currentLine << std::endl;
//	}
//	else {
//		ConsumeToken();
//	}
//
//	auto ifblock = ParseBlock();
//
//	if (m_tokens[m_currentToken].first == Token::TOK_ELSE) {
//		ConsumeToken();
//		if (m_tokens[m_currentToken].first != Token::TOK_OPEN_BRACE) {
//			std::cout << "Expected '{' after 'else' on line " << m_currentLine << std::endl;
//		} else {
//			ConsumeToken();
//		}
//
//		auto elseBlock = ParseBlock();
//		return std::make_unique<IfStatementNode>(std::move(condition), std::move(ifblock), std::move(elseBlock));
//	}
//
//	return nullptr;
//}
//
//std::unique_ptr<ReturnStatementNode> Parser::ParseReturnStatement()
//{
//	std::cout << __FUNCTION__ << std::endl;
//	ConsumeToken();
//	auto expr = ParseExpression();
//	if (expr) {
//		return std::make_unique<ReturnStatementNode>(std::move(expr));
//	}
//
//	return std::make_unique<ReturnStatementNode>();
//}

std::unique_ptr<VarStatementNode> Parser::ParseVarStatement()
{
	std::cout << __FUNCTION__ << std::endl;
	Token type = m_tokens[m_currentToken].first;
	if (type == Token::TOK_BOOL ||
		type == Token::TOK_NUMBER ||
		type == Token::TOK_STRING) {
		ConsumeToken();
	} else {
		std::cout << "Expected type on line " << m_currentLine << std::endl;
	}

	std::string ident = ParseIdentifierExpression()->name;

	if (m_tokens[m_currentToken].first == Token::TOK_ASSIGN) {
		ConsumeToken();
		auto expr = ParseExpression();
		if (expr) {
			return std::make_unique<VarStatementNode>(std::move(type), std::move(ident), std::move(expr));
		}
	}

	return nullptr;
}

std::unique_ptr<ExpressionNode> Parser::ParseExpression()
{
	std::cout << __FUNCTION__ << std::endl;
	return ParseBinaryExpression();
}

std::unique_ptr<ExpressionNode> Parser::ParsePrimaryExpression()
{
	std::cout << __FUNCTION__ << std::endl;
	if (m_tokens[m_currentToken].first == Token::TOK_NUMBER_LIT ||
		m_tokens[m_currentToken].first == Token::TOK_STRING_LIT || 
		m_tokens[m_currentToken].first == Token::TOK_TRUE		||
		m_tokens[m_currentToken].first == Token::TOK_FALSE) {
		return ParseLiteralExpression();
	} else if (m_tokens[m_currentToken].first == Token::TOK_IDENTIFIER) {
		return ParseIdentifierExpression();
	} else if (m_tokens[m_currentToken].first == Token::TOK_OPEN_PAREN) {
		ConsumeToken();
		auto expr = ParseExpression();
		if (m_tokens[m_currentToken].first != Token::TOK_CLOSE_PAREN) {
			std::cout << "Expected ')' on line " << m_currentLine << std::endl;
			return nullptr;
		}

		ConsumeToken();
		if (expr) {
			return expr;
		}
	}
	std::cout << "Unexpected token" << std::endl;
	return nullptr;
}

std::unique_ptr<BinaryExpressionNode> Parser::ParseBinaryExpression()
{
	std::cout << __FUNCTION__ << std::endl;
	auto left = ParsePrimaryExpression();
	std::cout << "left: " <<  << std::endl;
	
	ConsumeToken();
	if (!left) {
		std::cout << "Expected expression before operator on line " << m_currentLine << std::endl;
		return nullptr;
	}

	auto op = m_tokens[m_currentToken].first;
	ConsumeToken();

	auto right = ParseExpression();
	ConsumeToken();
	if (!right) {
		std::cout << "Expected expression after operator on line " << m_currentLine << std::endl;
		return nullptr;
	}

	return std::make_unique<BinaryExpressionNode>(std::move(left), std::move(right), std::move(op));
}

std::unique_ptr<LiteralExpressionNode> Parser::ParseLiteralExpression()
{
	std::cout << __FUNCTION__ << std::endl;
	if (m_tokens[m_currentToken].first == Token::TOK_STRING_LIT) {
		std::string val = m_tokens[m_currentToken].second;
		ConsumeToken();
		return std::make_unique<LiteralExpressionNode>(val);
	} else if (m_tokens[m_currentToken].first == Token::TOK_NUMBER_LIT) {
		double val = std::stod(m_tokens[m_currentToken].second);
		ConsumeToken();
		return std::make_unique<LiteralExpressionNode>(val);
	} else if (m_tokens[m_currentToken].first == Token::TOK_TRUE) {
		bool val = true;
		ConsumeToken();
		return std::make_unique<LiteralExpressionNode>(val);
	} else if (m_tokens[m_currentToken].first == Token::TOK_FALSE) {
		bool val = false;
		ConsumeToken();
		return std::make_unique<LiteralExpressionNode>(val);
	}
	else {
		return nullptr;
	}
}

std::unique_ptr<IdentifierExpressionNode> Parser::ParseIdentifierExpression()
{
	std::cout << __FUNCTION__ << std::endl;
	Token type = m_tokens[m_currentToken].first;
	std::string val = m_tokens[m_currentToken].second;

	if (type == Token::TOK_IDENTIFIER) {
		ConsumeToken();
		return std::make_unique<IdentifierExpressionNode>(val);
	}
	
	std::cout << "Expected identifier on line " << m_currentLine << std::endl;
	return nullptr;
}