/* 
 * File:   testTreeDB.cpp
 * Author: Varun
 *
 * Created on November 13, 2012, 11:24 AM
 */

#include <cstdlib>
#include <string.h>
#include <iostream>
#include "../TreeDB.h"

using namespace std;

/*
   TreeNode* root;
   int probesCount;
   
 */

// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    cout<<"constructing a new TreeDB, using the default constructor\n";
    root = new TreeNode;
    root->setLeft(NULL);
    root->setRight(NULL);
    probesCount = 0;
    cout<<"Set root to ("<<root->getLeft()<<","<<root->getRight()<<")\n";
    cout<<"Leaving the constructor\n";
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    cout<<"Entered the destructor\n";
    deleteTree(root);
    cout<<"Deleted all the entries\n";
}

TreeNode *TreeDB::getRoot() const{
    cout<<"Entered getRoot(). Returning root = "<<root<<endl;
    return root;
}

void TreeDB::deleteTree(TreeNode* currNode){
    cout<<"Entered delteteTree("<<currNode->getEntry()->getName()<<")\n\t";
    if(currNode == NULL){        //The tree is empty, or we've gone past a leaf
        cout<<"\tTree is empty, or gone past a leaf. Returning (no value).\n";
        return;
    }
    else{
        cout    <<"\tThe node with entry \""<<currNode->getEntry()->getName()<<"\" has children.\n"
                <<"\t\tDeleting these children\n";
        //The current node has children
        deleteTree(currNode->getLeft());
        deleteTree(currNode->getRight());
    }
    cout<<"\tDeleting \""<<currNode->getEntry()->getName()<<"\"\n";
    delete currNode;
    
}

// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry){
    cout<<"Entered TreeDB::insert("<<newEntry->getName()<<")\n\t";
    //First, search for a node with the same key (
    //If found, return false;
    //if not found, insert the node at the required location. -- when it's greater
    //  than KEY's left, but less than KEY's right
    TreeNode *ins = new TreeNode(newEntry);
    if(root->getEntry() == NULL){
        cout<<"Tree is empty, setting root to new entry\n";
        root = ins;
        return true;
    }
    
    insert_in_bst(ins,root);
    
    cout<<"Success\n";
    return true;        //The node wasn't found, so we inserted it
}

