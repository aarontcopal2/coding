#include <cassert>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

bool has_path(unordered_map<char, vector<char>> &graph, unordered_set<char> &visited, char src, char dst) {
    if (src == dst) return true;
    if (visited.find(src) != visited.end()) return false;

    visited.insert(src);

    for (char neighbor: graph[src]) {
        bool found_path = has_path(graph, visited, neighbor, dst);
        if (found_path) return true;
    }
    return false;
}

int main () {
    unordered_map<char, vector<char>> graph = {
        {'f', {'g', 'i'}},
        {'g', {'h'}},
        {'h', {}},
        {'i', {'g', 'k'}},
        {'j', {'i'}},
        {'k', {}},
    };

    unordered_set<char> visited;
    bool result = has_path(graph, visited, 'f', 'k');
    assert(result == true);

    result = has_path(graph, visited, 'j', 'f');
    assert(result == false);
}