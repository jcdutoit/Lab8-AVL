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
    if(checkValue(root, data)){
        return false;
    }
    root = doAdd(root, data);
    //cout << treeString(root) << endl;
    return true;
}

bool AVL::remove(int data){
    if(!checkValue(root, data)){
        return false;
    }
    //cout << "Removing " << data << endl;
    root = doRemove(root, data);
    //cout << treeString(root) << endl;
    return true;
}

void AVL::clear(){
    doClear(root);
}




