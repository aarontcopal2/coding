#include <algorithm>
#include <iostream>
#include <vector>

#define ASSERT(left,operator,right) { if(!((left) operator (right))) {\
    std::cerr << "ASSERT FAILED at line " << __LINE__ \
        << ", " << #left << " " << #operator << " " <<  #right << "\n"\
        << "LHS" << " = " << (left) << "; " << "RHS" << " = " << (right) << "\n"; }\
}

using namespace std;


int minimize (const vector<int> &A, const vector<int> &B, const vector<int> &C) {
    // Given three sorted arrays A, B, C:
    // minimize abs|max(a,b,c) - min(a,b,c)|
    // Where:
    //   a belongs to A
    //   b belongs to B
    //   c belongs to C

    // three pointer approach:
    // pointers i,j,k will be traversing over A,B,C respectively.
    // increment the pointer to smallest value
    // return the min value in all of the traversal.
    // TC: O(n), SC: O(1)
    int min_value = INT_MAX;
    int i=0, j=0, k=0;
    while (i < A.size() && j < B.size() && k < C.size()) {
        int curr_value = abs(max({A[i], B[j], C[k]}) - min({A[i], B[j], C[k]}));
        min_value = min(curr_value, min_value);
        // increment index with min value.
        if (A[i] <= B[j] && A[i] <= C[k]) i++;
        else if (B[j] <= A[i] && B[j] <= C[k]) j++;
        else if (C[k] <= A[i] && C[k] <= B[j]) k++;
    }

    return min_value;
}

int main() {
    int result = minimize({1, 4, 5, 8, 10}, {6, 9, 15}, {2, 3, 3, 6});
    ASSERT(result, ==, 1);

    result = minimize({2, 3, 5}, {1, 3, 8}, {0, 3, 10});
    ASSERT(result, ==, 0);
}