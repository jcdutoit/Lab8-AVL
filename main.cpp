#include "AVL.h"
#include "AVLutil.h"
#include <sstream>
#include <queue>
#include <iostream>



int main(){
    AVL avlTree;
    for(int i=1; i<16; ++i){
        avlTree.add(i);
    }
    cout << treeString(avlTree.getRootNode()) << endl;
    avlTree.remove(9);
    avlTree.remove(11);
    avlTree.remove(13);
    avlTree.remove(15);
    avlTree.remove(10);
    avlTree.remove(14);
    avlTree.remove(1);
    avlTree.remove(3);
    cout << treeString(avlTree.getRootNode()) << endl;
    checkBalance(avlTree.root);

    rotateLeft(avlTree.root);
}