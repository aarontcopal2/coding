#include <cassert>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

stack<string> split(const std::string &s, char delim) {
    // For our convenience, we are splitting the string and 
    // returning the result in a stack.
    stack<string> result;

    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        result.push(item);
    }
    return result;
}

string reverse(const string &str) {
    stack <string> tokens = split(str, ' ');
    string reversed_str;
    while (!tokens.empty()) {
        if (reversed_str.size() > 0) reversed_str += ' ';
        reversed_str += tokens.top();
        tokens.pop();
    }
    return reversed_str;
}

int main() {
    string s = "the sky is blue";
    string expected = "blue is sky the";
    assert(reverse(s) == expected);

    s = "blue";
    expected = "blue";
    assert(reverse(s) == expected);
}