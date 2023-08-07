#include <cassert>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<char> dfs(unordered_map<char, vector<char>> &graph, char src) {
    vector<char> result;
    unordered_set<char> visited;
    stack<char> q;
    q.push(src);

    while (!q.empty()) {
        char curr = q.top();
        q.pop();
        if (visited.find(curr) != visited.end()) {
            continue;
        }
        visited.insert(curr);

        result.push_back(curr);

        for (char neighbor: graph[curr]) {
            q.push(neighbor);
        }
    }
    return result;
}

void dfs_rec(unordered_map<char, vector<char>> &graph, unordered_set<char> &visited, vector<char> &result, char src) {
    if (visited.find(src) != visited.end()) {
        return;
    }
    visited.insert(src);

    result.push_back(src);

    for (char neighbor: graph[src]) {
        dfs_rec(graph, visited, result, neighbor);
    }
}

void assert_helper(vector<char> actual, vector<char> expected) {
    assert(actual == expected);
}

int main () {
    unordered_map<char, vector<char>> graph = {
        {'a', {'b', 'c'}},
        {'b', {'d'}},
        {'c', {'e'}},
        {'d', {'f'}},
        {'e', {}},
        {'f', {}},
    };

    vector<char> expected = {'a', 'c', 'e', 'b', 'd', 'f'};
    vector<char> result = dfs(graph, 'a');
    assert_helper(result, expected);
    
    unordered_set<char> visited;
    result.clear();
    // The DFS order changes when we use recursion mechanism instead of stack.
    // This is because stack pushes all neighbors to stack before picking the element,
    // hence the last neigbor is processed first. 
    // whereas in recursion, we immediately start processing the first neigbor.
    expected = {'a', 'b', 'd', 'f', 'c', 'e'};
    dfs_rec(graph, visited, result, 'a');
    assert_helper(result, expected);
}