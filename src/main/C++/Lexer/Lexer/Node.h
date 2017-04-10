#pragma once
#include <string>
#include <map>
class Node{

public:
	Node::Node(std::string type, std::string value);
	void setLeft(Node left);
	void setRight(Node left);
	std::pair<std::string, std::string> type;
	std::pair<std::string, std::string> value;
	Node* leftChild;
	Node* rightChild;
};