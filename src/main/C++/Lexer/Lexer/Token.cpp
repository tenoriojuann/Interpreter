#include "Token.h"
#include <string>





Token::Token() {

}

Token::Token(bool closed) {
	this->closed = closed;
}

Token::Token(std::string token, std::string lexeme) {
	this->lexeme = lexeme;
	this->token = token;
}



Token::Token(std::string token, std::string lexeme, bool closed)
{
	
	this->lexeme = lexeme;
	this->token = token;
	this->closed = closed;

}


Token::~Token()
{

}

void Token::setBool(bool value) {

	closed = value;
}

void Token::setLexeme(std::string value) {

	lexeme = value;

}

void Token::setToken(std::string value) {

	token = value;

}

bool Token::getBool() {

	return closed;
}

std::string Token::getLexeme() {

	return lexeme;
	
}

bool Token::getBool() {

	return closed;
}

