#include "AVL.h"
#include "NodeInterface.h"
#include "Node.h"

NodeInterface* AVL::getRootNode() const{
    return root;
}

bool AVL::add(int data){
    return doAdd(root, data);
}

bool AVL::remove(int data){
    return doRemove(root, data);
}

void AVL::clear(){
    doClear(root);
}

int AVL::getMax(Node* &localNode){
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

void AVL::rotateLeft(Node* &localRoot) {
    bool replaceRoot = false;
    if(root == localRoot){
        replaceRoot = true;
    }
    Node* temp = localRoot->rightChild;
    localRoot->rightChild = temp->leftChild;
    temp->leftChild = localRoot;
    localRoot = temp;
    localRoot->leftChild->height = getMax(localRoot->rightChild);
    localRoot->height = getMax(localRoot);
    if(replaceRoot){
        root = localRoot;
    }
}

void AVL::rotateRight(Node* &localRoot) {
    bool replaceRoot = false;
    if(root == localRoot){
        replaceRoot = true;
    }
    Node* temp = localRoot->leftChild;
    localRoot->leftChild = temp->rightChild;
    temp->rightChild = localRoot;
    localRoot = temp;
    localRoot->rightChild->height = getMax(localRoot->rightChild);
    localRoot->height = getMax(localRoot);
    if(replaceRoot){
        root = localRoot;
    }
}

void AVL::rebalance(Node* &localNode){
    // Left Left Tree
    if(getBalance(localNode) < -1 && getBalance(localNode->leftChild) == -1){
        rotateRight(localNode);
    }
    // Left Right Tree
    else if(getBalance(localNode) < -1 && getBalance(localNode->rightChild) == 1){
        rotateLeft(localNode->leftChild);
        rotateRight(localNode);
    }
    // Right Right Tree
    else if(getBalance(localNode) > 1 && getBalance(localNode->rightChild) == 1){
        rotateLeft(localNode);
    }
    // Right Left Tree
    else if(getBalance(localNode) > 1 && getBalance(localNode->rightChild) == -1){
        rotateRight(localNode->leftChild);
        rotateLeft(localNode->rightChild);
    }
    // We are balanced
    else{
        return;
    }
}

bool AVL::doAdd(Node* &localRoot, int value){
    if(localRoot == nullptr){
        Node* newNode = new Node(value);
        localRoot = newNode;
        if(root == nullptr){
            root = localRoot;
        }
        return true;
    }
    else if(value < localRoot->data){
        bool isAdded = doAdd(localRoot->leftChild, value);
        if(isAdded){
            localRoot->height = getMax(localRoot);   
            rebalance(localRoot);
        }
        return isAdded;
    }
    else if(localRoot->data < value){
        bool isAdded = doAdd(localRoot->rightChild, value);
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
		oldRoot->data = localRoot->data;
		oldRoot = localRoot;
		localRoot = localRoot->leftChild;
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
                localRoot = localRoot->rightChild;
            }
            else if(localRoot->rightChild == nullptr){
                localRoot = localRoot->leftChild;
            }

            else {
                replaceParent(oldRoot, oldRoot->leftChild);
            }
            delete oldRoot;
			oldRoot = nullptr;
            // localRoot->height = getMax(localRoot);
            // rebalance(localRoot);
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