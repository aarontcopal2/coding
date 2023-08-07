#include <algorithm>    // std::reverse
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<string>> allConstructRecursive(string target, const vector<string> &wordBank, unordered_map<string, vector<vector<string>>> &memo) {
    // allConstruct should a 2D array containing all the ways 
    // in which target can be constructed with elements of wordBank.
    // Elements of wordBank can be reused to create target.
    if (memo.find(target) != memo.end()) return memo[target];
    if (target == "") return {{}};

    vector<vector<string>> all_ways = {};
    for (string word: wordBank) {
        if (target.compare(0, word.size(), word) == 0) {
            // word is a prefix of target.
            vector<vector<string>> ways = allConstructRecursive(target.substr(word.size(), string::npos) , wordBank, memo);
            if (!ways.empty()) {
                for (vector<string>  way: ways) {
                    // Append current word.
                    way.push_back(word);
                    all_ways.push_back(way);
                }
            }
        }
    }
    memo[target] = all_ways;
    return memo[target];
}

vector<vector<string>> allConstruct(string target, const vector<string> &wordBank) {
    unordered_map<string, vector<vector<string>>> memo;
    vector<vector<string>> all_ways = allConstructRecursive(target, wordBank, memo);
    for (vector<string>  &way: all_ways) {
        reverse(way.begin(), way.end());
    }
    return all_ways;
}

int main() {
    vector<vector<string>> result = allConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"});
    vector<vector<string>> expected = {{"abc", "def"}};
    assert(result == expected);

    result = allConstruct("purple", {"purp", "p", "ur", "le", "purpl"});
    expected = {{"purp", "le"}, {"p", "ur", "p", "le"}};
    assert(result == expected);

    result = allConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"});
    expected = {};
    assert(result == expected);

    result = allConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"});
    expected = {
        {"enter", "a", "p", "ot", "ent", "p", "ot"},
        {"enter", "a", "p", "ot", "ent", "p", "o", "t"},
        {"enter", "a", "p", "o", "t", "ent", "p", "ot"},
        {"enter", "a", "p", "o", "t", "ent", "p", "o", "t"}
    };
    assert(result == expected);

    result = allConstruct("eeeeeeeeeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"});
    expected = {};
    assert(result == expected);
}