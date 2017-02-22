#include <stdio.h>
#include <ctype.h>


struct Token{
	char token[3] = NULL;
	char lexeme[2] = NULL;
}

Token nextToken(File *fp){
	
	
	static const struct Token Empty;
	struct Token returnedTOKEN;
	
	int state = 1;
        int numBuffer = 0;
        char ch *alphaBuffer[256] = "";
        boolean skipped = false;
		
        while(true){

            if(ch == '0' && !skipped) { // EOF

                skipped = true;
            }
            else if(skipped) {
                
				fclose(fp);
				
                return NULL;
            }



            switch (state){

                case 1:
                    switch (ch){
                        case ' ':
                            ch = fgetc(fp); // spaces can be ignored
                            continue;
                        case '.':
                            ch = fgetc(fp);
							returnedToken = Empty; 
							strcpy(returnedTOKEN.token, "PD");
							strcpy(returnedTOKEN.lexeme, ".");
                            return returnedTOKEN;
                        case '+':
							returnedToken = Empty; 
							strcpy(returnedTOKEN.token, "SM");
							strcpy(returnedTOKEN.lexeme, "+");
                            return returnedTOKEN;
                        case'=': 
                            ch=fgetc(fp);
                            state=6;
                            continue;
                        case '-':
                            ch = fgetc(fp);
                            state = 7;
                            continue;
                        default:
                            state =2;
                            continue;

                    }


                //  The case for when a number is scanned
                case 2:
                    if(isdigit(ch)){
                        numBuffer = 0;
                        numBuffer  += ch-'0';

                        state = 3;

                        ch = fgetc(fp);
                    }
                    else{
                        state = 4;
                    }
                    continue;

                // Number is found by itself
                case 3:
                    if(isdigit(ch)){
                        numBuffer *= 10;
                        numBuffer += (ch-'0');

                        ch = fgetc(fp);
                    }
                    else{
						returnedTOKEN = Empty; 
						strcpy(returnedTOKEN.token, "NUM");
						strcpy(returnedTOKEN.lexeme, "" + numBuffer);
                        return  returnedTOKEN;
                    }
                    continue;

                // Either a keyword is found or there is an invalid input
                case 4:

                    if(isalpha(ch) || ch == '_') {

                        alphaBuffer = "";
                        alphaBuffer += ch;
                        state = 5;
                        ch = fgetc(fp);
                    }
                    else{
                        alphaBuffer = "";
                        alphaBuffer += ch;

                        ch = fgetc(fp);
						returnedToken = Empty; 
						strcpy(returnedTOKEN.token, "INV");
						strcpy(returnedTOKEN.lexeme, ""+alphaBuffer);
                        return   returnedTOKEN;
                    }
                    continue;

                // Keyword is found or a variable
                case 5:

                    if(isalpha(ch) || isdigit(ch) || ch == '_'){
                        alphaBuffer += ch;
                        ch = fgetc(fp);
                    }
                    else{
                        if(while(strcmp(alphaBuffer, "int")) != 0) {
							returnedToken = Empty; 
							strcpy(returnedTOKEN.token, "KW");
							strcpy(returnedTOKEN.lexeme, alphaBuffer);
							return returnedTOKEN                        

						}

						returnedToken = Empty; 
						strcpy(returnedTOKEN.token, "ID");
						trcpy(returnedTOKEN.lexeme, alphaBuffer);
                        return  returnedTOKEN;
                    }

                    continue;

                // A boolean comparison is found or an assignment
                case 6:
                    if(ch == '='){
                        ch = fgetc(fp);
						returnedToken = Empty; 
						strcpy(returnedTOKEN.token, "EQ");
						strcpy(returnedTOKEN.lexeme, "==");
                        return  returnedTOKEN;
                    }
                    else {
						returnedToken = Empty; 
						strcpy(returnedTOKEN.token, "ASS");
						strcpy(returnedTOKEN.lexeme, "=");
                        return  returnedTOKEN;
                    }

                // Found a comment
                case 7:
                    if(ch == '-'){
                        ch = fgetc(fp);
						returnedToken = Empty; 
						strcpy(returnedTOKEN.token, "CM");
						strcpy(returnedTOKEN.lexeme, "--");
                        return  returnedTOKEN;
                    }
                    ch = fgetc(fp);
                    continue;
                case 8:
                    if(ch == '\n'){
                        state =1;
                    }
                    ch = fgetc(fp);
                    continue;

            }
        }
    }
	
	
}


int main(char *filename[]){
	
	
	File *fp = fopen(const char * filename, const char * "r");
	
	File *output = fopen("output.txt", "a");
	
	while( (struct Token out = nextToken(fp)) != NULL){
		
		fputs(out.token, output);
		fputc(" ", output);
		fputs(out.lexeme, output);
		
	}
	
	
	return 0;
}