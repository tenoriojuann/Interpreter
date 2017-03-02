// Lexer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Token.h"
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
class Lexer {

	Token nextToken(FILE *fp) {

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
					
					return Token("LP","(");

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


				
			}

		}

	}


};
