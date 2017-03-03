#pragma once
#include <string>
#include "Token.h"
#include <fstream>
class Lexer {

public:

	Lexer(std::string filename);
	Token nextToken(std::ifstream& fp);
	void Analyze(std::string filename);
};