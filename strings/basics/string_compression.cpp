#include <algorithm>
#include <iostream>
#include <string>

#define ASSERT(left,operator,right) { if(!((left) operator (right))) {\
    std::cerr << "ASSERT FAILED at line " << __LINE__ \
        << ", " << #left << " " << #operator << " " <<  #right << "\n"\
        << "LHS" << " = " << (left) << "; " << "RHS" << " = " << (right) << "\n"; }\
}

using namespace std;

string print_char_count (const int count, const char c) {
    if (count > 1) {
        return c + to_string(count);
    } else if (count == 1) {
        return string(1, c);
    }
    // If count == 0
    return "";
}

string compress(const string &str) {
    string result;
    char curr_char;
    int count = 0;
    for (const char &c: str) {
        if (c != curr_char) {
            result += print_char_count (count, curr_char);
            curr_char = c;
            count = 1;
        } else {
            count++;
        }
    }
    result += print_char_count (count, curr_char);

    return result;
}


int main() {
    string s = "vscode";
    string result = compress(s);
    ASSERT(result, ==, "vscode");

    s = "aabbcccc";
    result = compress(s);
    ASSERT(result, ==, "a2b2c4");
}