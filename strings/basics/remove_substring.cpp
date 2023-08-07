#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <stack>

#define ASSERT(left,operator,right) { if(!((left) operator (right))) {\
    std::cerr << "ASSERT FAILED at line " << __LINE__ \
        << ", " << #left << " " << #operator << " " <<  #right << "\n"\
        << "LHS" << " = " << (left) << "; " << "RHS" << " = " << (right) << "\n"; }\
}

using namespace std;

string remove_all_occurence_of_substring (const string &str, const string &substr) {
    // If a substring is removed, the chars
    // before and after it can combine to form another substring.
    // Brute force will require iterating through the string multiple times
    // till no occurence of substring is found.
    if (substr == "") return str;
    stack<char> s;

    for (const char c: str) {
        s.push(c);

        if (s.size() < substr.size()) continue;
        for (int i=substr.size()-1; i>=0; i--) {
            if (substr[i] == s.top()) {
                s.pop();
            } else {
                for (int j=i+1; j<substr.size(); j++) {
                    s.push(substr[j]);
                }
                break;
            }
        }
    }

    string result(s.size(), ' ');
    for (int i=s.size()-1; i>=0; i--) {
        result[i] = s.top();
        s.pop();
    }
    return result;
}


int main() {
    string str = "abcdefgh";
    string result = remove_all_occurence_of_substring(str, "cd");
    ASSERT(result, ==, "abefgh");

    str = "xaaaaaabbbbbby";
    result = remove_all_occurence_of_substring(str, "ab");
    ASSERT(result, ==, "xy");

    str = "gjzgbpggjzgbpgsvpwdk";
    result = remove_all_occurence_of_substring(str, "gjzgbpg");
    ASSERT(result, ==, "svpwdk");
}