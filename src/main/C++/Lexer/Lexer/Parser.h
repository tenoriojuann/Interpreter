#pragma once
#include "json.hpp"
#include "Token.h"
#include "Lexer.h"
#include "Node.h"
#include <list>
#include "Token.h"
#include <list>

class Parser {

public:
	Parser(std::string filename);

	std::list<Token> delimited(Token start, Token stop, Token separator, Token(*parser()));

	Node parse_toplevel();

	Node parse_if();

	auto parse_atom();
	
};
