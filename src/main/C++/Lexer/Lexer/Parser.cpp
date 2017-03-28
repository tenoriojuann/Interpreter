#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include "Node.h"
#include <string>
#include <list>
#include <iostream>	
#include <map>



Parser::Parser(std::string filename)
{


}



std::list<Token> Parser::delimited(Token start, Token stop, Token separator, Token (*parser()) ) {

	std::list<Token> a;
	bool first = true;
	skip_punc(start);
	while (!input.eof()) {

		if (is_punc(stop)) break;
		if (first) {
			first = false;
		}
		else {
			skip_punc(separator);
		}
		if (is_punc(stop)) break;
		a.push_back(parser());
	}
}

Node Parser::parse_toplevel() {
	std::list<Node> prog;
	while (!input.eof()) {
		prog.push_back(parse_expression());
		if (!input.eof()) skip_punc(';');
	}

	return  Node("prog", "prog");

}

Node Parser::parse_if() {

	skip_kw("if");
	auto cond = parse_expression();
	if (!is_punc("{")) {
		skip_kw("then");
	}
	auto then = parse_expression();
	Node ret("if", NULL);
	return ret;
}

auto Parser::parse_atom() {
	if (is_punc("(")) {
		input.next();
		auto exp = parse_expression();
		skip_punc(")");
		return exp;
	}

	if (is_punc("{")) return parse_prog();
	if (is_kw("if")) { auto a = parse_if(); return a; }
	if (is_kw("true") || is_kw("false")) return parse_bool();
	if (is_kw("lambda") || is_kw("λ")) {
		input.next();
		return parse_lambda();
	}
	var tok = input.next();
	if (tok.type == "var" || tok.type == "num" || tok.type == "str")
		return tok;
	unexpected();
}