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

string remove_adjacent_duplicates (const string &str) {
    stack<char> s;

    for (const char c: str) {
        if (!s.empty() && s.top() == c) {
            s.pop();
            continue;
        }
        s.push(c);
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
    string result = remove_adjacent_duplicates(str);
    ASSERT(result, ==, "abcdefgh");

    str = "xaaaaaabbbbbby";
    result = remove_adjacent_duplicates(str);
    ASSERT(result, ==, "xy");

    str = "gjzgbpggjzgbpgsvpwdk";
    result = remove_adjacent_duplicates(str);
    ASSERT(result, ==, "gjzgbpjzgbpgsvpwdk");
}