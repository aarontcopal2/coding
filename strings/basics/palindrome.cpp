#include <cassert>
#include <string>

using namespace std;

bool is_palindrome(string &str) {
    int size = str.size();
    int s = 0;
    int e = size - 1;

    while (s < e) {
        while (str[s] == ' ') s++;
        while (str[e] == ' ') e--;
        if (tolower(str[s++]) != tolower(str[e--])) return false;
    }
    return true;
}


int main() {
    string s = "vscode";
    assert(is_palindrome(s) == false);

    s = "malayalam";
    assert(is_palindrome(s) == true);

    s = "malayalam is palindrome";
    assert(is_palindrome(s) == false);

    s = "RaDAr";
    assert(is_palindrome(s) == true);

    s = "ACROBATS STAB ORCA";
    assert(is_palindrome(s) == true);
}