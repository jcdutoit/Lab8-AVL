#include "AVL.h"
#include "NodeInterface.h"
#include "Node.h"
#include <iostream>

NodeInterface* AVL::getRootNode() const{
    return root;
}

bool AVL::add(int data){
    return doAdd(nullptr, root, data);
}

bool AVL::remove(int data){
    return doRemove(root, data);
}

void AVL::clear(){
    doClear(root);
}

int AVL::getMax(Node* &localNode){
    if(localNode == nullptr){
        cout << "TRYING TO TAKE BALANCE OF NULL PTR" << endl;
    }
    int leftHeight = (localNode->leftChild == nullptr)? 0:localNode->leftChild->height;
    int rightHeight = (localNode->rightChild == nullptr)? 0:localNode->rightChild->height;
    return (leftHeight > rightHeight)? leftHeight + 1:rightHeight + 1;
}

int AVL::getBalance(Node* &localNode){
    if(localNode == nullptr){
        return 0;
    }
    int leftHeight = (localNode->leftChild == nullptr)? 0:localNode->leftChild->height;
    int rightHeight = (localNode->rightChild == nullptr)? 0:localNode->rightChild->height;
    return rightHeight - leftHeight;
}

Node* AVL::rotateLeft(Node* &localRoot) {
    bool replaceRoot = false;
    if(root == localRoot){
        replaceRoot = true;
    }
    Node* temp = localRoot->rightChild;
    localRoot->rightChild = temp->leftChild;
    if(temp->leftChild != nullptr){
       temp->leftChild->parent = localRoot; 
    }
    
    temp->leftChild = localRoot;
    if(localRoot != nullptr){
        localRoot->parent = temp;
    }
    localRoot = temp;
    localRoot->leftChild->height = getMax(localRoot->leftChild);
    localRoot->height = getMax(localRoot);
   
    
    if(replaceRoot){
        root = localRoot;
        localRoot->parent = nullptr;
    }
    return localRoot;
}

Node* AVL::rotateRight(Node* &localRoot) {
    bool replaceRoot = false;
    if(root == localRoot){
        replaceRoot = true;
    }
    Node* temp = localRoot->leftChild;
    localRoot->leftChild = temp->rightChild;
    if(temp->rightChild != nullptr){
        temp->rightChild->parent = localRoot;
    }
    temp->rightChild = localRoot;
    if(localRoot != nullptr){
        localRoot->parent = temp;
    }
    localRoot = temp;
    localRoot->rightChild->height = getMax(localRoot->rightChild);
    localRoot->height = getMax(localRoot);
    if(replaceRoot){
        root = localRoot;
    }
    return localRoot;
}

void AVL::rebalance(Node* &localNode){
    // Left Left Tree
    if(getBalance(localNode) < -1 && (getBalance(localNode->leftChild) == -1 || getBalance(localNode->leftChild) == 0)){
        rotateRight(localNode);
    }
    // Left Right Tree
    else if(getBalance(localNode) < -1 && (getBalance(localNode->leftChild) == 1)){ // || getBalance(localNode->rightChild) == 0)){
        localNode->leftChild = rotateLeft(localNode->leftChild);
        rotateRight(localNode);
        
    }
    // Right Right Tree
    else if(getBalance(localNode) > 1 && (getBalance(localNode->rightChild) == 1 || getBalance(localNode->rightChild) == 0)){
        rotateLeft(localNode);
    }
    // Right Left Tree
    else if(getBalance(localNode) > 1 && (getBalance(localNode->rightChild) == -1)){ //|| getBalance(localNode->leftChild) == 0)){
        cout << "Doing a Right Left rebalance on " << localNode->data << endl;
        Node* rootParent = localNode->parent;
        cout << "rootParent is: " << rootParent->data << endl;
        localNode->rightChild = rotateRight(localNode->rightChild);
        Node* newRoot = rotateLeft(localNode);
        cout << "NewRoot is " << newRoot->data << endl;
        cout << "localNode parent is " << localNode->parent->data << endl;
        localNode->parent->rightChild = newRoot;

    }
    // We are balanced
    else{
        return;
    }
}

bool AVL::doAdd(Node* parentNode, Node* &localRoot, int value){
    if(localRoot == nullptr){
        Node* newNode = new Node(value);
        newNode->parent = parentNode;
        localRoot = newNode;
        if(root == nullptr){
            root = localRoot;
        }
        return true;
    }
    else if(value < localRoot->data){
        bool isAdded = doAdd(localRoot, localRoot->leftChild, value);
        if(isAdded){
            localRoot->height = getMax(localRoot);   
            rebalance(localRoot);
        }
        return isAdded;
    }
    else if(localRoot->data < value){
        bool isAdded = doAdd(localRoot, localRoot->rightChild, value);
        if(isAdded){
            localRoot->height = getMax(localRoot);
            rebalance(localRoot);
        }
        return isAdded;
    }
    else{
        return false;
    }
}

void AVL::replaceParent(Node* &oldRoot, Node* &localRoot){
	if(localRoot->rightChild != nullptr){
		replaceParent(oldRoot, localRoot->rightChild);
	}
	else {
        //cout << "Leftmost root is: " << localRoot->data << endl;
		oldRoot->data = localRoot->data;
		doRemove(oldRoot->leftChild, oldRoot->data);
        //removeRebalance(oldRoot);
        oldRoot->height = getMax(oldRoot);
        cout << "Balance of replaceParent node is " << getBalance(oldRoot) << endl;
        rebalance(oldRoot);
        // oldRoot = localRoot;
		// localRoot = localRoot->leftChild;
	}
}

bool AVL::doRemove(Node* &localRoot, int value){
    if(localRoot == nullptr){
        return false;
    }
    else{
        if(value < localRoot->getData()){
            bool isRemoved = doRemove(localRoot->leftChild, value);
            if(isRemoved){
                localRoot->height = getMax(localRoot);
                rebalance(localRoot);
            }
            return isRemoved;

        }
        else if(value > localRoot->getData()){
            bool isRemoved = doRemove(localRoot->rightChild, value);
            if(isRemoved){
                localRoot->height = getMax(localRoot);
                rebalance(localRoot);
            }
            return isRemoved;
        }
        else {
            Node* oldRoot = localRoot;
            if(localRoot->leftChild == nullptr){
                if(localRoot->rightChild != nullptr){
                    localRoot->rightChild->parent = localRoot->parent;
                }
                localRoot = localRoot->rightChild;
            }
            else if(localRoot->rightChild == nullptr){
                if(localRoot->leftChild != nullptr){
                    localRoot->leftChild->parent = localRoot->parent;
                }
                localRoot = localRoot->leftChild;
            }
            else {
                replaceParent(oldRoot, oldRoot->leftChild);
                return true;
            }
            delete oldRoot;
			oldRoot = nullptr;
            
            return true;
        }
    }
}

void AVL::doClear(Node* &localRoot){
	if(localRoot == nullptr){
		return;
	}
	else{
		doClear(localRoot->leftChild);
		doClear(localRoot->rightChild);
		delete localRoot;
		localRoot = nullptr;
		return;
	}
}