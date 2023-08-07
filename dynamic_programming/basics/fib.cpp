#include <cassert>
#include <iostream>
#include <unordered_map>

using namespace std;

long long fib (int n, unordered_map<int, long long> &memo) {
    // Return should be long long to prevent overflow
    // Fibonacci series: [1, 1, 2, 3, 5, 8, 13, ...]
    if (memo.find(n) != memo.end()) return memo[n];
    if (n <= 0) return 0;
    if (n <= 2) return 1;

    memo[n] = fib(n-1, memo) + fib(n-2, memo);
    return memo[n];
}

int main() {
    unordered_map<int, long long> memo;
    assert(fib(6, memo) == 8); 
    // No need to call memo.clear(); as memo values can be reused
    assert(fib(7, memo) == 13);
    assert(fib(8, memo) == 21);
    assert(fib(50, memo) == 12586269025);
}