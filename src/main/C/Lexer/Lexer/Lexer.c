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


	// Variables that will hold the cases,
	// some variables will hold numbers and some char arrays

	int state = 1;
	int numBuffer = 0;
	char alphaBuffer[10];
	alphaBuffer[0] = '\0';
	char ch;

	// Getting a single char from the stream
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


		// Finding single tokens or spaces.

		case 1:

			switch (ch) {
			
			case '(':
				
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "LP");
				strcpy(returnedTOKEN.lexeme, "(");
				return returnedTOKEN;
			case ')':
				
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "RP");
				strcpy(returnedTOKEN.lexeme, ")");
				return returnedTOKEN;
			case '{':
				
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "LB");
				strcpy(returnedTOKEN.lexeme, "{");
				return returnedTOKEN;
			case '}':
				
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

			case '*':

				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "MUL");
				strcpy(returnedTOKEN.lexeme, "*");
				return returnedTOKEN;

			case '/':

				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "DIV");
				strcpy(returnedTOKEN.lexeme, "/");
				return returnedTOKEN;

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
				numBuffer += (ch - '0');

				
				ch = fgetc(fp);
			}
			else{
				returnedTOKEN = Empty;

				strcpy(returnedTOKEN.token, "NUM");
				
				// integer to char
				sprintf(returnedTOKEN.lexeme, "%d", numBuffer);

				return  returnedTOKEN;
			}
			continue;

			// A Letter/invalid character has been identified

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

				// The ID/Keyword has been identified 
				// We need to put the last character taken
				// back in the stream
				// and reset the state

				state = 1;
				ungetc(ch, fp);

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



				return  returnedTOKEN;
			}

			continue;

			// A bool comparison is found or an assignment
		case 6:
			if (ch == '=') {
			
				ch = fgetc(fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "IEQ");
				strcpy(returnedTOKEN.lexeme, "==");
				return  returnedTOKEN;
			}
			else {

				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "EQ");
				strcpy(returnedTOKEN.lexeme, "=");
				return  returnedTOKEN;
			}

			// EIther a comment is found or a subtraction operator
		case 7:
			if (ch == '-') {
				
			
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "CM");
				strcpy(returnedTOKEN.lexeme, "--");
				return  returnedTOKEN;
			}
			else {
				
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "SUB");
				strcpy(returnedTOKEN.lexeme, "-");
				return  returnedTOKEN;

			}
			
			ch = fgetc(fp);
			continue;

			// End of Line

		case 8:
			if (ch == '\n') {
				state = 1;
			}

			continue;
		}
		
	}
}


int main(int arc, char *filename[]){
	

	FILE *fp;

	// Openning the stream

	if ((sizeof(filename) / sizeof(filename[0])) > 1) {
		fp = fopen(filename[1], "r");
	}
	else {

		printf("Please enter the name of the file if located in this folder\n");
		printf("Else drag the file here\n ");
		char file[100];
		scanf("%s",file);

		fp = fopen(file, "r");

	}
	
	
	if (fp == NULL) {
		printf("File not located\n");
		return 1;
	}
	
	// Creating the output file
	FILE *output = fopen("output.txt", "a");


	struct Token out;
	out = nextToken(fp);
	
	// Looping until the stream reaches EOF 
	// That will set the 'closed' variable in 
	// the struct to true

	while( !out.closed){
		
		fputs(out.token, output);
		fprintf(output, " ");
		fprintf(output, "%s",out.lexeme);
		fprintf(output, "\n");
		out = nextToken(fp);
		
	}
	
	
	return 0;
}