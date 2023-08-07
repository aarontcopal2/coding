#include <cassert>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int explore(const vector<vector<char>> &grid, unordered_set<string> &visited, int i, int j) {
    // perform dfs operation on grid.
    bool out_of_bounds = (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size());
    if (out_of_bounds) return 0;

    if (grid[i][j] == 'W') return 0;

    string idx = to_string(i) + "," + to_string(j);
    if (visited.find(idx) != visited.end()) return 0;
    visited.insert(idx);

    explore(grid, visited, i-1, j);
    explore(grid, visited, i, j-1);
    explore(grid, visited, i+1, j);
    explore(grid, visited, i, j+1);
    return 1;
}

int min_island_size(const vector<vector<char>> &grid) {
    int count = 0;
    unordered_set<string> visited;

    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            count += explore(grid, visited, i, j);
        }
    }
    return count;
}

int main() {
    vector<vector<char>> grid = {
        {'L','L','L','L','W'},
        {'L','L','W','L','W'},
        {'L','L','W','W','W'},
        {'W','W','W','W','W'}
    };
    int count = min_island_size(grid);
    assert(count == 1);

    grid = {
        {'L','L','W','W','W'},
        {'L','L','W','W','W'},
        {'W','W','L','W','W'},
        {'W','W','W','L','L'}
    };
    count = min_island_size(grid);
    assert(count == 3);
}