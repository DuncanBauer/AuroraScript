#pragma once

#include "Tokens.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct StatementNode;
struct AssignmentStatementNode;
struct VariableDeclarationStatementNode;
struct ExpressionNode;
struct AdditiveExpressionNode;
struct MultiplicativeExpressionNode;
struct UnaryExpressionNode;
struct PostfixExpressionNode;
struct PrimaryExpressionNode;
struct IdentifierNode;
struct NumberNode;
struct StringNode;
struct BoolNode;

enum class NodeType {
	PROGRAM,
	STATEMENT,
	ASSIGNMENT_STATEMENT,
	VARIABLE_DECLARATION_STATEMENT,
	EXPRESSION,
	ADDITIVE_EXPRESSION,
	MULTIPLICATIVE_EXPRESSION,
	UNARY_EXPRESSION,
	POSTFIX_EXPRESSION,
	PRIMARY_EXPRESSION,
	IDENTIFIER,
	NUMBER,
	STRING,
	BOOL
};

struct ASTNode {
	virtual ~ASTNode() = default;
	virtual void Print() = 0;

	NodeType type;
};

struct StatementNode : public ASTNode {
	virtual void Print() {}

	NodeType type = NodeType::STATEMENT;
};

struct ExpressionNode : public ASTNode {
	virtual void Print() {}

	NodeType type = NodeType::EXPRESSION;
};

struct BoolNode : public ASTNode {
	BoolNode() {}
	BoolNode(bool value) : value(value) {}

	virtual void Print() {
		std::cout << value;
	}

	NodeType type = NodeType::BOOL;
	bool value;
};

struct IdentifierNode : public ASTNode {
	IdentifierNode() {}
	IdentifierNode(std::string value) : value(value) {}

	virtual void Print() {
		std::cout <<  value;
	}
	
	NodeType type = NodeType::IDENTIFIER;
	std::string value;
};

struct NumberNode : public ASTNode {
	NumberNode() {}
	NumberNode(double value) : value(value) {}

	virtual void Print() {
		std::cout << value;
	}

	NodeType type = NodeType::NUMBER;
	double value;
};

struct StringNode : public ASTNode {
	StringNode() {}
	StringNode(std::string value) : value(value) {}

	virtual void Print() {
		std::cout << value;
	}
	
	NodeType type = NodeType::STRING;
	std::string value;
};

struct ProgramNode : public ASTNode {
	virtual void Print() {
		for (int i = 0; i < statements.size(); i++) {
			statements[i]->Print();
		}
	}
	
	NodeType type = NodeType::PROGRAM;
	std::vector<std::unique_ptr<ASTNode>> statements;
};

struct AssignmentStatementNode : public ASTNode {
	AssignmentStatementNode() {}
	
	virtual void Print() {
		if (left) {
			left->Print();
		}

		std::cout << " = ";
		
		if (right) {
			right->Print();
		}
		
		std::cout << std::endl;
	}

	NodeType type = NodeType::ASSIGNMENT_STATEMENT;
	std::unique_ptr<ASTNode> left = nullptr;
	std::unique_ptr<ASTNode> right = nullptr;
};

struct VariableDeclarationStatementNode : public ASTNode {
	VariableDeclarationStatementNode() {}
	VariableDeclarationStatementNode(DataType dataType, std::unique_ptr<ASTNode> identifier, std::unique_ptr<ASTNode> value)
		: dataType(dataType), identifier(std::move(identifier)), value(std::move(value)) {}

	virtual void Print() {
		std::cout << "Variable Declaration: ";
		
		switch (dataType) {
			case DataType::BOOL:
				std::cout << "bool ";
				break;
			case DataType::NUMBER:
				std::cout << "number ";
				break;
			case DataType::STRING:
				std::cout << "string ";
				break;
			case DataType::VOID:
				std::cout << "void ";
				break;
			default:
				break;
		}

		if (identifier) {
			identifier->Print();
		}
		
		if (value) {
			std::cout << " = ";
			value->Print();
		}
		
		std::cout << std::endl;
	}

	NodeType type = NodeType::VARIABLE_DECLARATION_STATEMENT;
	DataType dataType;
	std::unique_ptr<ASTNode> identifier = nullptr;
	std::unique_ptr<ASTNode> value = nullptr;
};

struct PrimaryExpressionNode : public ASTNode {
	PrimaryExpressionNode() {}
	PrimaryExpressionNode(std::unique_ptr<ASTNode> expr)
		: expr(std::move(expr)) {}

