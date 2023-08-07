#include <cassert>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> howSum (int targetSum, const vector<int> &numbers, unordered_map<int, vector<int>> &memo) {
    // The function should return any combination of elements that add up to exactly
    // the targetSum. If there is no combination that adds up to the targetSum,
    // then return null.
    // If there are multiple combinations possible, you may return any single one.
    if (memo.find(targetSum) != memo.end()) return memo[targetSum];
    if (targetSum == 0) return {0};
    if (targetSum < 0) return {};

    for (int num: numbers) {
        vector<int> result = howSum(targetSum - num, numbers, memo);
        if (result.size() != 0) {
            if (result.size() == 1 && result[0] == 0) {
                result[0] = num;
            } else {
                result.push_back(num);
            }
            memo[targetSum] = result;
            return memo[targetSum];
        }
    }
    memo[targetSum] = {};
    return {};
}

int main() {
    unordered_map<int, vector<int>> memo;
    vector<int> result = howSum(7, {5, 3, 4, 7}, memo);
    vector<int> expected = {4, 3};
    assert(result == expected);
    memo.clear();

    result = howSum(7, {2, 4}, memo);
    expected = {};
    assert(result == expected);
    memo.clear();

    result = howSum(8, {2, 3, 5}, memo);
    expected = {2, 2, 2, 2};
    assert(result == expected);
    memo.clear();

    result = howSum(300, {7, 14}, memo);
    expected = {};
    assert(result == expected);
    memo.clear();
}