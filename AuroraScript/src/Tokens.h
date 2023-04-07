#pragma once

enum class UnaryExpressionType {
	PREFIX,
	POSTFIX
};

enum class Token {
	TOK_IDENTIFIER,		// [a-zA-Z_][a-zA-Z0-9_]*

	// Literals
	TOK_STRING_LIT,		// ".*"
	TOK_NUMBER_LIT,		// [0-9]+
	TOK_TRUE,			// true
	TOK_FALSE,			// false
	TOK_NULL,			// null
	TOK_NEW_LINE, 		// \n
	TOK_TAB,			// \t
	TOK_SPACE,			// ' '

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
	TOK_SELF, 			// self
	TOK_SUPER,			// super
	TOK_NEW,			// new
	TOK_IMPORT,			// import
	TOK_AS,				// as
	TOK_ENUM,			// enum
	TOK_TRY,			// try
	TOK_CATCH,			// catch
	TOK_EOF,			// EOF

	// Types
	TOK_VOID,			// void
	TOK_BOOL,			// bool
	TOK_NUMBER,			// number
	TOK_STRING,			// string

	// Comment symbols
	TOK_LINE_COMMENT,	// //
	TOK_BLOCK_COMMENT,	// /* .* */

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
	TOK_BITWISE_AND_ASSIGN,	// &=
	TOK_BITWISE_OR_ASSIGN,	// |=
	TOK_BITWISE_XOR_ASSIGN,	// ^=
	TOK_BITWISE_NOT_ASSIGN,	// ~=
	
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
	TOK_BITWISE_SHIFT_LEFT_ASSIGN,	// <<=
	TOK_BITWISE_SHIFT_RIGHT_ASSIGN,	// >>=

	// Arithmetic
	TOK_PLUS,			// +
	TOK_MINUS,			// -
	TOK_STAR,			// *
	TOK_SLASH,			// /
	TOK_MOD,			// %

	TOK_PLUS_ASSIGN,		// +=
	TOK_MINUS_ASSIGN,	// -=
	TOK_STAR_ASSIGN,		// *=
	TOK_SLASH_ASSIGN,	// /=
	TOK_MOD_ASSIGN,		// %=

	TOK_INCREMENT,		// ++
	TOK_DECREMENT,		// --
};

