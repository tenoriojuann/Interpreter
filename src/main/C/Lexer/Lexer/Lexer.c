#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


struct Token{
	char token[10];
	char lexeme[10];
	bool closed;
};



struct Token nextToken(FILE *fp) {


	static const struct Token Empty;
	struct Token returnedTOKEN;

	int state = 1;
	int numBuffer = 0;
	char alphaBuffer[10];
	alphaBuffer[0] = '\0';
	char ch;
	ch = fgetc(fp);
	bool skipped = false;

	while (true) {


		if (ch == EOF && !skipped) { // EOF

			skipped = true;
		}
		else if (skipped) {

			fclose(fp);
			returnedTOKEN = Empty;
			returnedTOKEN.closed = true;
			return returnedTOKEN;
		}



		switch (state) {

		case 1:

			switch (ch) {
			
			case '(':
				ch = fgetc(fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "LP");
				strcpy(returnedTOKEN.lexeme, "(");
				return returnedTOKEN;
			case ')':
				ch = fgetc(fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "RP");
				strcpy(returnedTOKEN.lexeme, ")");
				return returnedTOKEN;
			case '{':
				ch = fgetc(fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "LB");
				strcpy(returnedTOKEN.lexeme, "{");
				return returnedTOKEN;
			case '}':
				ch = fgetc(fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "RB");
				strcpy(returnedTOKEN.lexeme, "}");
				return returnedTOKEN;
			case ' ':
			case '\n':
			case '\b':
			case '\f':
			case '\r':
			case '\t':
					ch = fgetc(fp); // spaces can be ignored
		
					continue;
			case '.':
					
					ch = fgetc(fp);
					returnedTOKEN = Empty;
					strcpy(returnedTOKEN.token, "PD");
					strcpy(returnedTOKEN.lexeme, ".");
					return returnedTOKEN;
		
			case '+':
					returnedTOKEN = Empty;
					strcpy(returnedTOKEN.token, "SM");
					strcpy(returnedTOKEN.lexeme, "+");
					return returnedTOKEN;

			case '=':
					
				ch = fgetc(fp);
					state = 6;
					continue;
				
			case '-':
				
				ch = fgetc(fp);
					state = 7;
					continue;

			default:
					state = 2;
					continue;

			}


			//  The case for when a number is scanned
		case 2:
			if (isdigit(ch)) {
				numBuffer = 0;
				numBuffer += (ch-'0');

				state = 3;

				
				ch =  fgetc(fp);
			}
			else {
				state = 4;
			}
			continue;

			// Number is found 
		case 3:
			if (isdigit(ch)) {
				numBuffer *= 10;
				numBuffer += atoi(ch);

				
				ch = fgetc(fp);
			}
			else{
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "NUM");
				itoa( numBuffer, returnedTOKEN.lexeme,10);
				return  returnedTOKEN;
			}
			continue;

			// Either a keyword is found or there is an invalid input
		case 4:

			if (isalpha(ch) || ch == '_') {

				memset(&alphaBuffer[0], 0, sizeof(alphaBuffer));
				strncat(alphaBuffer, &ch,1);
				state = 5;
				ch = fgetc(fp);
			}
			else {
				memset(&alphaBuffer[0], 0, sizeof(alphaBuffer));
				strncat(alphaBuffer, &ch, 1);

				
				ch = fgetc(fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "INV");
				strcpy(returnedTOKEN.lexeme, alphaBuffer);

				return   returnedTOKEN;
			}
			continue;

			// Keyword is found or a variable
		case 5:

			if (isalpha(ch) || isdigit(ch) || ch == '_') {
			

				strncat(alphaBuffer, &ch, 1);
				ch = fgetc(fp);
			}
			else {

				
	
				if (strcmp(alphaBuffer, "int") == 0) {
					returnedTOKEN = Empty;
					strcpy(returnedTOKEN.token, "KW");
					strcpy(returnedTOKEN.lexeme, "int");
					
					return returnedTOKEN;

				}
				else if (strcmp(alphaBuffer, "end") == 0) {
					returnedTOKEN = Empty;
					strcpy(returnedTOKEN.token, "KW");
					strcpy(returnedTOKEN.lexeme, "end");

					return returnedTOKEN;
				}
				else if (strcmp(alphaBuffer, "if") == 0) {
					returnedTOKEN = Empty;
					strcpy(returnedTOKEN.token, "KW");
					strcpy(returnedTOKEN.lexeme, "if");

					return returnedTOKEN;
				}
				else if (strcmp(alphaBuffer, "while") == 0) {
					returnedTOKEN = Empty;
					strcpy(returnedTOKEN.token, "KW");
					strcpy(returnedTOKEN.lexeme, "while");

					return returnedTOKEN;
				}

				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "ID");
				strcpy(returnedTOKEN.lexeme, alphaBuffer);

				memset(&alphaBuffer[0], 0, sizeof(alphaBuffer));
				strncat(alphaBuffer, &ch, 1);

				return  returnedTOKEN;
			}

			continue;

			// A bool comparison is found or an assignment
		case 6:
			if (ch == '=') {
			
				ch = fgetc(fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "EQ");
				strcpy(returnedTOKEN.lexeme, "==");
				return  returnedTOKEN;
			}
			else {

				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "ASS");
				strcpy(returnedTOKEN.lexeme, "=");
				return  returnedTOKEN;
			}

			// Found a comment
		case 7:
			if (ch == '-') {
				
				ch = fgetc(fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "CM");
				strcpy(returnedTOKEN.lexeme, "--");
				return  returnedTOKEN;
			}
			
			ch = fgetc(fp);
			continue;
		case 8:
			if (ch == '\n') {
				state = 1;
			}

			continue;
		}
		
	}
}


int main(int arc, char *filename[]){
	
	static const struct Token Empty;
	FILE *fp;
	fp = fopen("C:\\Users\\Tenor\\Desktop\\Sample.in", "r");
	if (fp == NULL) {
		printf("File not created okay, error = %d\n", errno);
		return 1;
	}
	
	FILE *output = fopen("output.txt", "a");


	struct Token out;
	out = nextToken(fp);
	
	while( !out.closed){
		
		fputs(out.token, output);
		fprintf(output, " ");
		fprintf(output, out.lexeme);
		fprintf(output, "\n");
		out = nextToken(fp);
		
	}
	
	
	return 0;
}