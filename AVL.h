#pragma once
#include "AVLInterface.h"
#include "Node.h"

class AVL : public AVLInterface {
public:
	AVL() { root = nullptr;}
	virtual ~AVL() {clear();}
	NodeInterface* getRootNode() const override;
	bool add(int data) override;
	bool remove(int data) override;
	void clear() override;
	//Protected
	Node *root;
	//Private
	void replaceParent(Node* localRoot, Node* oldRoot);
	bool doRemove(Node* localRoot, int data);
};