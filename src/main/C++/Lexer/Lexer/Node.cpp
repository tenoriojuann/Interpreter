#include "Node.h"
#include "Lexer.h"
#include "Token.h"


Node::Node(std::string type, std::string value)
{
	this->type = (std::make_pair("type", type));
	this->value = (std::make_pair("value", value));
}

Node::setLeft(Node left) {
	leftChild.insert("left", left);
}
