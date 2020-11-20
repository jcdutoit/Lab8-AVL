#pragma once
#include "NodeInterface.h"
using namespace std;

class Node : public NodeInterface{
	friend class AVL;
public:
	Node(int value) {data = value; parent = nullptr; leftChild = nullptr; rightChild = nullptr; height = 1;}
	~Node() {}
	int getData() const;
	int getHeight();
	Node* getLeftChild() const;
	Node* getRightChild() const;
	void setData(int value);
	void setLeft(Node *ptr);
	void setRight(Node *ptr);
protected:
	int height;
	Node* parent;
	Node* leftChild;
	Node* rightChild;
	int data;
};
