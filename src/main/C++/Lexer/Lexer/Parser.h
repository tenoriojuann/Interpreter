#pragma once
#include "Token.h"
#include "Lexer.h"
#include <list>
#include "Token.h"
#include <vector>
#include <deque>

class Parser {

public:

<<<<<<< HEAD
	std::vector<std::deque<Token> > list;
=======
	std::vector<std::deque<Token>> list;
>>>>>>> refs/remotes/tenoriojuann/master
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
<<<<<<< HEAD
=======
	void printT();
>>>>>>> refs/remotes/tenoriojuann/master
	void foundIF();
	void foundSM();
	void foundDIV();
	void foundSUB();
	void foundMUL();
};
