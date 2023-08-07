#include <cassert>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> bestSum (int targetSum, const vector<int> &numbers, unordered_map<int, vector<int>> &memo) {
    // The function should return shortest combination of elements that add up to exactly
    // the targetSum. If there is no combination that adds up to the targetSum,
    // then return null. If there is a tie for the shortest combination,
    // you may return any of the shortest.
    // If there are multiple combinations possible, you may return any single one.
    if (memo.find(targetSum) != memo.end()) return memo[targetSum];
    if (targetSum == 0) return {0};
    if (targetSum < 0) return {};

    vector<int> shortest_result = {};
    for (int num: numbers) {
        vector<int> result = bestSum(targetSum - num, numbers, memo);
        if (result.size() != 0) {
            if (result.size() == 1 && result[0] == 0) {
                result[0] = num;
            } else {
                result.push_back(num);
            }
            if (shortest_result.empty() || result.size() < shortest_result.size()) {
                shortest_result = result;
            }
        }
    }
    memo[targetSum] = shortest_result;
    return shortest_result;
}

int main() {
    unordered_map<int, vector<int>> memo;
    vector<int> result = bestSum(7, {5, 3, 4, 7}, memo);
    vector<int> expected = {7};
    assert(result == expected);
    memo.clear();

    result = bestSum(7, {2, 4}, memo);
    expected = {};
    assert(result == expected);
    memo.clear();

    result = bestSum(8, {2, 3, 5}, memo);
    expected = {5, 3};
    assert(result == expected);
    memo.clear();

    result = bestSum(8, {1, 4, 5}, memo);
    expected = {4, 4};
    assert(result == expected);
    memo.clear();

    result = bestSum(300, {7, 14}, memo);
    expected = {};
    assert(result == expected);
    memo.clear();

    result = bestSum(100, {1, 2, 5, 25}, memo);
    expected = {25, 25, 25, 25};
    assert(result == expected);
    memo.clear();
}