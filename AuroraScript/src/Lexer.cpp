#include "common.h"

std::vector<std::pair<Token, std::string>> Tokenize(std::string data)
{
	std::vector<std::pair<Token, std::string>> tokens;
	std::regex masterRegex(GetMasterRegex());

	std::sregex_iterator iter(data.begin(), data.end(), masterRegex);
	std::sregex_iterator end;

	if (std::distance(iter, end) == 0) {
		std::cout << "No matches found for regular expression.\n";
		return tokens;
	}

	while (iter != end) {
		std::smatch match = *iter;
		Token tokenType;
		std::string tokenValue;

		// Get Token type and value from match
		for (int i = 0; i < match.size(); i++)
		{
			if (!match[i].str().empty())
			{
				for (const auto& tokenRegex : TOKEN_REGEXES)
				{
					if (std::regex_match(match[i].str(), std::regex(tokenRegex.second)))
					{
						tokenType = tokenRegex.first;
						tokenValue = match[i].str();
						tokens.push_back(std::make_pair(tokenType, tokenValue));
						break;
					}
				}
				break;
			}
		}

		iter++;
	}

	return tokens;
}

std::string GetMasterRegex() {
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