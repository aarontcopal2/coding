#include <algorithm>
#include <cassert>
#include <string>

using namespace std;

void reverse(string &str) {
    int size = str.size();
    int s = 0;
    int e = size - 1;

    while (s < e) {
        swap(str[s++], str[e--]);
    }
}


int main() {
    string s = "vscode";
    reverse(s);
    assert(s == "edocsv");

    s = "malayalam";
    reverse(s);
    assert(s == "malayalam");

    s = "malayalam is palindrome";
    reverse(s);
    assert(s == "emordnilap si malayalam");
}