#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include "Node.h"
#include <string>
#include <list>
#include <iostream>	
#include <map>



Parser::Parser(std::string filename)
{
	this->filename = filename;

}

void Parser::grabLineCode( Token tok)
{
	Lexer lex = Lexer(filename);
	int LineNum = 1;
	Token tok = lex.nextToken();
	tokens.push_back(tok);
	while (!tokens.back().getBool()) {

		Token *tokP = &tokens.back();

		if (tokens.back().getLexeme() == "if") {
			foundIF();
		}
		else if (tokens.back().getLexeme() == "then") {
			foundTHEN();
		}
		else if (tokens.back().getLexeme() == "while") {
			foundWHILE();
		}
		else if (tokens.back().getLexeme() == "end") {
			foudnEND();
		}
		else if (tokens.back().getLexeme() == "=") {
			foundEQ();
		}


		// Checking for new LINE
		tokens.push_back(lex.nextToken());
		if (tokens.back().getLineNum() > tokP->getLineNum()) {
			newLine();
		}

	}

}

void Parser::newLine() {
	//Token that belongs to the new line
	Token tmp = tokens.back();
	tokens.pop_back();


	if (tokens.back().getToken() != "LP" || tokens.back().getToken() != "LC") {
		tokens.push_back(Token("SEMI", ";", tokens.back().getLineNum()));
	}
	list.push_back(tokens);

	// Clearing the queue for the new line of the source code
	tokens.clear();
	//Pushing the first token of the new line
	tokens.push_back(tmp);
}

void Parser::foudnEND() {

	Token tmp = Token("RC", "}", tokens.back().getLineNum());
	tokens.pop_back();
	tokens.push_back(tmp);

}

void Parser::foundWHILE() {

	tokens.push_back(Token("LP", "(", tokens.back().getLineNum()));

}

void Parser::foundDO() {

	tokens.pop_back();
	tokens.push_back(Token("RP", ")", tokens.back().getLineNum()));
	tokens.push_back(Token("LC", "{", tokens.back().getLineNum()));
}

void Parser::foundIF() {

	tokens.push_back(Token("LP", "(", tokens.back().getLineNum()));

}

void Parser::foundTHEN() {

	tokens.pop_back();
	tokens.push_back(Token("RP", ")", tokens.back().getLineNum()));
	tokens.push_back(Token("KW", "THEN", tokens.back().getLineNum()));

}

void Parser::foundCOMMA() {

	if (tokens.front().getLexeme() != "local" || tokens.front().getLexeme() != "type") {

		std::cout << "ERROR ON LINE:" << tokens.front().getLineNum() << ",  define kind of variable" << std::endl;
	}
}

void Parser::foundEQ() {
	Token tmp = tokens.back();
	tokens.pop_back();

	// Looping through the list checking all of the deques for the variable definition
	if (tokens.back().getToken() == "ID") {
		bool search = false;
		for (int i = 0; i < list.size()-1; i++) {
			search = ScanQUEUE(tokens.back(), list[i]);
		}

		if (!search) {
			std::cout << "Error in line" << tokens.back().getLineNum() << " variable is not defined" << std::endl;
		}

		tokens.push_back(tmp);
	}

}


// Searches a deque for a specific token
bool Parser::ScanQUEUE(Token var, std::deque<Token> deq) {


	// found
	if (std::find(deq.begin(), deq.end(), var.getLexeme()) != deq.end()) {

		return true;
	}


	// Not found
	return false;
}






