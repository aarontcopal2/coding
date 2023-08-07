#include <cassert>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int explore(unordered_map<int, vector<int>> &graph, unordered_set<int> &visited, int src) {
    if (visited.find(src) != visited.end()) return 0;
    
    visited.insert(src);
    int count = 1;

    for (int neighbor: graph[src]) {
        count += explore(graph, visited, neighbor);
    }
    return count;
}

int largest_component(unordered_map<int, vector<int>> &graph) {
    unordered_set<int> visited;
    int max_size = INT_MIN;
    for(auto it = graph.begin(); it != graph.end(); ++it) {
        int src = it->first;
        // dfs on node, and return size of the connected component
        int size = explore(graph, visited, src);
        max_size = max(max_size, size);
    }
    return max_size;
}

int main () {
    unordered_map<int, vector<int>> graph = {
        {0, {8, 1, 5}},
        {1, {0}},
        {5, {0, 8}},
        {8, {0, 5}},
        {2, {3, 4}},
        {3, {2, 4}},
        {4, {3, 2}},
    };

    unordered_set<char> visited;
    int result = largest_component(graph);
    assert(result == 4);
}