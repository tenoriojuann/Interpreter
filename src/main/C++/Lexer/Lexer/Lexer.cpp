// Lexer.cpp : Defines the entry point for the console application.
//

#include "Lexer.h"
#include "Token.h"
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

Lexer::Lexer(std::string filename) {
	
	Analyze(filename);
}

Token Lexer::nextToken(std::ifstream& fp) {
	
	int state = 1;
	int numBuffer = 0;
	std::string alphaBuffer;
	char ch;
	ch = fp.get();
	bool skipped = false;

	while (true)
	{

		if (ch == EOF && !skipped) {

			skipped = true;
		}
		else if (skipped) {

			fp.close();

			return Token(true);

		}


		switch (state)
		{

		case 1:

			switch (ch)
			{
			case '(':

				return Token("LP", "(");

			case ')':

				return Token("RP", ")");

			case '{':

				return Token("LB", "{");

			case '}':

				return Token("RP", "}");

			case ' ':
			case '\n':
			case '\b':
			case '\f':
			case '\r':
			case '\t':
				ch = fp.get(); // spaces can be ignored

				continue;

			case '.':

				return Token("PD", ".");

			case '+':

				return Token("SM", "+");

			case '=':

				ch = fp.get();
				state = 6;
				continue;

			case '-':

				ch = fp.get();
				state = 7;
				continue;

			case '*':

				return Token("MUL", "*");

			case '/':

				return Token("DIV", "/");

			default:
				state = 2;
				continue;
			}

		case 2:

			if (isdigit(ch)) {

				numBuffer = 0;
				numBuffer += static_cast<int>(ch);
				state = 3;
				ch = fp.get();
			}
			else {
				state = 4;
			}

			continue;

		case 3:

			if (isdigit(ch)) {

				numBuffer *= 10;
				numBuffer += static_cast<int>(ch);
				ch = fp.get();
			}

			else {

				return Token("NUM", std::to_string(numBuffer));

			}

			continue;


		case 4:

			if (isalpha(ch) || ch == '_') {

				alphaBuffer = "";
				alphaBuffer += ch;
				state = 5;
				ch = fp.get();
			}

			else {
				alphaBuffer = "";
				alphaBuffer += ch;
				return Token("INVALID: ", alphaBuffer);
			}

			continue;

		case 5:

			if (isalpha(ch) || isdigit(ch) || ch == '_') {

				alphaBuffer += ch;
				ch = fp.get();
			}

			else {

				state = 1;

				fp.unget();

				if (alphaBuffer == "int" || alphaBuffer == "end" || alphaBuffer == "end" ||
					alphaBuffer == "if" || alphaBuffer == "while" || alphaBuffer == "not") {
					return Token("KW", alphaBuffer);
				}

				return Token("ID", alphaBuffer);
			}

			continue;

		case 6:

			if (ch == '=') {
				
				return Token("IEQ", "==");
			}

			else {
				return Token("EQ", "=");
			}

		case 7:

			if (ch == '-') {
				alphaBuffer = "--";
				ch = fp.get();
				state = 8;
				
			}

			else {
				return Token("SUB", "-");
			}
			continue;

		case 8:

			if (ch != '\n') {
				
				alphaBuffer += ch;
				
				ch = fp.get();
			}
			else {
				return Token("COM", alphaBuffer);
			}

			continue;

		case 9:

			if (ch == '\n') {
				state = 1;
			}
			continue;

		}

	}

}

void Lexer::Analyze(std::string filename)
{

	std::ifstream fp;
	fp.open(filename);

	if (fp.fail()) {
		std::cout << ("--Could not find file") << std::endl;
		std::cout << ("--Check the path") << std::endl;

		return exit(1);
	}

	std::ofstream output("output.txt");
	
	Token out(false);
	out = nextToken(fp);
	while (fp) {

		output << out.getToken();
		output << " ";
		output << out.getLexeme();
		output << std::endl;
		out = nextToken(fp);


	}

	exit(1);

}
