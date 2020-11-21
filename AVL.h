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
protected:
	Node *root;

};