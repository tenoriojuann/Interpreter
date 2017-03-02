#pragma once
#include <string>
#include "Token.h"

class Lexer {

public:

	Lexer(FILE *fp, char *filename[]);
	Token nextToken();
	void Analyze(char *filename[]);

private:

	FILE *fp;



};