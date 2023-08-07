#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#define ASSERT(left,operator,right) { if(!((left) operator (right))) {\
    std::cerr << "ASSERT FAILED at line " << __LINE__ \
        << ", " << #left << " " << #operator << " " <<  #right << "\n"\
        << "LHS" << " = " << (left) << "; " << "RHS" << " = " << (right) << "\n"; }\
}

using namespace std;


vector<int> collect (const vector<int> &height) {
    // Given the heights of towers, return a vector that contains
    // the rainwater collected on top of each tower.
    // TC: O(n), SC: O(n)

    // Water collected atop any tower would be dependent on the tallest
    // towers to its left(A) and right(B). To be specific, the collected 
    // water will reach height of min(A,B).
    // Collected water would be min(A,B) - tower_height.
    vector<int> left_max(height.size());
    vector<int> right_max(height.size());
    vector<int> water(height.size());
    if (height.size() > 0) {
        left_max[0] = height[0];
        right_max[height.size() -1] = height[height.size() -1];
    }
    for (int i=1; i < height.size(); i++) {
        left_max[i] = max(height[i], left_max[i-1]);
    }
    for (int i=height.size() -2; i >= 0; i--) {
        right_max[i] = max(height[i], right_max[i+1]);
    }
    for (int i=0; i < height.size(); i++) {
        water[i] = min(left_max[i], right_max[i]) - height[i];
        // collected water cannot be negative.
        water[i] = max(water[i], 0);
    }

    return water;
}

int main() {
    vector<int> result = collect({1, 4, 5, 8, 10});
    vector<int> expected = {0, 0, 0, 0, 0};
    assert(result == expected);

    result = collect({1, 8, 6, 2, 5, 4, 8, 3, 7});
    expected = {0, 0, 2, 6, 3, 4, 0, 4, 0};
    assert(result == expected);
}