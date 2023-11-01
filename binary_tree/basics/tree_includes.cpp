#include <cassert>
#include <iostream>
#include <queue>

using namespace std;

class Node {
public:
    Node *left;
    Node *right;
    char val;

    Node(char c): val(c) {
        left = nullptr;
        right = nullptr;
    }
};

bool includes(Node *n, char target) {
    if (n == nullptr) return false;
    if (n->val == target) return true;

    return includes(n->left, target) ||
            includes(n->right, target);

}

int main () {
    Node a('a');
    Node b('b');
    Node c('c');
    Node d('d');
    Node e('e');
    Node f('f');
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;

    Node *root = &a;
    bool found = includes(root, 'e');
    assert(found == true);

    found = includes(root, 'x');
    assert(found == false);
}