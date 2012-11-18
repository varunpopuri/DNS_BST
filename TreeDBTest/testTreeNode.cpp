/* 
 * File:   testTreeNode.cpp
 * Author: Varun
 *
 * Created on November 13, 2012, 12:39 AM
 */

#include <cstdlib>
#include <iostream>
#include "DBentry.h"
#include "TreeNode.h"

using namespace std;

/*
    DBentry* entryPtr;
    TreeNode* left;
    TreeNode* right; 
 */

// A useful constructor
TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;                       //entryPtr is the pointer to the DBentry of the current TreeNode
    cout<<"\tUseful constructor, set entryPtr to "<<entryPtr<<endl;
    cout<<"Value of DBentry set to: "<<*entryPtr;
}

// the destructor
TreeNode::~TreeNode(){
    //No dynamic allocation, set the pointers to NULL:
    entryPtr = NULL;
    left = NULL;
    right = NULL;
    cout<<"\tDestroyed TreeNode;\n"
        <<"\t\tentryPtr = "<<entryPtr<<endl
        <<"\t\tleft = "<<left<<endl
        <<"\t\tright = "<<right<<endl;
}

// sets the left child of the TreeNode.
void  TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
    cout<<"\tEntered setLeft();\n"
        <<"\t\tset left to "<<left<<endl;
}

// sets the right child of the TreeNode
void  TreeNode::setRight(TreeNode* newRight){
    right = newRight;
    cout<<"\tEntered setRight();\n"
        <<"\t\tset right to "<<right<<endl;
}

// gets the left child of the TreeNode.
TreeNode*  TreeNode::getLeft() const{
    cout<<"Entered getLeft();\n"
        <<"\t\treturning "<<left<<endl;
    return left;
}

// gets the right child of the TreeNode
TreeNode*  TreeNode::getRight() const{
    cout<<"Entered getRight();\n"
        <<"\t\treturning "<<right<<endl;
    return right;
}

// returns a pointer to the DBentry the TreeNode contains. 
DBentry*  TreeNode::getEntry() const{
    cout<<"Entered getEntry();\n"
        <<"\t\treturning "<<entryPtr<<endl;
    return entryPtr;
}

int main(int argc, char** argv) {
    cout<<"Testing TreeNode.cpp\n";
    cout<<"Creating a TreeNode and a DBentry, and checking if the right values are assigned.\n";
    
    DBentry *testDB1 = new DBentry();
    TreeNode *treeNodeTest = new TreeNode(testDB1);
    
    cout<<"Commencing Accessor Functions to TreeNode...\n";
    TreeNode *testLeft = treeNodeTest->getLeft();
    TreeNode *getRight = treeNodeTest->getRight();
    DBentry *testDB2 = treeNodeTest->getEntry();
    
    cout<<"Expected: random addresses\n";
    cout<<"Accessor Function Tests Complete.\n"
        <<"Commencing Mutator Function Tests...\n";
    
    treeNodeTest->setLeft(NULL);
    treeNodeTest->setRight(NULL);
    
    cout<<"Expected: 0 \n 0\n";
    cout<<"Mutator Function Testing Complete.\n";
    cout<<"All Tests Complete!\n";
    cout<<"Deleting dynamically allocated objects in main...\n";
    
    delete testDB1;
    testDB1 = NULL;
    
    delete treeNodeTest;
    treeNodeTest = NULL;
    
    cout<<"Deletes completed. Exiting...\n";
    return 0;
}

