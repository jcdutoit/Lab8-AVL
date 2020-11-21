#include "AVLutil.h"
#include <iostream>
#include <queue>
#include <sstream>

int GetHeight(const Node* localNode) {
    if(localNode==nullptr) {
        return 0;
    }
    return localNode->getHeight();
}

int getMaxHeight(const Node* localNode){
    if(localNode == nullptr){
        cout << "TRYING TO TAKE HEIGHT OF NULL PTR" << endl;
        return 0;
    }
    return localNode->getHeight();
    // int leftHeight = (localNode->getLeftChild() == nullptr)? 0:localNode->getLeftChild()->getHeight();
    // int rightHeight = (localNode->getRightChild()== nullptr)? 0:localNode->getRightChild()->getHeight();
    // return (leftHeight > rightHeight)? leftHeight + 1:rightHeight + 1;
}

int getBalance(const Node* localNode){
    if(localNode == nullptr){
        return 0;
    }
    int leftHeight = (localNode->getLeftChild() == nullptr)? 0:localNode->getLeftChild()->getHeight();
    int rightHeight = (localNode->getRightChild() == nullptr)? 0:localNode->getRightChild()->getHeight();
    return rightHeight - leftHeight;
}

Node* rotateLeft(Node* localRoot) {
    cout << "Rotating left on " << localRoot->getData()  << endl;
    Node* temp = localRoot->getRightChild();
    localRoot->setRight(temp->getLeftChild()); 
    temp->setRight(localRoot);
    localRoot = temp;
    
    localRoot->getLeftChild()->setHeight(getMaxHeight(localRoot->getLeftChild()));
    localRoot->setHeight(getMaxHeight(localRoot));
    return localRoot;
}

Node* rotateRight(Node* localRoot) {
    cout << "Rotating right on " << localRoot->getData() << endl;
    Node* temp = localRoot->getLeftChild();
    localRoot->setLeft(temp->getRightChild());
    temp->setRight(localRoot);
    localRoot = temp;
    localRoot->getRightChild()->setHeight(getMaxHeight(localRoot->getRightChild()));
    localRoot->setHeight(getMaxHeight(localRoot));
    return localRoot;
}

void rebalance(Node* localNode){
    // Left Left Tree
    
    if(getBalance(localNode) < -1 && (getBalance(localNode->getLeftChild()) == -1 || getBalance(localNode->getLeftChild()) == 0)){
        cout << "Left Left tree" << endl;
        rotateRight(localNode);
    }
    // Left Right Tree
    
    else if(getBalance(localNode) < -1 && (getBalance(localNode->getLeftChild()) == 1)){ // || getBalance(localNode->rightChild) == 0)){
        cout << "Left Right tree" << endl;
        localNode->setLeft(rotateLeft(localNode->getLeftChild()));
        rotateRight(localNode);
        
    }
    // Right Right Tree
    else if(getBalance(localNode) > 1 && (getBalance(localNode->getRightChild()) == 1 || getBalance(localNode->getRightChild()) == 0)){
        cout << "Right Right tree" << endl;
        rotateLeft(localNode);
    }
    // Right Left Tree
    else if(getBalance(localNode) > 1 && (getBalance(localNode->getRightChild()) == -1)){ //|| getBalance(localNode->getLeftChild()) == 0)){
        cout << "Right Left tree" << endl;
        localNode->setRight(localNode->getRightChild());
        rotateLeft(localNode);
    }
    // We are balanced
    else{
        return;
    }
}

void doClear(Node* localRoot){
	if(localRoot == nullptr){
		return;
	}
	else{
		doClear(localRoot->getLeftChild());
		doClear(localRoot->getRightChild());
		delete localRoot;
		localRoot = nullptr;
		return;
	}
}