const std::vector<std::pair<Token, std::string>> TOKEN_REGEXES = {
	// Keywords
	{ Token::TOK_CLASS, "class$" },								// class
	{ Token::TOK_FUNCTION, "function$" },						// function
	{ Token::TOK_RETURN, "return$" },							// return
	{ Token::TOK_IF, "if$" },									// if
	{ Token::TOK_ELSE, "else$" },								// else
	{ Token::TOK_DO, "do$" },									// do
	{ Token::TOK_WHILE, "while$" },								// while
	{ Token::TOK_FOR, "for$" },									// for
	{ Token::TOK_SWITCH, "switch$" },							// switch
	{ Token::TOK_CASE, "case$" },								// case
	{ Token::TOK_END, "end$" },									// end
	{ Token::TOK_BREAK, "break$" },								// break
	{ Token::TOK_CONTINUE, "continue$" },						// continue
	{ Token::TOK_CONST, "const$" },								// const
	{ Token::TOK_SELF, "self$" },								// self
	{ Token::TOK_SUPER, "super$" },								// super
	{ Token::TOK_NEW, "new$" },									// new
	{ Token::TOK_IMPORT, "import$" },							// import
	{ Token::TOK_AS, "as$" },									// as
	{ Token::TOK_ENUM, "enum" },								// enum
	{ Token::TOK_TRY, "try" },									// try
	{ Token::TOK_CATCH, "catch" },								// catch
	{ Token::TOK_EOF, "" },										// EOF

	// Types
	{ Token::TOK_VOID, "void$" },								// void
	{ Token::TOK_BOOL, "bool$" },								// bool
	{ Token::TOK_NUMBER, "number$" },							// number
	{ Token::TOK_STRING, "string$" },							// string

	{ Token::TOK_NEW_LINE, "\n" },								// \n
	{ Token::TOK_TAB, "\t" },									// \t
	{ Token::TOK_SPACE, " " },									// ' '
	{ Token::TOK_LINE_COMMENT, "//.*\n" },						// // .*
	{ Token::TOK_BLOCK_COMMENT, "\\/\\*.*\\*\\/" },				// /* .* */

	// Operators
	{ Token::TOK_OPEN_PAREN, "\\($" },							// (
	{ Token::TOK_CLOSE_PAREN, "\\)$" },							// )
	{ Token::TOK_OPEN_BRACE, "\\{$" },							// {
	{ Token::TOK_CLOSE_BRACE, "\\}$" },							// }
	{ Token::TOK_OPEN_BRACKET, "\\[$" },						// [
	{ Token::TOK_CLOSE_BRACKET, "\\]$" },						// ]

	{ Token::TOK_COMMA, ",$" },									// ,
	{ Token::TOK_DOT, "\\.$" },									// .
	{ Token::TOK_QUESTION, "\\?$" },							// ?
	{ Token::TOK_COLON, ":$" },									// :
	{ Token::TOK_SEMICOLON, ";$" },								// ;

	{ Token::TOK_DOUBLE_QUOTE, "\"$" },							// "
	{ Token::TOK_SINGLE_QUOTE, "'$" },							// '
	{ Token::TOK_BACK_TICK, "`$" },								// `

	{ Token::TOK_BITWISE_AND_ASSIGN, "&=$" },					// &=
	{ Token::TOK_BITWISE_OR_ASSIGN, "\\|=$" },					// |=
	{ Token::TOK_BITWISE_XOR_ASSIGN, "\\^=$" },					// ^=
	{ Token::TOK_BITWISE_NOT_ASSIGN, "\\~=$" },					// ~=

	{ Token::TOK_AND, "&&$" },									// &&
	{ Token::TOK_OR, "\\|\\|$" },								// ||
	{ Token::TOK_XOR, "\\^\\^$" },								// ^^

	{ Token::TOK_BITWISE_AND, "&$" },							// &
	{ Token::TOK_BITWISE_OR, "\\|$" },							// |
	{ Token::TOK_BITWISE_XOR, "\\^$" },							// ^
	{ Token::TOK_BITWISE_NOT, "\\~$" },							// ~

	{ Token::TOK_STRICT_EQUAL, "===$" },						// ===
	{ Token::TOK_LOOSE_EQUAL, "==$" },							// ==
	{ Token::TOK_ASSIGN, "=" },								// =
	{ Token::TOK_NOT_EQUAL, "!=$" },							// !=
	{ Token::TOK_NOT, "!$" },									// !

	{ Token::TOK_BITWISE_SHIFT_LEFT_ASSIGN, "<<=$" },			// <<=
	{ Token::TOK_BITWISE_SHIFT_RIGHT_ASSIGN, ">>=$" },			// >>=
	{ Token::TOK_LESS_EQUAL, "<=$" },							// <=
	{ Token::TOK_GREATER_EQUAL, ">=$" },						// >=
	{ Token::TOK_BITWISE_SHIFT_LEFT, "<<$" },					// <<
	{ Token::TOK_BITWISE_SHIFT_RIGHT, ">>$" },					// >>
	{ Token::TOK_LESS, "<$" },									// <
	{ Token::TOK_GREATER, ">$" },								// >

	// Arithmetic
	{ Token::TOK_PLUS_ASSIGN, "\\+=$" },						// +=
	{ Token::TOK_MINUS_ASSIGN, "-=$" },							// -=
	{ Token::TOK_STAR_ASSIGN, "\\*=$" },						// *=
	{ Token::TOK_SLASH_ASSIGN, "/=$" },							// /=
	{ Token::TOK_MOD_ASSIGN, "%=$" },							// %=

	{ Token::TOK_INCREMENT, "\\+\\+$" },						// ++
	{ Token::TOK_DECREMENT, "--$" },							// --

	{ Token::TOK_PLUS, "\\+$" },								// +
	{ Token::TOK_MINUS, "-$" },									// -
	{ Token::TOK_STAR, "\\*$" },								// *
	{ Token::TOK_SLASH, "/$" },									// /
	{ Token::TOK_MOD, "%$" },									// %

	// Literals
	{ Token::TOK_STRING_LIT, "(\".*\")|(\'.*\')|(`.*`)" },		// ".*"
	{ Token::TOK_NUMBER_LIT, "[-]?(\\d+)?(.\\d+)?" },			// [0-9]+
	{ Token::TOK_TRUE, "true$" },								// true
	{ Token::TOK_FALSE, "false$" },								// false
	{ Token::TOK_NULL, "null$" },								// null

	// User-made identifiers
	{ Token::TOK_IDENTIFIER, "[a-zA-Z_][a-zA-Z0-9_]*" },		// [a-zA-Z_][a-zA-Z0-9_]*
};