#include "Lexer.h"

#include <iostream>
#include <regex>

std::vector<std::pair<Token, std::string>> Lexer::Tokenize()
{
	std::regex masterRegex(GetMasterRegex());
	std::sregex_iterator iter(data.begin(), data.end(), masterRegex);
	std::sregex_iterator end;

	if (std::distance(iter, end) == 0) {
		std::cout << "No matches found for regular expression.\n";
		return tokens;
	}

	while (iter != end) {
		std::smatch match = *iter;

		// Get Token type and value from match
		for (int i = 0; i < match.size(); i++) {
			if (!match[i].str().empty()) {
				FindToken(match[i]);
				break;
			}
		}
		iter++;
	}
	return tokens;
}

std::vector<std::pair<Token, std::string>> Lexer::Tokenize(std::string _data)
{
	data = _data;
	std::regex masterRegex(GetMasterRegex());
	std::sregex_iterator iter(data.begin(), data.end(), masterRegex);
	std::sregex_iterator end;

	if (std::distance(iter, end) == 0) {
		std::cout << "No matches found for regular expression.\n";
		return tokens;
	}

	while (iter != end) {
		std::smatch match = *iter;

		// Get Token type and value from match
		for (int i = 0; i < match.size(); i++) {
			if (!match[i].str().empty()) {
				FindToken(match[i]);
				break;
			}
		}
		iter++;
	}
	return tokens;
}

void Lexer::FindToken(auto match) {
	for (const auto& tokenRegex : TOKEN_REGEXES) {
		if (std::regex_match(match.str(), std::regex(tokenRegex.second))) {
			//if (tokenRegex.first == Token::TOK_NEW_LINE ||
			//	tokenRegex.first == Token::TOK_TAB ||
			//	tokenRegex.first == Token::TOK_SPACE
			//	) {
			//	break;
			//}
			tokens.push_back(std::make_pair(tokenRegex.first, match.str()));
			break;
		}
	}
}

std::string Lexer::GetMasterRegex() {
	std::string pattern = "";

	// Create a massive regex statement so we can match literally any token.
	// Trust me, it'll be tremendous
	for (const auto& token : TOKEN_REGEXES) {
		pattern += "(?:" + token.second + ")|";
	}
	
	// Remove trailing | character
	pattern.pop_back();
	return pattern;
}