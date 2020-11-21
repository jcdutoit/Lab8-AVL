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
    root = doRemove(root, data);
    return true;
}

void AVL::clear(){
    doClear(root);
}

// void AVL::replaceParent(Node* oldRoot, Node* localRoot){
// 	if(localRoot->rightChild != nullptr){
// 		replaceParent(oldRoot, localRoot->rightChild);
// 	}
// 	else {
//         //cout << "Leftmost root is: " << localRoot->data << endl;
// 		oldRoot->data = localRoot->data;
// 		doRemove(oldRoot->leftChild, oldRoot->data);
//         oldRoot->height = getMaxHeight(oldRoot);
//         cout << "Balance of replaceParent node is " << getBalance(oldRoot) << endl;
//         //rebalance(oldRoot);
//         // oldRoot = localRoot;
// 		// localRoot = localRoot->leftChild;
// 	}
// }



