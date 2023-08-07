#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
typedef unsigned int uint;

uint countConstruct(string target, const vector<string> &wordBank, unordered_map<string, uint> &memo) {
    // countConstruct should return number of ways in which target can be
    // constructed with wordBank.
    // Elements of wordBank can be reused to create target.
    if (memo.find(target) != memo.end()) return memo[target];
    if (target == "") return 1;

    uint total_ways = 0;
    for (string word: wordBank) {
        if (target.compare(0, word.size(), word) == 0) {
            // word is a prefix of target.
            uint ways = countConstruct(target.substr(word.size(), string::npos) , wordBank, memo);
            total_ways += ways;
        }
    }
    memo[target] = total_ways;
    return memo[target];
}

int main() {
    unordered_map<string, uint> memo;
    uint result = countConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}, memo);
    assert(result == 1);
    memo.clear();

    result = countConstruct("purple", {"purp", "p", "ur", "le", "purpl"}, memo);
    assert(result == 2);
    memo.clear();

    result = countConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, memo);
    assert(result == 0);
    memo.clear();

    result = countConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, memo);
    assert(result == 4);
    memo.clear();

    result = countConstruct("eeeeeeeeeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}, memo);
    assert(result == 0);
    memo.clear();
}