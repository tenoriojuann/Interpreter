﻿#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include <string>
#include <list>
#include <iostream>	
#include <map>
#include <algorithm>
#include <vector>
#include <deque>




Parser::Parser(std::string filename)
{
	this->filename = filename;

}

void Parser::grabLineCode()
{
	
	Lexer lex(filename);
	int LineNum = 1;
	Token tok = lex.nextToken();
	tokens.push_back(tok);
	while (lex.fp.is_open()) {

		
		
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

		else if (tokens.back().getToken() == "ID") {
			foundID();
		}

		
		// Checking for new LINE
		 tok = lex.nextToken();
		if (tokens.back().getLineNum() < tok.getLineNum()) {
			tokens.push_back(tok);
			newLine();
		}
		else {
			tokens.push_back(tok);
		}


	}

}

void Parser::newLine() {
	//Token that belongs to the new line
	Token tmp = tokens.back();
	tokens.pop_back();



	 if ((tokens.front().getLexeme() == "while")) {
		tokens.push_back(Token("RP", ")", tokens.back().getLineNum()));
		tokens.push_back(Token("LC", "{", tokens.back().getLineNum()));
		list.push_back(tokens);

		// Clearing the queue for the new line of the source code
		tokens.clear();
		//Pushing the first token of the new line
		tokens.push_back(tmp);

	}
	
	else if (tmp.getLexeme() == "end") {
		foudnEND();
	}
	else if (tmp.getLexeme() == "if") {
		tokens.clear();
		tokens.push_back(tmp);
		foundIF();
	}
	else if (tmp.getToken() == "COM") {
		tokens.clear();
		tokens.push_back(tmp);
		foundCOMMENT();
	}
	else if (tokens.back().getToken() != "LP" && tokens.back().getToken() != "LC" && tokens.back().getToken() != "RP") {
		
		tokens.push_back(Token("SEMI", ";", tokens.back().getLineNum()));
		list.push_back(tokens);

		// Clearing the queue for the new line of the source code
		tokens.clear();
		//Pushing the first token of the new line
		tokens.push_back(tmp);

	}

}
	
void Parser::foundCOMMENT() {
	
	Token tmp = tokens.back();
	tokens.pop_back();


	std::string st = tmp.getLexeme();
	st.erase(0, 2);
	std::string cm = "   //";
	cm += st;
	tmp.setLexeme(cm);
	tokens.push_back(tmp);
}


void Parser::foudnEND() {

	Token tmp = Token("RC", "}", tokens.back().getLineNum());
	if (tokens.back().getLexeme() == "end") {

		tokens.pop_back();
	}
	list.push_back(tokens);
	tokens.clear();
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

	Token tmp = tokens.back();
	tokens.pop_back();
	tokens.push_back(Token("RP", ")", tmp.getLineNum()));
	tokens.push_back(Token("LC", "{", tmp.getLineNum()));
	list.push_back(tokens);

}

void Parser::foundCOMMA() {

	if (tokens.front().getLexeme() != "local" || tokens.front().getLexeme() != "type") {

		std::cout << "ERROR ON LINE:" << tokens.front().getLineNum() << ",  define kind of variable" << std::endl;
	}
}

void Parser::foundEQ() {


	//



}


void Parser::foundID() {


	bool search = false;

	if (tokens.front().getLexeme() == "type") return;

	else {
		for (int i = 0; i < list.size(); i++) {

			search = ScanQUEUE(tokens.back().getLexeme(), list[i]);
		}

		if (!search) {
			std::cout << "Error in line " << tokens.back().getLineNum() << ": variable '" << tokens.back().getLexeme() << "' is not defined" << std::endl;
		}
	}



}

void Parser::foundSM(){
	Token tmp = tokens.back();
	tokens.pop_back();
	if(tokens.back().getLexeme() == "+")
	{
		bool search = false;
		for (unsigned int i = 0; i < list.size()-1; i++) 
		{
			search = ScanQUEUE("+", list[i]);
		}
		if (!search) 
		{
			std::cout << "Error in line" << tokens.back().getLineNum() << " variable is not defined" << std::endl;
		}


		tokens.push_back(tmp);
		
	}
	if(tokens.front().getLexeme() != "ID" || tokens.front().getLexeme() != "NUM")
	{
		std::cout<<"Error, Number or ID expected at: " << tokens.back().getLineNum() << std::endl;
	}
}
void Parser::foundMUL(){
	Token tmp = tokens.back();
	tokens.pop_back();
	if(tokens.back().getLexeme() == "*")
	{
		bool search = false;
		for (unsigned int i = 0; i < list.size()-1; i++) 
		{
			search = ScanQUEUE(tokens.back().getLexeme(), list[i]);
		}
		if (!search) 
		{
			std::cout << "Error in line" << tokens.back().getLineNum() << " variable is not defined" << std::endl;
		}
		tokens.push_back(tmp);
		
	}
	if(tokens.front().getLexeme() != "ID" || tokens.front().getLexeme() != "NUM")
	{
		std::cout<<"Error, Number or ID expected at: " << tokens.back().getLineNum() << std::endl;
	}
	
}
void Parser::foundSUB(){
	Token tmp = tokens.back();
	tokens.pop_back();
	if(tokens.back().getLexeme() == "-")
	{
		bool search = false;
		for (unsigned int i = 0; i < list.size()-1; i++) 
		{
			search = ScanQUEUE("-", list[i]);
		}
		if (!search) 
		{
			std::cout << "Error in line" << tokens.back().getLineNum() << " variable is not defined" << std::endl;
		}
		tokens.push_back(tmp);
		
	}
	if(tokens.front().getLexeme() != "ID" || tokens.front().getLexeme() != "NUM")
	{
		std::cout<<"Error, Number or ID expected at: " << tokens.back().getLineNum() << std::endl;
	}
	
}
void Parser::foundDIV(){
	Token tmp = tokens.back();
	tokens.pop_back();
	if(tokens.back().getLexeme() == "/")
	{
		bool search = false;
		for (unsigned int i = 0; i < list.size()-1; i++) 
		{
			search = ScanQUEUE("/", list[i]);
		}
		if (!search) 
		{
			std::cout << "Error in line" << tokens.back().getLineNum() << " variable is not defined" << std::endl;
		}
		tokens.push_back(tmp);
		
	}
	if(tokens.front().getLexeme() != "ID" || tokens.front().getLexeme() != "NUM")
	{
		std::cout<<"Error, Number or ID expected at: " << tokens.back().getLineNum() << std::endl;
	}
	
}




// Searches a deque for a specific token
bool Parser::ScanQUEUE(std::string var, std::deque<Token> &deq) {


	// using a lambda function to search the 
	// since we are searching a list of deques of tokens
	// and looking for a specific string


	auto pred = [var]( Token & item) {
		return item.getLexeme() == var;
	};
	auto x = std::find_if(deq.begin(), deq.end(), pred) != deq.end();

	return x;
}


void Parser::printT() 
{
	// For every queue in the list
	for (std::vector<std::deque<Token>>::iterator queue = list.begin(); queue < list.end(); queue++)
	{
		// for every token in the queue 		
		for(std::deque<Token>::iterator it=(*queue).begin(); it < (*queue).end(); it++)
		{ 			
			// print the lexeme
			std::cout<< (*it).getLexeme() << " "; 		
		} 	

		std::cout<<std::endl;
	}
}