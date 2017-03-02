#pragma once
#include <string>
class Token
{
public:

	Token();
	Token(bool closed);
	Token(std::string token, std::string lexeme);
	Token(std::string lexeme, std::string token, bool closed);
	~Token();
	void setBool(bool value);
	void setLexeme(std::string value);
	void setToken(std::string value);
	bool getBool();
	std::string getLexeme();
	std::string getToken();


private:
	std::string lexeme;
	std::string token;
	bool closed;

};

