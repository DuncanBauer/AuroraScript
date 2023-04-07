#pragma once

#include "common.h"

#include <map>
#include <string>
#include <vector>

struct ASTNode {
	virtual ~ASTNode() = default;
};

struct ProgramNode : public ASTNode {
	std::vector<std::unique_ptr<ASTNode>> statements;
};

struct BlockNode : public ASTNode {
	std::vector<std::unique_ptr<ASTNode>> statements;
};

struct StatementNode : public ASTNode {};

struct IfStatementNode : public StatementNode {
	IfStatementNode(std::unique_ptr<ASTNode> condition, std::unique_ptr<ASTNode> ifBlock, std::unique_ptr<ASTNode> elseBlock) :
		condition(std::move(condition)), ifBlock(std::move(ifBlock)), elseBlock(std::move(elseBlock)) {}
	std::unique_ptr<ASTNode> condition;
	std::unique_ptr<ASTNode> ifBlock;
	std::unique_ptr<ASTNode> elseBlock;
};

struct ReturnStatementNode : public StatementNode {
	ReturnStatementNode() {}
	ReturnStatementNode(std::unique_ptr<ASTNode> value) 
		: value(std::move(value)) {}
	std::unique_ptr<ASTNode> value;
};

struct VarStatementNode : public StatementNode {
	VarStatementNode(Token type, std::string name, std::unique_ptr<ASTNode> value) 
		: type(type), name(name), value(std::move(value)) {}
	Token type;
	std::string name;
	std::unique_ptr<ASTNode> value;
};

//struct WhileStatementNode : public StatementNode {
//	std::unique_ptr<ASTNode> condition;
//	std::unique_ptr<ASTNode> block;
//};

struct ExpressionNode : public ASTNode {
};

struct UnaryExpressionNode : public ExpressionNode {
	UnaryExpressionNode(Token op, std::unique_ptr<ExpressionNode> operand, UnaryExpressionType type)
		: operand(std::move(operand)), op(op), type(type) {}
	Token op;
	std::unique_ptr<ExpressionNode> operand;
	UnaryExpressionType type;
};

struct BinaryExpressionNode : public ExpressionNode {
	BinaryExpressionNode(std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right, Token op)
		: left(std::move(left)), right(std::move(right)), op(op) {}
	std::unique_ptr<ExpressionNode> left;
	std::unique_ptr<ExpressionNode> right;
	Token op;
};

struct LiteralExpressionNode : public ExpressionNode {
	LiteralExpressionNode(std::string stringVal) 
		: stringVal(stringVal), type(Token::TOK_STRING) {}
	LiteralExpressionNode(double numberVal) 
		: numberVal(numberVal), type(Token::TOK_NUMBER) {}
	LiteralExpressionNode(bool boolVal) 
		: boolVal(boolVal), type(Token::TOK_BOOL) {}

	Token type;
	std::string stringVal = "";
	double numberVal = 0;
	bool boolVal = false;
};

struct IdentifierExpressionNode : public ExpressionNode {
	IdentifierExpressionNode(std::string name) : name(name) {}
	std::string name;
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
	std::unique_ptr<ProgramNode> ParseProgram();
	std::unique_ptr<BlockNode> ParseBlock();
	std::unique_ptr<StatementNode> ParseStatement();
	std::unique_ptr<IfStatementNode> ParseIfStatement();
	std::unique_ptr<ReturnStatementNode> ParseReturnStatement();
	std::unique_ptr<VarStatementNode> ParseVarStatement();

	std::unique_ptr<ExpressionNode> ParseExpression();
	std::unique_ptr<ExpressionNode> ParsePrimaryExpression();
	std::unique_ptr<UnaryExpressionNode> ParseUnaryExpression();
	std::unique_ptr<BinaryExpressionNode> ParseBinaryExpression();
	std::unique_ptr<LiteralExpressionNode> ParseLiteralExpression();
	std::unique_ptr<IdentifierExpressionNode> ParseIdentifierExpression();
	
	void ConsumeToken() {
		m_currentToken++;
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