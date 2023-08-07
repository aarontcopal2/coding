#include <cassert>
#include <string>
#include <unordered_map>

using namespace std;
typedef unsigned long long ull;

ull gridTraveller(int m, int n, unordered_map<string, ull> &memo) {
    if (m == 0 || n == 0) return 0;
    if (m == 1 && n == 1) return 1;
    if (m > n) {
        // The memo values of x,y and y,x will be the same.
        // To avoid duplicate memo keys, we will ensure that
        // m <= n
        int tmp = m;
        m = n;
        n = tmp;
    }
    string key = to_string(m) + "," + to_string(n);
    if (memo.find(key) != memo.end()) return memo[key];
    memo[key] = gridTraveller(m-1, n, memo) + gridTraveller(m, n-1, memo);
    return memo[key];
}

int main () {
    unordered_map<string, ull> memo = {};
    ull result = gridTraveller(1, 1, memo);
    assert(result == 1);
    
    result = gridTraveller(2, 3, memo);
    assert(result == 3);

    result = gridTraveller(3, 2, memo);
    assert(result == 3);

    result = gridTraveller(3, 3, memo);
    assert(result == 6);

    result = gridTraveller(18, 18, memo);
    assert(result == 2333606220);
}