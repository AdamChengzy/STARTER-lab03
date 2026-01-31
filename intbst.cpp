// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE
#include "intbst.h"

#include <iostream>
using std::cout;

IntBST::IntBST() : root(nullptr) {}

IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

void IntBST::clear(Node *n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

bool IntBST::insert(int value, Node *n) {
    if (value == n->data) return false;

    if (value < n->data) {
        if (n->left) return insert(value, n->left);
        n->left = new Node(value);
        return true;
    } else {
        if (n->right) return insert(value, n->right);
        n->right = new Node(value);
        return true;
    }
}

void IntBST::printPreOrder() const {
    printPreOrder(root);
    cout << '\n';
}

void IntBST::printPreOrder(Node *n) const {
    if (!n) return;
    cout << n->data << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

void IntBST::printInOrder() const {
    printInOrder(root);
    cout << '\n';
}

void IntBST::printInOrder(Node *n) const {
    if (!n) return;
    printInOrder(n->left);
    cout << n->data << " ";
    printInOrder(n->right);
}

void IntBST::printPostOrder() const {
    printPostOrder(root);
    cout << '\n';
}

void IntBST::printPostOrder(Node *n) const {
    if (!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->data << " ";
}

int IntBST::sum() const {
    return sum(root);
}

int IntBST::sum(Node *n) const {
    if (!n) return 0;
    return n->data + sum(n->left) + sum(n->right);
}

int IntBST::count() const {
    return count(root);
}

int IntBST::count(Node *n) const {
    if (!n) return 0;
    return 1 + count(n->left) + count(n->right);
}

IntBST::Node* IntBST::getNodeFor(int value, Node* n) const {
    if (!n) return nullptr;
    if (value == n->data) return n;
    if (value < n->data) return getNodeFor(value, n->left);
    return getNodeFor(value, n->right);
}

bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != nullptr;
}

IntBST::Node* IntBST::getPredecessorNode(int value) const {
    Node* cur = root;
    Node* pred = nullptr;

    while (cur) {
        if (value > cur->data) {
            pred = cur;
            cur = cur->right;
        } else if (value < cur->data) {
            cur = cur->left;
        } else {
            if (cur->left) {
                Node* t = cur->left;
                while (t->right) t = t->right;
                return t;
            }
            return pred;
        }
    }
    return nullptr;
}

int IntBST::getPredecessor(int value) const {
    Node* p = getPredecessorNode(value);
    return p ? p->data : 0;
}

IntBST::Node* IntBST::getSuccessorNode(int value) const {
    Node* cur = root;
    Node* succ = nullptr;

    while (cur) {
        if (value < cur->data) {
            succ = cur;
            cur = cur->left;
        } else if (value > cur->data) {
            cur = cur->right;
        } else {
            if (cur->right) {
                Node* t = cur->right;
                while (t->left) t = t->left;
                return t;
            }
            return succ;
        }
    }
    return nullptr;
}

int IntBST::getSuccessor(int value) const {
    Node* s = getSuccessorNode(value);
    return s ? s->data : 0;
}

bool IntBST::remove(int value) {
    Node* parent = nullptr;
    Node* cur = root;

    while (cur && cur->data != value) {
        parent = cur;
        if (value < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    if (!cur) return false;

    auto replaceChild = [&](Node* oldChild, Node* newChild) {
        if (!parent) root = newChild;
        else if (parent->left == oldChild) parent->left = newChild;
        else parent->right = newChild;
    };

    if (cur->left && cur->right) {
        Node* predParent = cur;
        Node* pred = cur->left;
        while (pred->right) {
            predParent = pred;
            pred = pred->right;
        }

        cur->data = pred->data;

        Node* predChild = pred->left;
        if (predParent->left == pred) predParent->left = predChild;
        else predParent->right = predChild;

        delete pred;
        return true;
    }

    Node* child = cur->left ? cur->left : cur->right;
    replaceChild(cur, child);
    delete cur;
    return true;
}

