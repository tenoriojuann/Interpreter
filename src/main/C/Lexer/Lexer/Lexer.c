#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>



/*

CS4380 W01

Concepts of Programming Languages

Professor: Jose M Garrido

Students: Juan E. Tenorio Arzola, Thomas Nguyen, Andrew Shatz

*/




// struct to be returned

struct Token{
	char token[26];
	char lexeme[26];
	bool closed;
};



struct Token nextToken(FILE *fp) {

	// Empty struct that will be used to reset the returnedToken
	static const struct Token Empty;
	struct Token returnedTOKEN;


	// Variables that will hold the cases,
	// some variables will hold numbers and some char arrays

	int state = 1;
	int numBuffer = 0;
	char alphaBuffer[20];
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

			// EOF was reached
			// setting the boolean variable in the struct to true
			// and closing the stream
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

			case ';':
					
					returnedTOKEN = Empty;
					strcpy(returnedTOKEN.token, "semicolon");
					strcpy(returnedTOKEN.lexeme, ";");
					return returnedTOKEN;
		
			case '+':

					returnedTOKEN = Empty;
					strcpy(returnedTOKEN.token, "add_operator");
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
			case '~':

				ch = fgetc(fp);
				state = 9;
				continue;

			case '<':

				ch = fgetc(fp);
				state = 10;
				continue;

			case '>':

				ch = fgetc(fp);
				state = 11;
				continue;

			case '*':

				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "mul_operator");
				strcpy(returnedTOKEN.lexeme, "*");
				return returnedTOKEN;

			case '/':

				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "div_operator");
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

				strcpy(returnedTOKEN.token, "literal_integer");
				
				// integer to char
				sprintf(returnedTOKEN.lexeme, "%d", numBuffer);

				return  returnedTOKEN;
			}
			continue;

			// A Letter/invalid character has been identified

		case 4:

			// Clearing the array

			memset(&alphaBuffer[0], 0, sizeof(alphaBuffer));

			if (isalpha(ch) || ch == '_') {

				strncat(alphaBuffer, &ch,1);
				state = 5;
				ch = fgetc(fp);
			}
			else {


				strncat(alphaBuffer, &ch, 1);

				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "Invalid:");
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

				// Reassignnig the token to be return
				// Just in case that it contains unwanted token/lexeme

				returnedTOKEN = Empty;

				if (strcmp(alphaBuffer, "int") == 0) {
					
					strcpy(returnedTOKEN.token, "keyword");
					strcpy(returnedTOKEN.lexeme, "int");
					
					return returnedTOKEN;

				}

				if (strcmp(alphaBuffer, "print") == 0) {

					strcpy(returnedTOKEN.token, "keyword");
					strcpy(returnedTOKEN.lexeme, "print");

					return returnedTOKEN;

				}
				else if (strcmp(alphaBuffer, "end") == 0) {

					strcpy(returnedTOKEN.token, "keyword");
					strcpy(returnedTOKEN.lexeme, "end");
					
					return returnedTOKEN;
				}
				else if (strcmp(alphaBuffer, "not") == 0) {

					strcpy(returnedTOKEN.token, "keyword");
					strcpy(returnedTOKEN.lexeme, "not");

					return returnedTOKEN;
				}

				else if (strcmp(alphaBuffer, "if") == 0) {

					strcpy(returnedTOKEN.token, "keyword");
					strcpy(returnedTOKEN.lexeme, "if");
					
					return returnedTOKEN;
				}
				else if (strcmp(alphaBuffer, "while") == 0) {

					strcpy(returnedTOKEN.token, "keyword");
					strcpy(returnedTOKEN.lexeme, "while");

					return returnedTOKEN;
				}

				strcpy(returnedTOKEN.token, "id");
				strcpy(returnedTOKEN.lexeme, alphaBuffer);



				return  returnedTOKEN;
			}

			continue;


			// A bool comparison is found or an assignment
		case 6:
			if (ch == '=') {
			

				// Is equal

				ch = fgetc(fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "eq_operator");
				strcpy(returnedTOKEN.lexeme, "==");
				return  returnedTOKEN;
			}
			else {

				// Assignment

				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "assignment_operator");
				strcpy(returnedTOKEN.lexeme, "=");
				return  returnedTOKEN;
			}

			// EIther a comment is found or a subtraction operator
		case 7:
			if (ch == '-') {
				
			
				returnedTOKEN = Empty;

				// Comment

				memset(&alphaBuffer[0], 0, sizeof(alphaBuffer));
				strcpy(alphaBuffer, "--");
				ch = fgetc(fp);

				state = 12;


			}
			else {
				
				// Subtraction


				strcpy(returnedTOKEN.token, "sub_operator");
				strcpy(returnedTOKEN.lexeme, "-");
				return  returnedTOKEN;

			}
			

			continue;

			// End of Line

		case 8:
			if (ch == '\n') {
				state = 1;
			}

			continue;

			// Not Equals

		case 9:

			if (ch == '=') {
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "ne_operator");
				strcpy(returnedTOKEN.lexeme, "~=");
				return  returnedTOKEN;
			}

			ch = fgetc(fp);
			continue;


			// Less than or equal

		case 10:

			if (ch == '=') {
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "le_operator");
				strcpy(returnedTOKEN.lexeme, "<=");
				return  returnedTOKEN;
			}

			else {


				// Less than
				ungetc(ch, fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "lt_operator");
				strcpy(returnedTOKEN.lexeme, "<");
				return  returnedTOKEN;
			}


			// Greater than or equal
		case 11:


			if (ch == '=') {
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "ge_operator");
				strcpy(returnedTOKEN.lexeme, ">=");
				return  returnedTOKEN;
			}

			else {


				// Greater than
				ungetc(ch, fp);
				returnedTOKEN = Empty;
				strcpy(returnedTOKEN.token, "gt_operator");
				strcpy(returnedTOKEN.lexeme, ">");
				return  returnedTOKEN;
			}

		case 12:

			if (ch != '\n') {

				strncat(alphaBuffer, &ch, 1);


				ch = fgetc(fp);
				
			}

			else {
				strcpy(returnedTOKEN.token, "comment_operator");
				strcpy(returnedTOKEN.lexeme, alphaBuffer);
				return  returnedTOKEN;
			}


		}
		
	}
}


int main(int arc, char *filename[]){
	

	FILE *fp;

	// Openning the stream


	// Checking that an argument was passed
	if (arc > 1) {

		fp = fopen(filename[1], "r");
	}
	// If not, ask to input the name of the file or the path to the file
	else {

		printf("Please enter the name of the file if located in this folder\n");
		printf("Else drag the file here\n");
		char file[100];
		scanf("%s",file);

		fp = fopen(file, "r");

	}
	
	
	if (fp == NULL) {
		printf("File not located, check the filename and path\n");
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