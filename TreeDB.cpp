/* 
 * File:   testTreeDB.cpp
 * Author: Varun
 *
 * Created on November 13, 2012, 11:24 AM
 */

#include <cstdlib>
#include <string.h>
#include <iostream>
#include "TreeDB.h"

using namespace std;

// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    root = new TreeNode;
    root->setLeft(NULL);
    root->setRight(NULL);
    probesCount = 0;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    deleteTree(root);
}

TreeNode *TreeDB::getRoot() const{
    return root;
}

void TreeDB::deleteTree(TreeNode* currNode){
    if(currNode == NULL){        //The tree is empty, or we've gone past a leaf
        return;
    }
    else{
         remove(root->getEntry()->getName());
         deleteTree(root);
        }
}
// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry){
   //First, search for a node with the same key (
    //If found, return false;
    //if not found, insert the node at the required location. -- when it's greater
    //  than KEY's left, but less than KEY's right
    TreeNode *ins = new TreeNode(newEntry);
    if(root->getEntry() == NULL){
        root = ins;
        return true;
    }
    
    bool inserted = insert_in_bst(ins,root);
    
    cout<<"Success\n";
    return inserted;        //The node wasn't found, so we inserted it
}

bool TreeDB::insert_in_bst(TreeNode *ins, TreeNode *curr){
    if(ins->getEntry()->getName() == curr->getEntry()->getName()){
        cout<<"Error: entry already exists\n";
        return false;
    }
    
    if(ins->getEntry()->getName() < curr->getEntry()->getName()){  //Need to go left
        if(curr->getLeft() == NULL){
            curr->setLeft(ins);
        }
        else{
            insert_in_bst(ins,curr->getLeft());
        }
    }
    else{  //Need to go right  //Could just make this an else
        if(curr->getRight() == NULL){
            curr->setRight(ins);
        }
        else{
            insert_in_bst (ins, curr->getRight());
        }
    }
    return true;
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name){
    return find_in_bst(root, name);
}

//recursively searches the tree, starting with root.
//      returns the DBentry if its name matches the required name
//      returns NULL if not found.

