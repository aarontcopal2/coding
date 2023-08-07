#include <cassert>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_map<char, vector<char>> create_graph(vector<pair<char, char>> &edges) {
    unordered_map<char, vector<char>> graph;
    
    for (pair<char, char> e: edges) {
        int i = e.first;
        int j = e.second;
        graph[i].push_back(j);
        graph[j].push_back(i);
    }

    return graph;
}

bool undirected_path(unordered_map<char, vector<char>> &graph, unordered_set<char> &visited, char src, char dst) {
    if (src == dst) return true;
    if (visited.find(src) != visited.end()) return false;

    visited.insert(src);

    for (char neighbor: graph[src]) {
        bool found_path = undirected_path(graph, visited, neighbor, dst);
        if (found_path) return true;
    }
    return false;
}

int main () {
    vector<pair<char, char>> edges = {
        {'i', 'j'},
        {'k', 'i'},
        {'m', 'k'},
        {'k', 'l'},
        {'o', 'n'},        
    };

    unordered_map<char, vector<char>> graph = create_graph(edges);

    unordered_set<char> visited;
    bool result = undirected_path(graph, visited, 'j', 'm');
    assert(result == true);

    result = undirected_path(graph, visited, 'o', 'n');
    assert(result == true);

    result = undirected_path(graph, visited, 'l', 'n');
    assert(result == false);
}