#pragma once

// INCLUDES
#include <iostream>
#include <string>
#include <vector>

#include "Tokens.h"


// FUNCTION PROTOTYPES
std::vector<Token> lex(std::string data);

// MACROS
#define stringify(x) #x