#include "Node.h"

int Node::getData() const{
	return data;
}

Node* Node::getLeftChild() const{
	return leftChild;
}

Node* Node::getRightChild() const{
	return rightChild;
}

void Node::setData(int value){
	data = value;
}

void Node::setLeft(Node *ptr){
	leftChild = ptr;
}

void Node::setRight(Node *ptr){
	rightChild = ptr;
}

int Node::getHeight(){
	return height;
}

void Node::setHeight(int newHeight){
	height = newHeight;
}