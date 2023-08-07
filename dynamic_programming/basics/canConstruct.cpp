#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool canConstruct(string target, const vector<string> &wordBank, unordered_map<string, bool> &memo) {
    // canConstruct should return bool value denoting if target can be
    // constructed with wordBank.
    // Elements of wordBank can be reused to create target.
    if (memo.find(target) != memo.end()) return memo[target];
    if (target == "") return true;

    for (string word: wordBank) {
        if (target.compare(0, word.size(), word) == 0) {
            // word is a prefix of target.
            bool result = canConstruct(target.substr(word.size(), string::npos) , wordBank, memo);
            if (result == true) {
                memo[target] = true;
                return memo[target];
            }
        }
    }
    memo[target] = false;
    return memo[target];
}

int main() {
    unordered_map<string, bool> memo;
    bool result = canConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}, memo);
    assert(result == true);
    memo.clear();

    result = canConstruct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, memo);
    assert(result == false);
    memo.clear();

    result = canConstruct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, memo);
    assert(result == true);
    memo.clear();

    result = canConstruct("eeeeeeeeeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}, memo);
    assert(result == false);
    memo.clear();
}