#include <cassert>
#include <unordered_map>
#include <vector>

using namespace std;

bool canSum (int targetSum, const vector<int> &numbers, unordered_map<int, bool> &memo) {
    // Elements of numbers array can be used as many times as needed.
    // All elements of numbers array are non-negative.
    if (memo.find(targetSum) != memo.end()) return memo[targetSum];
    if (targetSum == 0) return true;
    if (targetSum < 0) return false;

    bool result;
    for (int num: numbers) {
        result = canSum(targetSum - num, numbers, memo);
        if (result == true) {
            memo[targetSum] = true;
            return memo[targetSum];
        }
    }
    memo[targetSum] = false;
    return memo[targetSum];
}

int main() {
    unordered_map<int, bool> memo;
    bool result = canSum(7, {5, 3, 4, 7}, memo);
    assert(result == true);
    memo.clear();

    result = canSum(7, {2, 4}, memo);
    assert(result == false);
    memo.clear();

    result = canSum(8, {2, 3, 5}, memo);
    assert(result == true);
    memo.clear();

    result = canSum(300, {7, 14}, memo);
    assert(result == false);
    memo.clear();
}