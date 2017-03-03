// Lexer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Lexer.h"
#include "Token.h"
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>


Lexer::Lexer(char *filename[]) {
	fp.open(filename[1]);
	Analyze(filename);
}

Token Lexer::nextToken() {
	
	int state = 1;
	int numBuffer = 0;
	std::string alphaBuffer;
	char ch;
	fp >> ch;
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
				fp >> ch; // spaces can be ignored

				continue;

			case '.':

				return Token("PD", ".");

			case '+':

				return Token("SM", "+");

			case '=':

				fp >> ch;
				state = 6;
				continue;

			case '-':

				fp >> ch;
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
				fp >> ch;
			}
			else {
				state = 4;
			}

			continue;

		case 3:

			if (isdigit(ch)) {

				numBuffer *= 10;
				numBuffer += static_cast<int>(ch);
				fp >> ch;
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
				fp >> ch;
			}

			else {
				alphaBuffer = "";
				alphaBuffer += ch;
				return Token("INV", alphaBuffer);
			}

			continue;

		case 5:

			if (isalpha(ch) || isdigit(ch) || ch == '_') {

				alphaBuffer += ch;
				fp >> ch;
			}

			else {

				state = 1;

				fp.putback(ch);

				if (alphaBuffer == "int" || alphaBuffer == "end" || alphaBuffer == "end" ||
					alphaBuffer == "if" || alphaBuffer == "while") {
					return Token("KW", alphaBuffer);
				}

				return Token("ID", alphaBuffer);
			}

			continue;

		case 6:

			if (ch == '=') {
				fp >> ch;
				return Token("IEQ", "==");
			}

			else {
				return Token("EQ", "=");
			}

		case 7:

			if (ch == '-') {
				fp >> ch;
				return Token("COM", "--");
			}

			else {
				return Token("SUB", "-");
			}

		case 8:

			if (ch == '\n') {
				state = 1;
			}
			continue;

		}

	}

}

void Lexer::Analyze(char *filename[])
{


	if (fp.fail()) {
		std::cout << ("Could not find file") << std::endl;

		return exit(1);
	}

	std::ofstream output("output.txt");

	Token out;

	while (!out.getBool()) {

		output << out.getToken();
		output << " ";
		output << out.getLexeme();
		output << std::endl;

	}

}
