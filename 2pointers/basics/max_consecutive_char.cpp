#include <algorithm>
#include <iostream>
#include <vector>

#define ASSERT(left,operator,right) { if(!((left) operator (right))) {\
    std::cerr << "ASSERT FAILED at line " << __LINE__ \
        << ", " << #left << " " << #operator << " " <<  #right << "\n"\
        << "LHS" << " = " << (left) << "; " << "RHS" << " = " << (right) << "\n"; }\
}

using namespace std;


int max_consecutive_chars (const vector<int> &height) {
    // Given the heights of towers, return the size of largest container.
    // A container is the rectangular space between two towers.
    // This problem is a variation of trapping_rainwater.cpp
    // TC: O(N), SC: O(1)

    int i = 0;
    int j = height.size() -1;
    int max_area = INT_MIN;
    while (i < j) {
        // area = height  * width
        int curr_area = min(height[i], height[j]) * (j-i);
        max_area = max(curr_area, max_area);
        if (height[i] < height[j]) {
            i++;
        } else {
            j--;
        }
    }

    return max_area;
}

int main() {
    int result = max_consecutive_chars({1, 4, 5, 8, 10});
    ASSERT(result, ==, 12);

    result = max_consecutive_chars({1, 8, 6, 2, 5, 4, 8, 3, 7});
    ASSERT(result, ==, 49);
}