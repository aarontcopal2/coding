#include <cassert>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<char> bfs(unordered_map<char, vector<char>> &graph, char src) {
    vector<char> result;
    unordered_set<char> visited;
    queue<char> q;
    q.push(src);

    while (!q.empty()) {
        char curr = q.front();
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

    vector<char> result = bfs(graph, 'a');
    vector<char> expected = {'a', 'b', 'c', 'd', 'e', 'f'};
    assert_helper(result, expected);
}