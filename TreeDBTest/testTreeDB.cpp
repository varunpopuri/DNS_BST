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
    //cout<<"Entered getRoot(). Returning root = "<<root<<endl;
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
     if (curr->getEntry()->getName() > name && curr->getLeft()){
        //Need to go left
        cout<<"\t\tHaven't yet found a match, looking left\n";
        tmp = find_in_bst(curr->getLeft(), name);
        if(tmp != NULL){ //if something was found
            cout<<"\t\t\tFound! "
                    <<"Returning node with entry name \""<<name<<"\"\n";
            return tmp;
        }
    }
    if (curr->getEntry()->getName() < name && curr->getRight()){
        //Need to go right
        cout<<"\t\tHaven't yet found a match, looking right\n";
        cout<<"\t\ti.e. go to node";
        cout<<curr->getRight()->getEntry()->getName()<<endl;
        tmp = find_in_bst(curr->getRight(), name);
        if(tmp != NULL){
            cout<<"\t\t\tFound!\n";
            return tmp;
        }
    }
    cout<<"Error: entry not found\n";
    return NULL;
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool TreeDB::remove(string name){
    cout<<"Removing node "<<name<<endl;
    if(root == NULL){                   //Empty tree
        cout<<"Error: entry does not exist\n";
        return false;
    }
    DBentry *toDelete = find_in_bst(root, name);
    if (toDelete == NULL){              //Entry not found
        cout<<"Error: entry does not exist\n";
        return false;
    }

    bool successfulDelete = false;

    //Case : deleting root
    if(root->getEntry()->getName() == name){
        cout<<"Deleting root\n";
        successfulDelete = removeRoot(name);
    }
   TreeNode *nodeToDelete = find_node_in_bst(root,name);
   TreeNode *parent = getParent(root, name);

    if(parent != NULL && parent->getEntry() != NULL)
        cout<<"Parent's entry (should be D for the single leaf, A for the one-subtree): "<<parent->getEntry()->getName()<<endl;
    
    // Counting the number of children to parent                                                        //
    int childCount = 0;
    if(parent->getLeft() != NULL)
        childCount += countChildren(parent->getLeft());
    if(parent->getRight() != NULL)
        childCount += countChildren(parent->getRight());
    
    //Case 1: Deleting a leaf
    if(childCount == 0){
        cout<<"Deleting a leaf\n";
        successfulDelete = removeLeaf(parent,name);
    }
        
    //Case 2: one child subtree
    if(childCount == 1){
        cout<<"Node to be removed has exactly one subtree\n";
        successfulDelete = removeWithOneSubtree(parent,name);
    }
    
    //Case 3: Both children are subtrees
    if(childCount == 2){
        cout<<"Node to be removed has two subtrees :'(\n";
        successfulDelete = removeWithTwoSubtrees(parent,name);
    }
    return successfulDelete;
}

TreeNode *TreeDB::find_node_in_bst (TreeNode *node, string name) {
    cout<<"finding a node in the bst\n";
   // cout<<"\tCurrently at Node \""<<node->getEntry()->getName()<<"\"\n";
    if (node == NULL) 
      return (NULL);    // Basis.  Not found.

   if (node->getEntry()->getName() == name)
      return (node);     // Basis.  Found.
  
   if (name < node->getEntry()->getName())
      return ( find_node_in_bst (node->getLeft(), name) );
   else 
      return ( find_node_in_bst (node->getRight(), name) );
}


bool TreeDB::removeRoot(string name){
    if(root == NULL){
        cout<<"\tDeleting an empty tree\n";
        return false;
    }
    cout<<"Deleting root...\n";
    int numChildren = countChildren(root);
    cout<<"Root has "<<numChildren<<" child(ren)\n";
    
    //Case 1: No children - delete root, set root to NULL
    if(numChildren == 0){
        cout<<"\tRoot has no children.\n";
        delete root;
        root = NULL;
        probesCount--;
        return true;
    }
    else if(numChildren == 1){
        cout<<"\tRoot has one child.\n";
        if(root->getLeft()){
            cout<<"\t\tChild is on Root's left\n";
            TreeNode *tmp = root->getLeft();
            delete root;
            root = tmp;
            probesCount--;
            return true;
        }
        else{
            cout<<"\t\tChild is on Root's right\n";
            TreeNode *tmp = root->getRight();
            delete root;
            root = tmp;
            probesCount--;
            return true;
        }
    }
    else if(numChildren == 2){
        cout<<"\tRoot has 2 children.\n";
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
        cout<<"Deleted Left leaf\n";
    }
    else if(parent->getRight() != NULL && parent->getRight()->getEntry()->getName() == name){
        delete parent->getRight();
        parent->setRight(NULL);
        cout<<"deleted right leaf\n";
    }
    probesCount--;
    return true;
}

