// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
clear(root);
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    }
    return insert(value, root); // REPLACE THIS NON-SOLUTION
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->data) return false;

    if (value < n->data) {
        if (n->left) return insert(value, n->left);
        n->left = new Node(value);
        return true;
    } else { // value > n->data
        if (n->right) return insert(value, n->right);
        n->right = new Node(value);
        return true;
    }// REPLACE THIS NON-SOLUTION
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
    cout << endl; // IMPLEMENT HERE
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (!n) return;
    cout << n->data << " ";
    printPreOrder(n->left);
    printPreOrder(n->right); // IMPLEMENT HERE
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
    cout << endl; // IMPLEMENT HERE
}
void IntBST::printInOrder(Node *n) const {
    if (!n) return;
    printInOrder(n->left);
    cout << n->data << " ";
    printInOrder(n->right); // IMPLEMENT HERE
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
  printPostOrder(root);
    cout << endl; // IMPLEMENT HERE
}

void IntBST::printPostOrder(Node *n) const {
    if (!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->data << " ";// IMPLEMENT HERE
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root); // REPLACE THIS NON-SOLUTION
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (!n) return 0;
    return n->data + sum(n->left) + sum(n->right);// REPLACE THIS NON-SOLUTION
}

// return count of values
int IntBST::count() const {
    return count(root);// REPLACE THIS NON-SOLUTION
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (!n) return 0;
    return 1 + count(n->left) + count(n->right);// REPLACE THIS NON-SOLUTION
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (!n) return nullptr;
    if (value == n->data) return n;
    if (value < n->data) return getNodeFor(value, n->left);
    return getNodeFor(value, n->right);// REPLACE THIS NON-SOLUTION
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != nullptr; // REPLACE THIS NON-SOLUTION
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* cur = root;
    Node* pred = nullptr;

    while (cur) {
        if (value <= cur->data) {
            cur = cur->left;
        } else { 
            pred = cur;
            cur = cur->right;
        }
    }
    return pred; // REPLACE THIS NON-SOLUTION
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* p = getPredecessorNode(value);
    return p ? p->data : 0; // REPLACE THIS NON-SOLUTION
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
     Node* cur = root;
    Node* succ = nullptr;

    while (cur) {
        if (value >= cur->data) {
            cur = cur->right;
        } else { // value < cur->data, cur could be successor
            succ = cur;
            cur = cur->left;
        }
    }
    return succ;// REPLACE THIS NON-SOLUTION
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* s = getSuccessorNode(value);
    return s ? s->data : 0; // REPLACE THIS NON-SOLUTION
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    bool removed = false;
    root = removeHelper(root, value, removed);
    return removed; // REPLACE THIS NON-SOLUTION
}