void checkBalance(const Node* localNode){
    // Left Left Tree
    
    if(getBalance(localNode) < -1 && (getBalance(localNode->getLeftChild()) == -1 || getBalance(localNode->getLeftChild()) == 0)){
        cout << "Left Left tree" << endl;
    }
    // Left Right Tree
    
    else if(getBalance(localNode) < -1 && (getBalance(localNode->getLeftChild()) == 1)){ // || getBalance(localNode->rightChild) == 0)){
        cout << "Left Right tree" << endl;
        
    }
    // Right Right Tree
    else if(getBalance(localNode) > 1 && (getBalance(localNode->getRightChild()) == 1 || getBalance(localNode->getRightChild()) == 0)){
        cout << "Right Right tree" << endl;
    }
    // Right Left Tree
    else if(getBalance(localNode) > 1 && (getBalance(localNode->getRightChild()) == -1)){ //|| getBalance(localNode->leftChild) == 0)){
        cout << "Right Left tree" << endl;
    }
    // We are balanced
    else{
        return;
    }
}

Node * doAdd(Node* localRoot, int value){
    if(localRoot == nullptr){
        return new Node(value);
    }
    else if(value < localRoot->data){
        localRoot->leftChild = doAdd(localRoot->leftChild, value);
    }
    else if(localRoot->data < value){
        localRoot->rightChild = doAdd(localRoot->rightChild, value);
    }
    else{
        return localRoot;
    }
    localRoot->height = 1 + std::max(GetHeight(localRoot->leftChild), GetHeight(localRoot->rightChild));
    return localRoot;
}

Node * minValueNode(Node* node) {  
    Node* current = node;  
    while (current->leftChild != nullptr)  
        current = current->leftChild;  
    return current;  
} 

Node* doRemove(Node* localRoot, int value){
    if(localRoot == nullptr){
        return localRoot;
    }
    if(value < localRoot->data){
        localRoot->leftChild = doRemove(localRoot->leftChild, value);
    }
    else if(value > localRoot->data){
        localRoot->rightChild = doRemove(localRoot->rightChild, value);
    }
    else {
        if(localRoot->leftChild == nullptr || localRoot->rightChild == nullptr) {
            Node *temp = (localRoot->leftChild == nullptr) ?
                         localRoot->rightChild :  
                         localRoot->leftChild; 
            if (temp == nullptr) {  
                temp = localRoot;  
                localRoot = nullptr;  
            }  
            else {  
                *localRoot = *temp; 
            }
            free(temp); 
        }
        else {
            Node* temp = minValueNode(localRoot->rightChild);
            localRoot->data = temp->data;   
            localRoot->rightChild = doRemove(localRoot->rightChild,  
                                     temp->data); 
        }
    }
    if (localRoot == NULL) { 
        return localRoot;  
    }
  
    localRoot->height = 1 + std::max(GetHeight(localRoot->leftChild),  
                           GetHeight(localRoot->rightChild));  

    return localRoot;
}

string treeString(NodeInterface* node) {
    //cout << "Printing tree: " << endl;
    queue<NodeInterface*> readQ; // used to read in the levels of the tree, contains Node*
    stringstream nodeReader_ss; // used to store the values of the nodes and the level-order sequence
    int depth = 0; // the depth of a node on the tree

    if (node == NULL) {
        return "Tree is empty\n";
    }

    readQ.push(node); // push the root node of the tree into the queue

    while (!readQ.empty()) { // as long as the queue has a remaining node:
        // cout << "Printing nodes" << endl;
        int i = readQ.size(); // store the number of nodes on this level of the tree
        nodeReader_ss << depth << ":  ";
        for (; i > 0; i--) { // for each node on this level,
            NodeInterface* nextNode = readQ.front(); // store the next node in the queue
            nodeReader_ss << nextNode->getData() << " "; // store the data from the node into the ss
            if (nextNode->getLeftChild() != NULL) { // if there is a left child, push the left child into the queue
                readQ.push(nextNode->getLeftChild());
            }
            if (nextNode->getRightChild() != NULL) { // if there is a right child, push the left child into the queue
                readQ.push(nextNode->getRightChild());
            }
            readQ.pop(); // pop the node off of the queue, leaving its children in the queue
        }
        nodeReader_ss << "\n"; // push an endl into the ss to distinguish levels
        depth++;
    }

    return nodeReader_ss.str();

}