//      if currNode's key == name, return key
//      If currNode == NULL, then we haven't found it. Return NULL 
//      else if (name < currNode's entry's name, find_in_bst(currNode->left, name)
//      else if (name > currnode's entry's name, find_in_bst(currNode->right, name)
//      find_in_bst checks if the input value's name matches either left or right, and returns it. 
//      Returns NULL otherwise, at which point, we'd recurse 
DBentry *TreeDB::find_in_bst(TreeNode *curr, string name){
    DBentry *tmp = NULL;
    probesCount++;                              //want to increment every time we reach a new node
    if(curr == NULL){                           //ERROR: NOT FOUND
        return NULL;
    }
    else if (curr->getEntry()->getName() == name){
        //We've found a match
        cout<<curr;                                                             //COUT<<CURR IN PARSER
        return curr->getEntry();
    }
     if (curr->getEntry()->getName() > name && curr->getLeft()){
        //Need to go left
        tmp = find_in_bst(curr->getLeft(), name);
        if(tmp != NULL){ //if something was found                               //COUT<<CURR IN 
            return tmp;
        }
    }
    if (curr->getEntry()->getName() < name && curr->getRight()){
        //Need to go right
        tmp = find_in_bst(curr->getRight(), name);
        if(tmp != NULL){                                                        //Found
            return tmp;
        }
    }
    return NULL;                                                                //ERROR: NOT FOUND
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool TreeDB::remove(string name){
    if(root == NULL){                   //Empty tree                            //ERROR:NOT FOUND in parser
        return false;
    }
    DBentry *toDelete = find_in_bst(root, name);
    if (toDelete == NULL){              //Entry not found                       //ERROR: NOT FOUND in parser
        return false;
    }

    bool successfulDelete = false;

    //Case : deleting root
    if(root->getEntry()->getName() == name){
        successfulDelete = removeRoot(name);
        return successfulDelete;
    }
   TreeNode *nodeToDelete = find_node_in_bst(root,name);
   TreeNode *parent = getParent(root, name);

    // Counting the number of children to parent                                                        //
    int childCount = 0;
    if(parent->getLeft() != NULL)
        childCount += countChildren(parent->getLeft());
    if(parent->getRight() != NULL)
        childCount += countChildren(parent->getRight());
    
    //Case 1: Deleting a leaf
    if(childCount == 0){
        successfulDelete = removeLeaf(parent,name);
    }
        
    //Case 2: one child subtree
    if(childCount == 1){
        successfulDelete = removeWithOneSubtree(parent,name);
    }
    
    //Case 3: Both children are subtrees
    if(childCount == 2){
        successfulDelete = removeWithTwoSubtrees(parent,name);
    }
    return successfulDelete;
}

TreeNode *TreeDB::find_node_in_bst (TreeNode *node, string name) {
    if (node == NULL) 
      return (NULL);    // Basis.  Not found.                                   //ERROR:NOT FOUND in parser

   if (node->getEntry()->getName() == name)
      return (node);     // Basis.  Found.                                      //ERROR:NOT FOUND in parser
  
   if (name < node->getEntry()->getName())
      return ( find_node_in_bst (node->getLeft(), name) );
   else 
      return ( find_node_in_bst (node->getRight(), name) );
}


bool TreeDB::removeRoot(string name){
    if(root == NULL){                                                           ////ERROR:NOT FOUND in parser
        return false;
    }

    int numChildren = countChildren(root);
    
    //Case 1: No children - delete root, set root to NULL
    if(numChildren == 0){
        delete root;
        root = NULL;
        probesCount--;
        return true;
    }
    else if(numChildren == 1){
        if(root->getLeft()){
            TreeNode *tmp = root->getLeft();
            delete root;
            root = tmp;
            probesCount--;
            return true;
        }
        else{
            TreeNode *tmp = root->getRight();
            delete root;
            root = tmp;
            probesCount--;
            return true;
        }
    }
    else if(numChildren == 2){
        TreeNode *max_left = getRightMost(root->getLeft());      //Finds the maximum node of the left child
        TreeNode *max_left_parent = NULL;
        if(countChildren(max_left)){
            //If the maximum left node has a left subtree
            //find the parent to the maximum node
            max_left_parent = getParent(max_left, name);
            //Set max_left's left subtree equal to max_left_parent's right pointer
            max_left_parent->setRight(max_left->getLeft());
        }
        TreeNode *left_subtree = root->getLeft();                            //reqNode's left subtree
        TreeNode *right_subtree = root->getRight();                          //reqNode's right subtree
        max_left->setLeft(left_subtree);                                        //Making max_left the parent of the left subtree's root
        max_left->setRight(right_subtree);                                      //Making max_left the parent of the right subtree's root

        delete root;
        root = max_left;
        probesCount--;
        return true;
    }
}

bool TreeDB::removeLeaf(TreeNode *parent, string name){
    if(parent == NULL)
        return false;
    
    if(parent->getLeft() != NULL && parent->getLeft()->getEntry()->getName() == name){
        delete parent->getLeft();
        parent->setLeft(NULL);
    }
    else if(parent->getRight() != NULL && parent->getRight()->getEntry()->getName() == name){
        delete parent->getRight();
        parent->setRight(NULL);
    }
    probesCount--;
    return true;
}

bool TreeDB::removeWithOneSubtree(TreeNode *parent, string name){
    TreeNode *reqNode = NULL;
    if(parent == NULL)
        return false;
    //Find if the node to be deleted is the left child or the right child
    if(parent->getLeft() != NULL && parent->getLeft()->getEntry()->getName() == name){          //If the left child is the required node
        reqNode = parent->getLeft();
    }
    else if(parent->getRight() != NULL && parent->getRight()->getEntry()->getName() == name){   //If the right child is the required node
        reqNode = parent->getRight();
    }
    TreeNode *tmp;
    if(reqNode->getLeft()){                                                                     //Left child is root of a subtree
            tmp = reqNode;      
            reqNode->setLeft(NULL);                                                             //Delete the left child of parent
            parent->setLeft(tmp);                                                               //Moved the subtree up to be the left child
    }
    else if(reqNode->getRight()){                                                               //Right child is root of a subtree
        tmp = reqNode;                                                                          
        reqNode->setRight(NULL);                                                                //Deleted the right child of parent
        parent->setRight(tmp->getRight());                                                      //Moved the subtree up to be the right child
    }
    probesCount--;
    return true;                                                                //COUT<<"SUCCESS" in parser, if true
}

bool TreeDB::removeWithTwoSubtrees(TreeNode *parent, string name){
    TreeNode *reqNode = NULL;
    if(parent == NULL){
        return false;
    }
    if(parent->getLeft()->getEntry()->getName() == name){
        reqNode = parent->getLeft();
    }
    else{
        reqNode = parent->getRight();
    }
    TreeNode *max_left = getRightMost(reqNode->getLeft());                      //Finds the maximum node of the left child
    TreeNode *max_left_parent = NULL;
    if(countChildren(max_left)){                                                
        //If the maximum left node has a left subtree, find the parent to the maximum left node
        max_left_parent = getParent(max_left, name);  
        //Set max_left's left subtree equal to max_left_parent's right pointer
        max_left_parent->setRight(max_left->getLeft());
    }
    TreeNode *left_subtree = reqNode->getLeft();                                //reqNode's left subtree
    TreeNode *right_subtree = reqNode->getRight();                              //reqNode's right subtree
    max_left->setLeft(left_subtree);                                            //Making max_left the parent of the left subtree's root
    max_left->setRight(right_subtree);                                          //Making max_left the parent of the right subtree's root

    if(parent->getLeft() == reqNode){                                           //Replacing reqNode with max_left
        parent->setLeft(max_left);
    }
    else{
        parent->setRight(max_left);
    }

    reqNode->setLeft(NULL);
    reqNode->setRight(NULL);
    probesCount--;
    return true;
}

TreeNode *TreeDB::getParent(TreeNode *curr, string name){
   if (curr == NULL) 
	return (NULL);    // Basis.  Not found.                                 //ERROR:NOT FOUND
    if(root == NULL)
        return NULL;
   
    if(curr->getLeft() != NULL){                                                //the current node has a left child
        if(curr->getLeft()->getEntry()->getName() == name){
            return curr;        //Basis. Found.
        }
    }
    
    if(curr->getRight() != NULL){
        if(curr->getRight()->getEntry()->getName() == name)
            return (curr);     // Basis.  Found.                                //COUT<<FOUND
   }
    
    
   if (name < curr->getEntry()->getName() && curr->getLeft() != NULL){          //Go left
      return ( getParent (curr->getLeft(), name) );
   }
   else if(name > curr->getEntry()->getName() && curr->getRight() != NULL){     //Go right
      return ( getParent (curr->getRight(), name) );
   }
}

int TreeDB::countChildren(TreeNode* curr){
    int count = 0;
    if(curr == NULL){
        return count;
    }
    
    if(curr->getLeft() != NULL){
        count++;
    }
    if(curr->getRight() != NULL){
        count++;
    }
    return count;
}

TreeNode *TreeDB::getRightMost(TreeNode *curr){
    if(curr->getRight() == NULL){
        return curr;
    }
    return getRightMost(curr->getRight());
}

// deletes all the entries in the database.
void TreeDB::clear(){
        deleteTree(root);
        cout<<"Success\n";
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const{
    cout<<probesCount<<endl;
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const{                                                                           
    //Recurse through the tree, and if active == 1, count++
    TreeNode *curr = root;
    int activeCount = 0;
    cout<<count_active(curr,activeCount)<<endl;
}

int TreeDB::count_active(TreeNode *curr, int& activeCount) const{                                       
    
    if(curr == NULL)
        return activeCount;                                                     //Basis. Reached the end of the branch
    if(curr->getEntry()->getActive() == true)
        activeCount++;

    //recurse left, then right. Results in adding the two.
    int leftActive = count_active(curr->getLeft(), activeCount);
    int rightActive = count_active(curr->getRight(), activeCount);
    
    return (activeCount);
}

// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, const TreeDB& rhs){
    if(rhs.getRoot() == NULL){                                                  //Empty tree. Return without printing anything.
        return out;
    }
        
    else{                                                                       //Print in order
        out<<rhs.getRoot();
    }
    return out;
}

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs){
    if(rhs == NULL){                                                            //Reached the end of the brangh
        return out;
    }
    
    //Recurse left
    if(rhs->getLeft() != NULL){
        out<<rhs->getLeft()<<endl;
    }
    //Print the current node
    rhs->printNode();
    
    //Recurse right
    if(rhs->getRight() != NULL){
        out<<rhs->getRight()<<endl;
    }
    
    return out;
}   
