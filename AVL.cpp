#include "AVL.h"
#include "NodeInterface.h"
#include "Node.h"
#include "AVLutil.h"
#include <iostream>
#include <algorithm>

NodeInterface* AVL::getRootNode() const{
    return root;
}

bool AVL::add(int data){
    root = doAdd(root, data);
    return true;
}

bool AVL::remove(int data){
    return doRemove(root, data);
}

void AVL::clear(){
    doClear(root);
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

