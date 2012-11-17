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
    cout<<"constructing a new TreeDB, using the default constructor\n";
    root->setLeft(NULL);
    root->setRight(NULL);
    cout<<"Set root to ("<<root->getLeft()<<","<<root->getRight()<<")\n";
    cout<<"Leaving the constructor\n";
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    cout<<"Entered the destructor\n";
    deleteTree(root);
    cout<<"Deleted all the entries\n";
}

TreeNode *TreeDB::getRoot(){
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
    TreeNode *currNode = root;
    if(currNode->getEntry()->getName() == newEntry->getName()){
        cout<<"Error: entry already exists\n";
        cout<<"Returning false from insert("<<newEntry->getName()<<")\n";
        return false;
    }
    cout<<currNode->getEntry()->getName()<<" != "<<newEntry->getName()<<endl;
    cout<<"Traversing Tree...\n";
    if(currNode->getEntry()->getName() < newEntry->getName()){  //Need to go right
        cout<<"\tGoing right\n";
        if(currNode->getRight == NULL){
            cout<<"\t\t"<<currNode->getEntry()->getName()<<"is a leaf.\n\t\t  Creating a new node on the right, with entry = "<<newEntry;
            currNode->setRight(newEntry);
        }
        else{
            cout<<"\t\t"<<currNode->getEntry()->getName()<<"is not a leaf.\n\t\t Traversing right until a leaf.\n";
            insert(currNode->getRight(), newEntry);
            cout<<"Inserted Node, leaving insert."<<endl;
        }
    }
    else if(currNode->getEntry()->getName() > newEntry->getName()){  //Need to go left  //Could just make this an else
        cout<<"\tGoing left\n";
        if(currNode->getLeft == NULL){
            cout<<"\t\t"<<currNode->getEntry()->getName()<<"is a leaf.\n\t\t  Creating a new node on the left, with entry = "<<newEntry;
            currNode->setLeft(newEntry);
        }
        else{
            insert (currNode->getLeft(), newEntry);
        }
    }
    cout<<"Success\n";
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
    TreeNode *parent = findParentToNodeWithEntry(toDelete);
    TreeNode *reqNode = NULL;
    
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Checking if the node to be deleted is on the left or the right
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Define an operator< function for the treeNode class? Then, I can just to parent < name => parent->getRight()
    cout<<"\tChecking if the required node is this entry's left or right child...\n";
    if(parent->getLeft()->getEntry()->getName() == name()){
        cout<<"\t\t Left Child \n";
        reqNode = parent->getLeft();
    }
    else{
        cout<<"\t\t Right Child.\n";
        reqNode = parent->getRight();
    }
    
    //  ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Counting the number of children to parent                                                        //
    // ///////////////////////////////////////////////////////////////////////////////////////////////////
    int childCount = countChildren(reqNode);
    
    
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
            max_left_parent = findParentToNodeWithEntry(max_left->getEntry());
            //Set max_left's left subtree equal to max_left_parent's right pointer
            max_left_parent->setRight(max_left->getLeft());
        }
        TreeNode *left_subtree = reqNode->getLeft();                            //reqNode's left subtree
        TreeNode *right_subtree = reqNode->getRight();                          //reqNode's right subtree
        max_left->setLeft(left_subtree);                                        //Making max_left the parent of the left subtree's root
        max_left->setRight(right_subtree);                                      //Making max_left the parent of the right subtree's root
        
        if(parent->getLeft() == reqNode()){                                     //Replacing reqNode with max_left
            parent->setLeft(max_left);
        }
        else{
            parent->setRight(max_left);
        }
        
        reqNode->setLeft(NULL);
        reqNode->setRight(NULL);
        return true;
    }
}

TreeNode *TreeDB::findParentToNodeWithEntry(DBentry* _entry){
    if(root == NULL)    //Empty tree
        return NULL;
    TreeNode *reqNode = root;
    while(reqNode->getEntry() != _entry){
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
    cout<<"Returning this node. Check if it's the left or right child that needs to be deleted\n";

    return reqNode;
}

int TreeDB::countChildren(TreeNode* curr){
    int count = 0;
    cout<<"Counting the number of children for Node with entry \""<<curr->getEntry()->getName()<<"|\"\n";
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

TreeNode *TreeDB::*getRightMost(TreeNode *curr){
    if(curr->getRight() == NULL){
        return curr;
    }
    return getRightMost(curr->getRight());
}
// deletes all the entries in the database.
void TreeDB::clear(){
    //to be implemented later
    deleteTree(root);
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
    if(rhs == NULL)
        return;
    //else, print left, then print rhs, then  print right.
    else{
       // out<<rhs->getRoot()->getLeft(); //Prints the left nodes
        out<<rhs->getRoot();
       // out<<rhs->getRoot()->getRight();
    }
}

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs){                                      //<< overload for TreeNode...basically, we can cout<<currNode in the provios function.
    if(rhs == NULL)
        return; //Don't want to dereference NULL
    //Recurse all the way to the left
    if(rhs->getLeft() != NULL)
        out<<rhs->getLeft();
    out<<rhs->printNode();
    if(rhs->getRight() != NULL)
        out<<rhs->getRight();
    return out;
}   

int main(int argc, char** argv) {

    return 0;
}

