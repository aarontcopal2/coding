/*
* You will be given an array of integers.
* Your goal is to find the min. number of insertions to be made to the array
* such that all elements in the array are divisible by a number k>=2
*
* Case 1:
* n=5 arr=[4,7,5,11,15]
* if we add [0,1,1,1,1] to arr, we get a resultant array where k=2
* output = 4 (1+1+1+1)
*/

#include <algorithm>
#include <iostream>
#include <vector>

#define ASSERT(left,operator,right) { if(!((left) operator (right))) {\
    std::cerr << "ASSERT FAILED at line " << __LINE__ \
        << ", " << #left << " " << #operator << " " <<  #right << "\n"\
        << "LHS" << " = " << (left) << "; " << "RHS" << " = " << (right) << "\n"; }\
}

using namespace std;

int equitable_distribution(vector<int> arr) {
    int max_elem = *max_element(arr.begin(), arr.end());
    int min_sum = INT_MAX;

    for (int i=2; i<=max_elem; i++) {
        int sum = 0;
        for (int a: arr) {
            sum += a%i;
        }
        min_sum = min(min_sum, sum);
    }
    return min_sum;
}

int main () {
    vector<int> arr = { 4, 7, 5, 11, 15 };
    int result = equitable_distribution(arr);
    ASSERT(result, ==, 4);
}