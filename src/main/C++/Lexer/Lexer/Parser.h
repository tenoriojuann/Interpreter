#pragma once
#include "Token.h"
#include "Lexer.h"
#include "Node.h"
#include <list>
#include <vector>
#include <deque>

class Parser {

public:

	std::vector<std::deque<Token>> list;

	std::string filename;
	std::deque<Token> tokens;


	void newLine();

	Parser(std::string filename);

	void grabLineCode();

	void foudnEND();

	void foundWHILE();

	void foundDO();

	void foundTHEN();

	void foundCOMMA();

	void foundEQ();

	bool ScanQUEUE(Token var, std::deque<Token> deq);

	void foundIF();


};
