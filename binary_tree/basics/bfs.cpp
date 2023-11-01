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

vector<char> bfs(Node *root) {
    vector<char> result;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node *n = q.front();
        q.pop();
        if (n == nullptr) continue;
        result.push_back(n->val);
        q.push(n->left);
        q.push(n->right);
    }
    return result;
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
    vector<char> result = bfs(root);
    vector<char> expected = {'a', 'b', 'c', 'd', 'e', 'f'};
    assert(result == expected);
}