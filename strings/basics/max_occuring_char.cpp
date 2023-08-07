#include <cassert>
#include <string>
#include <unordered_map>

using namespace std;

bool chars_to_be_ignored(char c) {
    return (c == ' ');
}

char max_occuring_char(const string &str) {
    unordered_map<char, int> freq;
    int max_freq = INT_MIN;
    char max_char;

    for (const char c: str) {
        if (chars_to_be_ignored(c)) continue;

        if (freq.find(c) != freq.end()) {
            freq[c]++;
        } else {
            freq[c] = 1;
        }
        if (freq[c] > max_freq) {
            max_freq = freq[c];
            max_char = c;
        }
    }
    return max_char;
}

int main() {
    string s = "the sky is blue";
    char expected = 's';
    assert(max_occuring_char(s) == expected);

    s = "blue";
    expected = 'b';
    assert(max_occuring_char(s) == expected);
}