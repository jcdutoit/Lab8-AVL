#pragma once
#include "AVLInterface.h"
#include "Node.h"

class AVL : public AVLInterface {
public:
	AVL() { root = nullptr;}
	virtual ~AVL() {clear();}
	NodeInterface * getRootNode() const;
	bool add(int data);
	bool remove(int data);
	void clear();
protected:
	Node *root;
private:
	bool doAdd(Node* &localRoot, int data);
	void replaceParent(Node* &localRoot, Node* &oldRoot);
	bool doRemove(Node* &localRoot, int data);
	void doClear(Node* &localRoot);
    void rotateRight(Node* &localRoot);
    void rotateLeft(Node* &localRoot);
    void rebalance(Node* &localNode);
	int getBalance(Node* &localNode);
    int getMax(Node* &localNode);
};