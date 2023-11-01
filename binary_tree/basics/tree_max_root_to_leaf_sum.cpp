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
    if (n == nullptr) return 0;
    int left_sum = tree_max_path(n->left);
    int right_sum = tree_max_path(n->right);
    return max(left_sum, right_sum) + n->val;
}

int main () {
    Node a(5);
    Node b(11);
    Node c(3);
    Node d(4);
    Node e(2);
    Node f(1);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;

    Node *root = &a;
    int max_sum = tree_max_path(root);
    assert(max_sum == 20);
}