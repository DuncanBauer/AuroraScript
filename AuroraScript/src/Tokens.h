#pragma once

enum class Token {
	TOK_IDENTIFIER,		// [a-zA-Z_][a-zA-Z0-9_]*

	// Keywords
	TOK_CLASS,			// class
	TOK_FUNCTION,		// function
	TOK_RETURN,			// return
	TOK_IF,				// if
	TOK_ELSE,			// else
	TOK_DO,				// do
	TOK_WHILE,			// while
	TOK_FOR,			// for
	TOK_SWITCH,			// switch
	TOK_CASE,			// case
	TOK_END,			// end
	TOK_BREAK,			// break
	TOK_CONTINUE,		// continue
	TOK_CONST,			// const
	TOK_TRUE,			// true
	TOK_FALSE,			// false
	TOK_NULL,			// null

	// Types
	TOK_VOID,			// void
	TOK_BOOL,			// bool
	TOK_NUMBER,			// number
	TOK_STRING,			// string

	// Literals
	TOK_STRING_LIT,		// ".*"
	TOK_NUMBER_LIT,		// [0-9]+

	// Operators
	TOK_OPEN_PAREN,		// (
	TOK_CLOSE_PAREN,	// )
	TOK_OPEN_BRACE,		// {
	TOK_CLOSE_BRACE,	// }
	TOK_OPEN_BRACKET,	// [
	TOK_CLOSE_BRACKET,	// ]

	TOK_COMMA,			// ,
	TOK_DOT,			// .
	TOK_QUESTION,		// ?
	TOK_COLON,			// :
	TOK_SEMICOLON,		// ;
	
	TOK_DOUBLE_QUOTE,	// "
	TOK_SINGLE_QUOTE,	// '
	TOK_BACK_TICK,		// `

	TOK_BITWISE_AND,	// &
	TOK_BITWISE_OR,		// |
	TOK_BITWISE_XOR,	// ^
	TOK_BITWISE_NOT,	// ~
	TOK_BITWISE_AND_EQUAL,	// &=
	TOK_BITWISE_OR_EQUAL,	// |=
	TOK_BITWISE_XOR_EQUAL,	// ^=
	TOK_BITWISE_NOT_EQUAL,	// ~=
	
	TOK_AND,			// &&
	TOK_OR,				// ||
	TOK_XOR,			// ^^
	TOK_NOT,			// !

	TOK_ASSIGN,			// =
	TOK_LOOSE_EQUAL,	// ==
	TOK_STRICT_EQUAL,	// ===
	TOK_NOT_EQUAL,		// !=

	TOK_LESS,						// <
	TOK_GREATER,					// >
	TOK_LESS_EQUAL,					// <=
	TOK_GREATER_EQUAL,				// >=
	TOK_BITWISE_SHIFT_LEFT,			// <<
	TOK_BITWISE_SHIFT_RIGHT,		// >>
	TOK_BITWISE_SHIFT_LEFT_EQUAL,	// <<=
	TOK_BITWISE_SHIFT_RIGHT_EQUAL,	// >>=

	// Arithmetic
	TOK_PLUS,			// +
	TOK_MINUS,			// -
	TOK_STAR,			// *
	TOK_SLASH,			// /
	TOK_MOD,			// %

	TOK_PLUS_EQUAL,		// +=
	TOK_MINUS_EQUAL,	// -=
	TOK_STAR_EQUAL,		// *=
	TOK_SLASH_EQUAL,	// /=
	TOK_MOD_EQUAL,		// %=

	TOK_INCREMENT,		// ++
	TOK_DECREMENT,		// --
};