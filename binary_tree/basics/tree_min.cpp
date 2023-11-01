#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

class Node {
public:
    Node *left;
    Node *right;
    int val;

    Node(int c): val(c) {
        left = nullptr;
        right = nullptr;
    }
};

int tree_max_path (Node *n) {
    if (n == nullptr) return INT_MAX;
    return min({tree_max_path(n->left), n->val, tree_max_path(n->right)});
}

int main () {
    Node a(3);
    Node b(11);
    Node c(4);
    Node d(4);
    Node e(-2);
    Node f(1);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;

    Node *root = &a;
    int min = tree_max_path(root);
    assert(min == -2);
}