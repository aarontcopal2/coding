#include <cassert>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int explore_size(const vector<vector<char>> &grid, unordered_set<string> &visited, int i, int j) {
    // perform dfs operation on grid.
    bool out_of_bounds = (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size());
    if (out_of_bounds) return 0;

    if (grid[i][j] == 'W') return 0;

    string idx = to_string(i) + "," + to_string(j);
    if (visited.find(idx) != visited.end()) return 0;
    visited.insert(idx);

    int size = 1;
    size += explore_size(grid, visited, i-1, j);
    size += explore_size(grid, visited, i, j-1);
    size += explore_size(grid, visited, i+1, j);
    size += explore_size(grid, visited, i, j+1);
    return size;
}

int min_island_size(const vector<vector<char>> &grid) {
    // We can assume that atleast one island exists.
    int min_size = INT_MAX;
    unordered_set<string> visited;

    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            int size = explore_size(grid, visited, i, j);
            if (size != 0) min_size = min(min_size, size);
        }
    }
    
    return min_size;
}

int main() {
    vector<vector<char>> grid = {
        {'L','L','L','L','W'},
        {'L','L','W','L','W'},
        {'L','L','W','W','W'},
        {'W','W','W','W','W'}
    };
    int min_size = min_island_size(grid);
    assert(min_size == 9);

    grid = {
        {'L','L','W','W','W'},
        {'L','L','W','W','W'},
        {'W','W','L','W','W'},
        {'W','W','W','L','L'}
    };
    min_size = min_island_size(grid);
    assert(min_size == 1);
}