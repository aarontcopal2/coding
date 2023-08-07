#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
 
unordered_map<int, vector<int>> create_graph(vector<pair<int, int>> &edges) {
	unordered_map<int, vector<int>> graph;
 
	for (pair<int, int> e: edges) {
		int i = e.first;
        int j = e.second;
        graph[i].push_back(j);
        graph[j].push_back(i);
	}
	return graph;
}
 
bool explore(const int src, unordered_map<int, vector<int>> &graph, unordered_set<int> &visited) {
	// returns 0 if component is visited, else returns 1.
	if (visited.find(src) != visited.end()) return 0;
	visited.insert(src);
 
	const vector<int> &neighbors = graph[src];
 
	for (const int dst: neighbors) {
		explore(dst, graph, visited);
	}
	return 1;
}
 
int connected_components(const int n, unordered_map<int, vector<int>> &graph) {
	unordered_set<int> visited;
	int count = 0;
 
	// iterate over graph keys.
	for (int i=1; i<=n; i++) {
		count += explore(i, graph, visited);
	}
 
	return count;
}
 
int main(){
	vector<pair<int, int>> edges = {
						pair(1, 2),
						pair(2, 3),
						pair(2, 4),
						pair(3, 5),
						pair(6, 7)
					};
	
	unordered_map<int, vector<int>> graph = create_graph(edges);
 
	assert(connected_components(8, graph) == 3);
}