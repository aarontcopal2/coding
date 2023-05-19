// https://leetcode.com/problems/snakes-and-ladders/
#include <cassert>
#include <stack>
#include <stdio.h>      // printf
#include <unordered_map>
#include <vector>

struct move {
    int pos;
    int steps;
    // For debug purposes
    int prev_pos;
};

class Solution {
public:
    int snakesAndLadders(const std::vector<std::vector<int>>& board) {
        // Return the least number of moves required to reach the square n2.
        // Squares 1 and n^2 do not have a snake or ladder.

        std::stack<move> moves;
        std::unordered_map<int, int> min_steps;
        int CANNOT_REACH_LAST_POS = -1;

        int last_pos = board.size() * board.size() -1;
        min_steps[last_pos] = INT_MAX;
        move start_pos = {0, 0, -1};
        moves.push(start_pos);

        while (!moves.empty()) {
            // Note that you only take a snake or ladder at most once per move.
            // If the destination to a snake or ladder is the start of
            // another snake or ladder,
            // you do not follow the subsequent snake or ladder.
            // For example, suppose the board is [[-1,4],[-1,3]],
            // and on the first move, your destination square is 2.
            // You follow the ladder to square 3,
            // but do not follow the subsequent ladder to 4.
            move curr_move = moves.top(); moves.pop();
            // printf("pos: %d, steps: %d, prev_pos: %d\n", curr_move.pos, curr_move.steps, curr_move.prev_pos);

            if (min_steps.find(curr_move.pos) != min_steps.end()) {
                if (min_steps[curr_move.pos] <= curr_move.steps) {
                    continue;
                }
                else {
                    min_steps[curr_move.pos] = curr_move.steps;
                }
            } else {
                min_steps[curr_move.pos] = curr_move.steps;
            }

            for (int i=1; i<=6; i++) {
                int newPos = curr_move.pos+i;
                // Ignore moves outside the board.
                if (newPos > last_pos) continue;
                if (hasJump(board, newPos)) {
                    int r, c;
                    get2DCoordinatesOfPos(newPos, board.size(), r, c);
                    // The jump positions are 1-indexed.
                    // Since our datastructure is 0-indexed,
                    // We substract the jump position by 1. 
                    newPos = board[r][c] - 1;
                }
                moves.push({newPos, curr_move.steps+1, curr_move.pos});
            }
        }

        // If it is not possible to reach the last square, return -1.
        return (min_steps[last_pos] != INT_MAX) ? min_steps[last_pos] : CANNOT_REACH_LAST_POS;
    }

private:
    bool hasJump(const std::vector<std::vector<int>>& board, const int &pos) {
        int r, c;
        get2DCoordinatesOfPos(pos, board.size(), r, c);
        return (board[r][c] > 0);
    }

    void get2DCoordinatesOfPos(const int &pos, const int &n, int &r, int &c) {
        // The 2D co-ordinates are returned through reference params r & c. 
        r = pos / n;
        r = n-r-1;
        c = pos % n;
        // In Boustrophedon style boards, row n-1 has pos 0 to n-1.
        // When n is even,
        //    moves in odd rows are made from left to right.
        //    moves in even rows are made from right to left.
        // Vice versa when n is odd
        bool left_moving_row = (r%2==0 && n%2==0) || (r%2==1 && n%2==1);
        if (left_moving_row) {
            c = n-c-1;
        }
    }
};

void assert_helper(Solution &s, const std::vector<std::vector<int>>& board, int expected) {
    int min_steps = s.snakesAndLadders(board);
    // printf("min_steps: %d\n", min_steps);
    assert(min_steps == expected);
}

int main() {
    Solution s;
    std::vector<std::vector<int>> board = {{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,35,-1,-1,13,-1},{-1,-1,-1,-1,-1,-1},{-1,15,-1,-1,-1,-1}};
    assert_helper(s, board, 4);

    board = {{-1,-1,-1},{-1,9,8},{-1,8,9}};
    assert_helper(s, board, 1);

    board = {{1,1,-1},{1,1,1},{-1,1,1}};
    assert_helper(s, board, -1);

    board = {{-1,1,2,-1},{2,13,15,-1},{-1,10,-1,-1},{-1,6,2,8}};
    assert_helper(s, board, 2);
}