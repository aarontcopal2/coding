#include <string>
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool exist(const std::vector<std::vector<char>>& board, const std::string &word) {
        // Save indices of all letters and their corresponding position in the board.
        int m = board.size();
        int n = board[0].size();
        char start_char = word[0];

        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                char c = board[i][j];
                if (c == start_char) {
                    start_loc.insert(std::pair(i,j));
                }
            }
        }
        
        for (std::pair<int, int> pos: start_loc) {
            // init the visited array to the size of board.
            std::vector<std::vector<bool>> visited;
            bool found = rec_search(board, word, pos, 1, visited);
            if (found) {
                return true;
            }
        }
        return false;
    }

private:
    bool rec_search(const std::vector<std::vector<char>>& board, const std::string &word, 
                    std::pair<int, int> &pos, const int &idx, std::vector<std::vector<bool>> &visited) {
        if (idx == word.size()) {
            // Word found.
            return true;
        }
        // for (dir: directions)
            // if word[idx] is in board[pos + dir], continue the recursive search
        // else return false
    }

    std::unordered_set<std::pair<int, int>> start_loc;
    std::unordered_set<std::pair<int, int>> directions = {};
};

int main() {
    Solution s;
    std::vector<std::vector<int>> board = {{"A","B","C","E"},{"S","F","C","S"},{"A","D","E","E"}};   
    s.exist(board, "SEE");
}