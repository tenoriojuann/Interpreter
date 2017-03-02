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


Lexer::Lexer(FILE *fp, char *filename[]) {
	this->fp = fp;
	Analyze(filename);
}

Token Lexer::nextToken() {
	
	int state = 1;
	int numBuffer = 0;
	std::string alphaBuffer;
	char ch;
	ch = fgetc(fp);
	bool skipped = false;

	while (true)
	{

		if (ch == EOF && !skipped) {

			skipped = true;
		}
		else if (skipped) {

			fclose(fp);

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
				ch = fgetc(fp); // spaces can be ignored

				continue;

			case '.':

				return Token("PD", ".");

			case '+':

				return Token("SM", "+");

			case '=':

				ch = fgetc(fp);
				state = 6;
				continue;

			case '-':

				ch = fgetc(fp);
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
				ch = fgetc(fp);
			}
			else {
				state = 4;
			}

			continue;

		case 3:

			if (isdigit(ch)) {

				numBuffer *= 10;
				numBuffer += static_cast<int>(ch);
				ch = fgetc(fp);
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
				ch = fgetc(fp);
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
				ch = fgetc(fp);
			}

			else {

				state = 1;

				ungetc(ch, fp);

				if (alphaBuffer == "int" || alphaBuffer == "end" || alphaBuffer == "end" ||
					alphaBuffer == "if" || alphaBuffer == "while") {
					return Token("KW", alphaBuffer);
				}

				return Token("ID", alphaBuffer);
			}

			continue;

		case 6:

			if (ch == '=') {
				ch = fgetc(fp);
				return Token("IEQ", "==");
			}

			else {
				return Token("EQ", "=");
			}

		case 7:

			if (ch == '-') {
				ch = fgetc(fp);
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

	fp = fopen(filename[1], "r");

	if (fp == NULL) {
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