bool TreeDB::insert_in_bst(TreeNode *ins, TreeNode *curr){
    cout<<"Insert_in_BST: \n";
   
    if(ins->getEntry()->getName() == curr->getEntry()->getName()){
        cout<<"Error: entry already exists\n";
        cout<<"Returning false from insert("<<ins->getEntry()->getName()<<")\n";
        return false;
    }
    
    cout<<ins->getEntry()->getName()<<" != "<<curr->getEntry()->getName()<<endl;
    cout<<"Traversing Tree...\n";
    if(ins->getEntry()->getName() < curr->getEntry()->getName()){  //Need to go left
        cout<<"\tGoing left\n";
        if(curr->getLeft() == NULL){
            cout<<"\t\t"<<curr->getEntry()->getName()<<"is a leaf.\n\t\t  Creating a new node on the left, with entry "<<ins->getEntry()->getName();
            curr->setLeft(ins);
        }
        else{
            cout<<"\t\t"<<curr->getEntry()->getName()<<"is not a leaf.\n\t\t Traversing left until a leaf.\n";
            insert_in_bst(ins,curr->getLeft());
            cout<<"Inserted Node, leaving insert."<<endl;
        }
    }
    else{  //Need to go left  //Could just make this an else
        cout<<"\tGoing right\n";
        if(curr->getRight() == NULL){
            cout<<"\t\t"<<curr->getEntry()->getName()<<"is a leaf.\n\t\t  Creating a new node on the right, with entry = "<<ins->getEntry()->getName();
            curr->setRight(ins);
        }
        else{
            cout<<"\t\t"<<curr->getEntry()->getName()<<"is not a leaf.\n\t\t Traversing right until a leaf.\n";
            insert_in_bst (ins, curr->getRight());
            cout<<"Inserted Node, leaving insert."<<endl;
        }
    }
    return true;
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name){
    cout<<"Entered \"TreeDB::find\"\n\t";
    cout<<"     returning NULL or a DBentry...\n";
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
    cout<<"\t\tEntered find_in_bst at \""<<curr->getEntry()->getName()<<"\", "<<name<<endl;
    DBentry *tmp = NULL;
    probesCount++;                              //want to increment every time we reach a new node
    cout<<"\t\tProbesCount: \t\t"<<probesCount<<endl;
    if(curr == NULL){
        cout<<"\t\tHaven't found entry \""<<name<<"\". Returning NULL\n";
        return NULL;
    }
    else if (curr->getEntry()->getName() == name){
        //We've found a match
        cout<<"\t\tFound a match. Returning node with entry name \""<<name<<"\"\n";
        return curr->getEntry();
    }
    else if (curr->getEntry()->getName() > name){
        //Need to go left
        cout<<"\t\tHaven't yet found a match, looking left\n";
        tmp = find_in_bst(curr->getLeft(), name);
        if(tmp != NULL){ //if something was found
            cout<<"\t\t\tFound! "
                    <<"Returning node with entry name \""<<name<<"\"\n";
            return tmp;
        }
    }
    if (curr->getEntry()->getName() < name){
        //Need to go right
        cout<<"\t\tHaven't yet found a match, looking right\n";
        tmp = find_in_bst(curr->getRight(), name);
        if(tmp != NULL){
            cout<<"\t\t\tFound!\n";
            return tmp;
        }
    }
    
    //If we got here, a match hasn't been found.
    //If we're in left and we return NULL, => not found in left branch
    //If we're in right and we return NULL, => not found in left or right...=>doesn't exist.
    //return NULL;
    
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool TreeDB::remove(string name){
    if(root == NULL){
        cout<<"Error: entry does not exist\n";
        return false;
    }
    DBentry *toDelete = find_in_bst(root, name);
    if (toDelete == NULL){
        cout<<"Error: entry does not exist\n";
        return false;
    }
    //The entry exists at the current DBentry
    //Find the node connected to the DBentry, and delete it in the correct manner.
    TreeNode *parent = getParent(toDelete);
    TreeNode *reqNode = NULL;
    TreeNode *temp = parent->getLeft();
   // cout<<"Parent->getLeft() is "<<parent->getLeft()<<endl;
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Checking if the node to be deleted is on the left or the right
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    if(parent != NULL && parent->getEntry() != NULL)
        cout<<"Parent's entry (should be D for the single leaf, A for the one-subtree): "<<parent->getEntry()->getName()<<endl;
    // Define an operator< function for the treeNode class? Then, I can just to parent < name => parent->getRight()
    cout<<"\tChecking if the required node is this entry's left or right child...\n";
    if(parent->getLeft()!= NULL && parent->getLeft()->getEntry()->getName() == name){
        cout<<"\t\t Left Child \n";
        reqNode = parent->getLeft();
    }
    else if(parent->getRight() !=NULL && parent->getRight()->getEntry()->getName() == name){
        cout<<"\t\t Right Child.\n";
        reqNode = parent->getRight();
    }
    
    //  ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Counting the number of children to parent                                                        //
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    int childCount = 0;
    if(parent->getLeft() != NULL)
        childCount += countChildren(parent->getLeft());
    if(parent->getRight() != NULL)
        childCount += countChildren(parent->getRight());
    
    
    if(reqNode == NULL){        //This will never happen...we know that the entry exists.
        cout<<"Error: entry does not exist ____ 1\n;";
        return false;
    }
    
   // bool twoChildren = (reqNode->getLeft() != NULL) && (reqNode->getRight() != NULL);       //Returns 1 iff neither is NULL
        //Count the number of children for this node
    //Case 1: Deleting a leaf
    if(childCount == 0){
        cout<<"Deleting a leaf\n";
        if(reqNode == parent->getLeft()){
            delete parent->getLeft();
            parent->setLeft(NULL);
            cout<<"Deleted Left leaf\n";
        }
        else if(reqNode == parent->getRight()){
            delete parent->getRight();
            parent->setRight(NULL);
            cout<<"deleted right leaf\n";
        }
        probesCount--;
        return true;
    }
        
    //Case 2: one child subtree
    if(childCount == 1){
        cout<<"Node to be removed has exactly one subtree\n";
        if(reqNode->getLeft()){
            cout<<"\tThe left child is the subtree\n";
            TreeNode *tmp = reqNode;
            reqNode->setLeft(NULL);
            //delete reqNode;
            parent->setLeft(tmp);
            cout<<"Moved the left subtree up to the deleted node's location\n";
        }
        else if(reqNode->getRight()){
            cout<<"\t The right child is the subtree\n";
            TreeNode *tmp = reqNode;
            reqNode->setRight(NULL);
            //delete reqNode;     //Needed? It wasn't allocated with new...
            parent->setRight(tmp);
            cout<<"Moved the right subtree up to the deleted node's location\n";
        }
        cout<<"Success\n";
        probesCount--;
        return true;
    }
    
    //Case 3: Both children are subtrees
    if(childCount == 2){
        cout<<"Node to be removed has two subtrees :'(\n";
        TreeNode *max_left = getRightMost(reqNode->getLeft());      //Finds the maximum node of the left child
        TreeNode *max_left_parent = NULL;
        if(countChildren(max_left)){
            //If the maximum node has a left subtree
            //find the parent to the maximum node
            max_left_parent = getParent(max_left->getEntry());
            //Set max_left's left subtree equal to max_left_parent's right pointer
            max_left_parent->setRight(max_left->getLeft());
        }
        TreeNode *left_subtree = reqNode->getLeft();                            //reqNode's left subtree
        TreeNode *right_subtree = reqNode->getRight();                          //reqNode's right subtree
        max_left->setLeft(left_subtree);                                        //Making max_left the parent of the left subtree's root
        max_left->setRight(right_subtree);                                      //Making max_left the parent of the right subtree's root
        
        if(parent->getLeft() == reqNode){                                     //Replacing reqNode with max_left
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
}

TreeNode *TreeDB::getParent(DBentry* _entry){
    if(root == NULL){    //Empty tree
        cout<<"getParent for an empty tree. Returning NULL\n";
        return NULL;
    }
    cout<<"Finding parent\n";
    TreeNode *reqNode = root;
    while(reqNode->getLeft()->getEntry() != _entry && reqNode->getRight()->getEntry() != _entry){
        cout<<"Searching tree for the node attached to the required entry...\n";
        if(reqNode->getEntry()->getName() > _entry->getName()){
            cout<<"\tGoing left\n";
            reqNode = reqNode->getLeft();
        }
        else if(reqNode->getEntry()->getName() < _entry->getName()){
            cout<<"\tGoing right\n";
            reqNode = reqNode->getRight();
        }
    }
    cout<<"Found Node before the one attached to entry "<<_entry->getName()<<endl;
    cout<<"\ti.e. parent = "<<reqNode->getEntry()->getName()<<endl;
    cout<<"Returning this node. Check if it's the left or right child that needs to be deleted\n";

    return reqNode;
}

int TreeDB::countChildren(TreeNode* curr){
    int count = 0;
    if(curr == NULL){
        cout<<"counting children for NULL!! Returning 0\n";
        return count;
    }
    cout<<"Counting the number of children for Node with entry \""<<curr->getEntry()->getName()<<"\"\n";
    if(curr->getLeft() != NULL){
        cout<<"\tcurr has a left child\n";
        count++;
    }
    if(curr->getRight() != NULL){
        cout<<"\tcurr has a right child\n";
        count++;
    }
    return count;
}

TreeNode *TreeDB::getRightMost(TreeNode *curr){
    cout<<"\tLooking for the rightmost node for TreeNode "<<curr->getEntry()->getName()<<endl;
    if(curr->getRight() == NULL){
        return curr;
    }
    return getRightMost(curr->getRight());
}
// deletes all the entries in the database.
void TreeDB::clear(){
        cout<<"Deleting Tree\n";
        deleteTree(root);
        cout<<"Success\n";
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const{
    cout<<"PrintProbes: ";
    cout<<probesCount<<endl;
}                                               //Implemented

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const{                                              //CONTINUE FROM HERE**********************                             
    //Recurse through the tree, and if active == 1, count++
    cout<<"\tIn countAvtive; counting Active nodes...\n";
    TreeNode *curr = root;
    int activeCount = 0;
    cout<<count_active(curr,activeCount)<<endl;
}

int TreeDB::count_active(TreeNode *curr, int& activeCount) const{                                       //Think it works...
    
    if(curr == NULL)
        return activeCount;
    cout<<"\t\tIn count_active, at Node \""<<curr->getEntry()->getName()<<"\";\n"
            <<"\t\t    current status: "<<curr->getEntry()->getActive()<<endl
            <<"\t\t    current activeCount: "<<activeCount<<endl;
    if(curr->getEntry()->getActive() == true)
        activeCount++;
    //go left, then go right, then add the two
    //recurses through the left, then reurses through the right, and then adds the two to get the activecount.
    cout<<"\t\tChecking Left children, activeCount = "<<activeCount<<endl;;
    int leftActive = count_active(curr->getLeft(), activeCount);
    cout<<"\t\tChecking Right children, activeCount = "<<activeCount<<endl;
    int rightActive = count_active(curr->getRight(), activeCount);
    cout<<"leftActive = "<<leftActive<<endl;
    cout<<"rightActive = "<<rightActive<<endl;
    cout<<"returning ActiveCount = "<<activeCount<<endl;
    return (activeCount);
    
}                                       //Think it works
// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, const TreeDB& rhs){
    //For each node, left, printNode, and then go right -- we want it in ascending order.
    cout<<"Printing the Tree...\n";
    //if(null), return
    if(rhs.getRoot() == NULL)
        return out;
    //else, print left, then print rhs, then  print right.
    else{
       // out<<rhs->getRoot()->getLeft(); //Prints the left nodes
        out<<rhs.getRoot()->getLeft();
        out<<rhs.getRoot();
        out<<rhs.getRoot()->getRight();
    }
    return out;
}

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs){                                      //<< overload for TreeNode...basically, we can cout<<currNode in the provios function.
    cout<<"\nPrinting Node\n";
    if(rhs == NULL)
        return out; //Don't want to dereference NULL
    //Recurse all the way to the left
    if(rhs->getLeft() != NULL){
        cout<<"\tGoing Left\n";
        out<<rhs->getLeft();
    }
    //cout<<"Printing \""<<rhs->getEntry()->getName()<<"\"\n";
    rhs->printNode();
    if(rhs->getRight() != NULL){
        cout<<"\tGoing Right\n";
        out<<rhs->getRight();
    }
    return out;
}   

int main(int argc, char** argv) {
    cout<<"Creating a new TreeDB\n";
    TreeDB tree;
    cout<<"Initial print test:\n\t";
    cout<<tree<<endl;
    
    cout<<"Creating a new entry with default constructor, to insert\n";
    DBentry *newEntry_default = new DBentry();
    cout<<"Commencing tests with the default entry contstuctor inseerted first...\n";
    cout<<"Need to test all public functions, i.e.:\n"
            <<"\t - insert (DBentry *newEntry_default)\n"
            <<"\t - find (string)\n"
            <<"\t - remove(string)\n"
            <<"\t clear()\n"
            <<"\t - printProbes()\n"
            <<"\t - countActive()\n"
            <<"\t - cout<<tree\n"
            <<"--------------------\n";
    tree.insert(newEntry_default);
    cout<<"Adding a duplicate name...check for error:\n";
    DBentry *newEntry_default2 = new DBentry();
    bool insertRoot = tree.insert(newEntry_default2);
    cout<<"Creating 5 entries using the second DBentry constructor";
    cout<<"Status for these entries: false, true, false, false, true\n";
    DBentry *newEntry3 = new DBentry("A",1,false);
    DBentry *newEntry4 = new DBentry("B",2,true);
    DBentry *newEntry5 = new DBentry("C",3,false);
    DBentry *newEntry6 = new DBentry("D",4,false);
    DBentry *newEntry7 = new DBentry("E",5,true);
    
    cout<<"Because the default entry constructor initializes to a blank, everything should be on the right side\n";
    bool insertFirst = tree.insert(newEntry3);
    bool insertSecond = tree.insert(newEntry4);
    bool insertThird = tree.insert(newEntry5);
    bool insertFourth = tree.insert(newEntry6);
    bool insertFifth = tree.insert(newEntry7);
    
    cout<<"Inserted all the nodes. \nCommencing the find test\n";
    DBentry *findThird = tree.find("C");
    cout<<"\tShould have found 'C'\n";
    
    cout<<"count-active test: should return 2\n";
    tree.countActive();
    
    cout<<"Find test completed. Remove tests commencing...\n";
    cout<<"With this structure, can only test remove of a leaf, or with one subtree\n";
    
    cout<<"Leaf remove first...\n";
    bool successfulLeafRemove = tree.remove("E");
    cout<<"Successfuly removed leaf?: "<<successfulLeafRemove<<endl;
     cout<<"Printing out tree to make sure...should be missing \"E\"\n"
        <<tree<<endl;
    cout<<"One-subtree remove:\n\tRemoving B...\n";
    bool successfulOneRemove = tree.remove("B");
    cout<<"Successful one-subtree remove?: "<<successfulOneRemove<<endl;
    cout<<"Printing out tree to make sure...should be missing \"E\" and \"B\"\n"
        <<tree<<endl;
    cout<<"Removing non-existant node...\n";
    bool successfulImaginaryRemove = tree.remove("Z");
    cout<<"successful imaginary remove?: "<<successfulImaginaryRemove<<endl;
    
    cout<<"Remove tests complete.\n"
            <<"Commencing PrintProbes test...\n";
    tree.printProbes();
    
    cout<<"PrintProbes test completed.\n"
            <<"Commencing active-count test...should return 0\n";
    tree.countActive();
    
    cout<<"count-active test completed.\n"
            <<"Commencing print test...\n";
    cout<<tree<<endl;
    
    cout<<"Print test completed.\n";
    cout<<"Commencing tree deletion\n";
    
    tree.clear();
    cout<<"printing tree to make sure it's empty (should be blank):\n";
    cout<<tree;
    
    cout<<"Tree deletion complete.\n";
    cout<<"ALL TESTS COMPLETE!\n"
            <<"Deleting dynamic data...\n";
    delete newEntry_default;
    delete newEntry_default2;
    delete newEntry3;
    delete newEntry4;
    delete newEntry5;
    delete newEntry6;
    delete newEntry7;
    
    newEntry_default = NULL;
    newEntry_default2 = NULL;
    newEntry3 = NULL;
    newEntry4 = NULL;
    newEntry5 = NULL;
    newEntry6 = NULL;
    newEntry7 = NULL;
    
    cout<<"Deletions complete!\n"
            <<"Exiting...\n";
    
    return 0;
}

