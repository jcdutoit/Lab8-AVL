#include "AVL.h"
#include "NodeInterface.h"
#include "Node.h"
#include "AVLutil.h"
#include <iostream>

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



bool AVL::doAdd(Node* localRoot, int value){
    if(localRoot == nullptr){
        Node* newNode = new Node(value);
        localRoot = newNode;
        if(root == nullptr){
            root = localRoot;
        }
        return true;
    }
    else if(value < localRoot->data){
        bool isAdded = doAdd(localRoot->getLeftChild(), value);
        if(isAdded){
            localRoot->height = getMaxHeight(localRoot);   
            rebalance(localRoot);
        }
        return isAdded;
    }
    else if(localRoot->data < value){
        bool isAdded = doAdd(localRoot->getRightChild(), value);
        if(isAdded){
            localRoot->height = getMaxHeight(localRoot);
            rebalance(localRoot);
        }
        return isAdded;
    }
    else{
        return false;
    }
}

void AVL::replaceParent(Node* oldRoot, Node* localRoot){
	if(localRoot->rightChild != nullptr){
		replaceParent(oldRoot, localRoot->rightChild);
	}
	else {
        //cout << "Leftmost root is: " << localRoot->data << endl;
		oldRoot->data = localRoot->data;
		doRemove(oldRoot->leftChild, oldRoot->data);
        oldRoot->height = getMaxHeight(oldRoot);
        cout << "Balance of replaceParent node is " << getBalance(oldRoot) << endl;
        //rebalance(oldRoot);
        // oldRoot = localRoot;
		// localRoot = localRoot->leftChild;
	}
}

bool AVL::doRemove(Node* localRoot, int value){
    if(localRoot == nullptr){
        return false;
    }
    else{
        if(value < localRoot->getData()){
            bool isRemoved = doRemove(localRoot->leftChild, value);
            if(isRemoved){
                localRoot->height = getMaxHeight(localRoot);
                //rebalance(localRoot);
            }
            return isRemoved;

        }
        else if(value > localRoot->getData()){
            bool isRemoved = doRemove(localRoot->rightChild, value);
            if(isRemoved){
                localRoot->height = getMaxHeight(localRoot);
                //rebalance(localRoot);
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
                return true;
            }
            delete oldRoot;
			oldRoot = nullptr;
            
            return true;
        }
    }
}

