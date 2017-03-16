#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include <string>
#include <iostream>	
#include <map>



Parser::Parser(std::string filename)
{
	FALSE["type"] = "bool";
	FALSE["value"] = false;

}

std::string Parser::delimited() {


}
