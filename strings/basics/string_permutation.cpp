#include <algorithm>
#include <iostream>
#include <string>
#include <queue>

#define ASSERT(left,operator,right) { if(!((left) operator (right))) {\
    std::cerr << "ASSERT FAILED at line " << __LINE__ \
        << ", " << #left << " " << #operator << " " <<  #right << "\n"\
        << "LHS" << " = " << (left) << "; " << "RHS" << " = " << (right) << "\n"; }\
}

typedef unsigned int uint;

using namespace std;

uint idx(char c) {
    return c - 'a';
}

bool checkInclusion(const string &s1, const string &s2) {
    // Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
    // In other words, return true if one of s1's permutations is the substring of s2.
    // 1 <= s1.length, s2.length <= 104
    // s1 and s2 consist of lowercase English letters.
    if (s1.size() > s2.size()) return false;
    
    vector<uint> expected_freq (26, 0);
    vector<uint> actual_freq (26, 0);

    for (int i=0; i<s1.size(); i++) {
        expected_freq[idx(s1[i])]++;
        actual_freq[idx(s2[i])]++;
    }
    for (int i=s1.size(); i<s2.size(); i++) {
        if (actual_freq == expected_freq) return true;
        actual_freq[idx(s2[i-s1.size()])]--;
        actual_freq[idx(s2[i])]++;
    }
    return (actual_freq == expected_freq);
}

int main() {
    string s = "vscode";
    bool result = checkInclusion("ab", "eidbaooo");
    ASSERT(result, ==, true);

    s = "aabbcccc";
    result = checkInclusion("ab", "eidboaoo");
    ASSERT(result, ==, false);
}