bool TreeDB::removeWithOneSubtree(TreeNode *parent, string name){
    TreeNode *reqNode = NULL;
    if(parent == NULL)
        return false;
    cout<<"Parent = "<<parent->getEntry()->getName()<<endl;
    //Find if the node to be deleted is the left child or the right child
    if(parent->getLeft() != NULL && parent->getLeft()->getEntry()->getName() == name){
        reqNode = parent->getLeft();
    }
    else if(parent->getRight() != NULL && parent->getRight()->getEntry()->getName() == name){
        reqNode = parent->getRight();
    }
    TreeNode *tmp;
    if(reqNode->getLeft()){
            cout<<"\tThe left child is the subtree\n";
            tmp = reqNode;
            reqNode->setLeft(NULL);
            //delete reqNode;
            parent->setLeft(tmp);
            cout<<"Moved the left subtree up to the deleted node's location\n";
    }
    else if(reqNode->getRight()){
        cout<<"\t The right child is the subtree\n";
        tmp = reqNode;
        cout<<"tmp->right = "<<tmp->getRight()->getEntry()->getName()<<endl;
        //reqNode->setRight(NULL);
        //delete reqNode;     //Needed? It wasn't allocated with new...
        parent->setRight(tmp->getRight());
        cout<<"Moved the right subtree up to the deleted node's location\n";
    }
    cout<<"Parent = "<<parent->getEntry()->getName()<<endl;
    cout<<"Right Child = "<<parent->getRight()->getEntry()->getName()<<endl;
    cout<<"Success\n";
    probesCount--;
    return true;
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
    TreeNode *max_left = getRightMost(reqNode->getLeft());      //Finds the maximum node of the left child
    TreeNode *max_left_parent = NULL;
    if(countChildren(max_left)){
        //If the maximum node has a left subtree
        //find the parent to the maximum node
        max_left_parent = getParent(max_left, name);  //was: max_left()->getEntry();
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

TreeNode *TreeDB::getParent(TreeNode *curr, string name){
    cout<<"Finding parent of node with name "<<name<<endl;
   if (curr == NULL) 
	return (NULL);    // Basis.  Not found.
    if(root == NULL)
        return NULL;
    cout<<"curr = "<<curr->getEntry()->getName()<<endl;
    if(curr->getLeft() != NULL){
        cout<<"Curr has a left child\n";
        if(curr->getLeft()->getEntry()->getName() == name){
            return curr;        //Basis. Found.
        }
    }
    
    if(curr->getRight() != NULL){
        cout<<"Curr has a right child\n";
        if(curr->getRight()->getEntry()->getName() == name)
            return (curr);     // Basis.  Found.
   }
    
    
   if (name < curr->getEntry()->getName() && curr->getLeft() != NULL){
       cout<<"\tGoing left\n";
      return ( getParent (curr->getLeft(), name) );
   }
   else if(name > curr->getEntry()->getName() && curr->getRight() != NULL){
       cout<<"\tGoing right\n";
      return ( getParent (curr->getRight(), name) );
   }
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
    if(rhs.getRoot() == NULL){
        cout<<"Printing an empty tree\n";
        return out;
    }
        
    //else, print left, then print rhs, then  print right.
    else{
        cout<<"Tree is not empty\n";
       // out<<rhs->getRoot()->getLeft(); //Prints the left nodes
        //out<<rhs.getRoot()->getLeft();
        out<<rhs.getRoot();
        //out<<rhs.getRoot()->getRight();
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
        cout<<"\tGoing Left from "<<rhs->getEntry()<<"\n";
        out<<rhs->getLeft()->getEntry()<<endl;
        return out;
    }
    cout<<"Printing rhs: \n";
    rhs->printNode();
    if(rhs->getRight() != NULL){
        cout<<"\tGoing Right from "<<rhs->getEntry()<<"\n";
        out<<rhs->getRight()->getEntry()<<endl;
        return out;
    }
    return out;
}   

int main(int argc, char** argv) {
    cout<<"Creating a new TreeDB\n";
    TreeDB tree;
    cout<<"Initial print test:\n\t";
    cout<<tree<<endl;
    
//    cout<<"Creating a new entry with default constructor, to insert\n";
//    DBentry *newEntry_default = new DBentry();
    DBentry *newEntry1 = new DBentry("Root",0,false);
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
    tree.insert(newEntry1);
    cout<<"Adding a duplicate name...check for error:\n";
    DBentry *newEntry2 = new DBentry("Root",15,true);
    bool insertRoot = tree.insert(newEntry2);
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
    cout<<"\nWas C deleted instead of B?: ";
    
    DBentry *CwasDeleted = tree.find("C");
    if(CwasDeleted == NULL)
        cout<<"C was deleted :'(\n";
    //    cout<<"Printing out tree to make sure...should be missing \"E\" and \"B\"\n"
//        <<tree<<endl;
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
    delete newEntry1;
    delete newEntry2;
    delete newEntry3;
    delete newEntry4;
    delete newEntry5;
    delete newEntry6;
    delete newEntry7;
    
    newEntry1 = NULL;
    newEntry2 = NULL;
    newEntry3 = NULL;
    newEntry4 = NULL;
    newEntry5 = NULL;
    newEntry6 = NULL;
    newEntry7 = NULL;
    
    cout<<"Deletions complete!\n"
            <<"Exiting...\n";
    
    return 0;
}

