#include "Token.h"
#include "Parser.h"
#include "Lexer.h"
#include <string>
#include <iostream>
#include <fstream>
int main(int arc, char* filename[] ) {


	if (arc > 1) {
		Parser par(filename[1]);
		par.grabLineCode();

		par.printT();
	}

	else {
		Parser par("Sample.lua");
		par.grabLineCode();

		par.printT();
	}

	int exit;
	std::cin >> exit;
	return 0;
}