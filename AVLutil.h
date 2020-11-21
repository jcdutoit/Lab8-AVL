#include "Node.h"
#include <string>

int getMaxHeight(const Node* localNode);
void rebalance(Node* localNode);
Node* rotateRight(Node* localRoot);
Node* rotateLeft(Node* localRoot);
int getBalance(const Node* localNode);
void checkBalance(const Node* localNode);
void doClear(Node* localRoot);
string treeString(NodeInterface* node);