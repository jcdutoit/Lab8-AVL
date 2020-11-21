# TARGETS = Test_Binary_Search_Tree_Numbers bst
CC = g++
CCFLAGS = -std=c++11 -g
avl: main.cpp AVLInterface.h NodeInterface.h AVL.h AVL.cpp Node.h Node.cpp AVLutil.h AVLutil.cpp 
	$(CC) $(CCFLAGS) -o avl main.cpp AVL.cpp Node.cpp AVLutil.cpp
# Test_Binary_Search_Tree_Numbers: Test_Binary_Search_Tree_Numbers.cpp Binary_Search_Tree.h Binary_Tree.h BTNode.h pre_order_traversal.h
# 	$(CC) $(CCFLAGS) -o Test_Binary_Search_Tree_Numbers Test_Binary_Search_Tree_Numbers.cpp



