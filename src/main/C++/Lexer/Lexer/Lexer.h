#pragma once
#include <string>
#include "Token.h"
#include <fstream>
class Lexer {

public:

	Lexer(char *filename[]);
	Token nextToken();
	void Analyze(char *filename[]);

private:

	std::ifstream fp;



};