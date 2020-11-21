#include "Node.h"
#include <string>

int GetHeight(const Node* localNode);
int getMaxHeight(const Node* localNode);
void rebalance(Node* localNode);
Node* rotateRight(Node* localRoot);
Node* rotateLeft(Node* localRoot);
int getBalance(const Node* localNode);
void checkBalance(const Node* localNode);
void doClear(Node* localRoot);
Node * doAdd(Node* localRoot, int value);
Node* doRemove(Node* localRoot, int value);
string treeString(NodeInterface* node);