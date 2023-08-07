#include <cassert>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define PATH_NOT_FOUND -1

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

int shortest_path(unordered_map<char, vector<char>> &graph, char src, char dst) {
    // We have to use BFS to find the shortest path
    unordered_set<char> visited;

    queue<pair<char, int>> q;
    q.push({src, 0});
    while (!q.empty()) {
        pair<char, int> curr = q.front();
        q.pop();
        if (visited.find(curr.first) != visited.end()) continue;
        visited.insert(curr.first);

        if (curr.first == dst) return curr.second;

        for (char neighbor: graph[curr.first]) {
            q.push({neighbor, curr.second + 1});
        }
    }

    return PATH_NOT_FOUND;
}

int main () {
    vector<pair<char, char>> edges = {
        {'w', 'x'},
        {'x', 'y'},
        {'z', 'y'},
        {'z', 'v'},
        {'w', 'v'},        
    };

    unordered_map<char, vector<char>> graph = create_graph(edges);

    
    int result = shortest_path(graph, 'w', 'z');
    assert(result == 2);

    result = shortest_path(graph, 'w', 'x');
    assert(result == 1);

    result = shortest_path(graph, 'w', 't');
    assert(result == PATH_NOT_FOUND);
}