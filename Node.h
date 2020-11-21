#pragma once
#include "NodeInterface.h"
using namespace std;

class Node : public NodeInterface{
	friend class AVL;
public:
	Node(int value) {data = value; leftChild = nullptr; rightChild = nullptr; height = 1;}
	~Node() {}
	int getData() const override;
	int getHeight() const override;
	Node* getLeftChild() const override;
	Node* getRightChild() const override;
	void setData(int value);
	void setLeft(Node *ptr);
	void setRight(Node *ptr);
	void setHeight(int height);
protected:
	int height;
	Node* leftChild;
	Node* rightChild;
	int data;
};
