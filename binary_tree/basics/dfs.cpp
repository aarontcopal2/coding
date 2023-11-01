#include <iostream>

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

void bfs(Node *n) {
    if (n == nullptr) return;
    printf("%c\n", n->val);
    bfs(n->left);
    bfs(n->right);
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
    bfs(root);
}