	virtual void Print() {
		if (expr)
			expr->Print();
	}

	NodeType type = NodeType::PRIMARY_EXPRESSION;
	std::unique_ptr<ASTNode> expr = nullptr;
};

struct PostfixExpressionNode : public ASTNode {
	PostfixExpressionNode() {}
	PostfixExpressionNode(std::unique_ptr<ASTNode> expr, Token op = Token::TOK_)
		: expr(std::move(expr)), op(op) {}

	virtual void Print() {
		if (expr)
			expr->Print();
	}

	NodeType type = NodeType::POSTFIX_EXPRESSION;
	std::unique_ptr<ASTNode> expr = nullptr;
	Token op = Token::TOK_;
};

struct UnaryExpressionNode : public ASTNode {
	UnaryExpressionNode() {}
	UnaryExpressionNode(std::unique_ptr<ASTNode> expr, Token op = Token::TOK_)
		: expr(std::move(expr)), op(op) {}

	virtual void Print() {
		if(expr)
			expr->Print();
	}

	NodeType type = NodeType::UNARY_EXPRESSION;
	std::unique_ptr<ASTNode> expr = nullptr;
	Token op = Token::TOK_;
};

struct MultiplicativeExpressionNode : public ASTNode {
	MultiplicativeExpressionNode() {}
	MultiplicativeExpressionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, Token op = Token::TOK_)
		: left(std::move(left)), right(std::move(right)), op(op) {}

	virtual void Print() {
		if(left)
			left->Print();

		if(op != Token::TOK_) 
			std::cout << " " << (int)op << " ";

		if(right)
			right->Print();
	}

	NodeType type = NodeType::MULTIPLICATIVE_EXPRESSION;
	std::unique_ptr<ASTNode> left = nullptr;
	std::unique_ptr<ASTNode> right = nullptr;
	Token op = Token::TOK_;
};

struct AdditiveExpressionNode : public ASTNode {
	AdditiveExpressionNode() {}
	AdditiveExpressionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, Token op = Token::TOK_)
		: left(std::move(left)), right(std::move(right)), op(op) {}

	virtual void Print() {
		if (left)
			left->Print();

		if(op != Token::TOK_)
			std::cout << " " << (int)op << " ";

		if (right)
			right->Print();
	}

	NodeType type = NodeType::ADDITIVE_EXPRESSION;
	std::unique_ptr<ASTNode> left = nullptr;
	std::unique_ptr<ASTNode> right = nullptr;
	Token op = Token::TOK_;
};

class Parser
{
	public:
		Parser(std::vector<std::pair<Token, std::string>> tokens) :m_tokens(tokens) {
			m_currentToken = 0;
			m_currentLine = 0;
		}

		std::unique_ptr<ASTNode> Parse();

	private:
		std::unique_ptr<ASTNode> ParseProgram();

		std::unique_ptr<ASTNode> ParseStatement();
		std::unique_ptr<ASTNode> ParseAssignmentStatement();
		std::unique_ptr<ASTNode> ParseVariableDeclarationStatement();

		std::unique_ptr<ASTNode> ParseExpression();
		std::unique_ptr<ASTNode> ParseAdditiveExpression();
		std::unique_ptr<ASTNode> ParseMultiplicativeExpression();
		std::unique_ptr<ASTNode> ParseUnaryExpression();
		std::unique_ptr<ASTNode> ParsePostfixExpression();
		std::unique_ptr<ASTNode> ParsePrimaryExpression();

		void ConsumeToken() {
			m_currentToken++;

			while (m_currentToken < m_tokens.size() &&
				  (m_tokens[m_currentToken].first == Token::TOK_SPACE ||
				   m_tokens[m_currentToken].first == Token::TOK_TAB)) {
				m_currentToken++;
			}
		}

		std::pair<Token, std::string> PeekToken() {
			if (m_tokens.size() < m_currentToken + 1) {
				return m_tokens[m_currentToken + 1];
			}
			return std::make_pair(Token::TOK_EOF, "");
		}

		std::pair<Token, std::string> PeekToken(size_t offset) {
			if (m_tokens.size() < m_currentToken + offset) {
				return m_tokens[m_currentToken + offset];
			}
			return std::make_pair(Token::TOK_EOF, "");
		}

		bool IsAtEnd() {
			return m_currentToken >= m_tokens.size();
		}

	private:
		std::vector<std::pair<Token, std::string>> m_tokens;
		size_t m_currentToken;
		size_t m_currentLine;
};