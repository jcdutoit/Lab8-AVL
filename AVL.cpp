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




