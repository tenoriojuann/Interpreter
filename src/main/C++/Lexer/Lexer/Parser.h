#pragma once
#include "json.hpp"
#include "Token.h"
#include "Lexer.h"


class Parser {

public:
	Parser(std::string filename);

	using json = nlohmann::json;

	json FALSE;

};