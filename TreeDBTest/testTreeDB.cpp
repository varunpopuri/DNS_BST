/* 
 * File:   testTreeDB.cpp
 * Author: Varun
 *
 * Created on November 13, 2012, 11:24 AM
 */

#include <cstdlib>
#include <string.h>

using namespace std;

/*
   TreeNode* root;
   int probesCount;
   
 */

// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    root->setLeft(NULL);
    root->setRight(NULL);
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    deleteTree(root);
}

void TreeDB::deleteTree(TreeNode* currNode){
    if(currNode == NULL)        //The tree is empty, or we've gone past a leaf
        return;
    else{
        //The current node has children
        deleteTree(currNode->getLeft());
        deleteTree(currNode->getRight());
    }
    delete currNode;
}

// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry){
    //First, search for a node with the same key (
    //If found, return false;
    //if not found, insert the node at the required location. -- when it's greater
    //  than KEY's left, but less than KEY's right
    TreeNode *currNode = root;
    if(currNode->getEntry()->getName() == newEntry->getName()){
        return false;
    }
    
    if(currNode->getEntry()->getName() < newEntry->getName()){  //Need to go right
        if(currNode->getRight == NULL){
            currNode->setRight(newEntry);
        }
        else
            insert(currNode->getRight(), newEntry);
    }
    else if(currNode->getEntry()->getName() > newEntry->getName()){  //Need to go left  //Could just make this an else
        if(currNode->getLeft == NULL){
            currNode->setLeft(newEntry);
        }
        else
            insert (currNode->getLeft(), newEntry);
    }
    return true;        //The node wasn't found, so we inserted it
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
    if(curr == NULL){
        return NULL;
    }
    else if (curr->getEntry()->getName() == name){
        //We've found a match
        return curr->getEntry();
    }
    else if (curr->getEntry()->getName() > name){
        //Need to go left
        tmp = find_in_bst(curr->getLeft(), name);
        if(tmp != NULL) //if something was found
            return tmp;
    }
    if (curr->getEntry()->getName() < name){
        //Need to go right
        tmp = find_in_bst(curr->getRight(), name);
        if(tmp != NULL)
            return tmp;
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
    //To be implemented later
}

// deletes all the entries in the database.
void TreeDB::clear(){
    //to be implemented later
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const{
    cout<<probesCount<<endl;
}                                               //Implemented

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const{                                      
    //Recurse through the tree, and if active == 1, count++
    TreeNode *curr = root;
    return count_active(root);
}

int TreeDB::count_active(TreeNode *curr){                                       //Think it works...
    int activeCount = 0;
       
    if(curr == NULL)
        return activeCount;
    if(curr->getEntry()->getActive() == true)
        activeCount++;
    //go left, then go right, then add the two
    //recurses through the left, then reurses through the right, and then adds the two to get the activecount.
    return (count_active(curr->getLeft()) + count_active(curr->getRight()));
    
}                                       //Think it works
// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, const TreeDB& rhs){
    //For each node, left, printNode, and then go right -- we want it in ascending order.
    
    //if(null), return
    //else, print left, then print rhs, then  print right.
}


// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs){                                      //<< overload for TreeNode...basically, we can cout<<currNode in the provios function.
    out<<rhs->printNode();
    return out;
}   

int main(int argc, char** argv) {

    return 0;
}

