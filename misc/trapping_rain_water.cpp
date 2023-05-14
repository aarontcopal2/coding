// https://leetcode.com/problems/trapping-rain-water/
#include <cassert>              // assert
#include <vector>

class Solution {
public:
    int trap(const std::vector<int>& height) {
        std::vector<int> max_height_from_left(height.size());
        std::vector<int> max_height_from_right(height.size());

        int max_height = INT_MIN;
        for (int i=0; i< height.size(); i++) {
            max_height = std::max(max_height, height[i]);
            max_height_from_left[i] = max_height;
        }

        max_height = INT_MIN;
        for (int i=height.size()-1; i>=0; i--) {
            max_height = std::max(max_height, height[i]);
            max_height_from_right[i] = max_height;
        }

        int collected_water = 0, curr_water_level;
        for (int i=0; i< height.size(); i++) {
            curr_water_level = std::min(max_height_from_left[i], max_height_from_right[i]) - height[i];
            collected_water += curr_water_level;
        }
        return collected_water;
    }
};

int main() {
    Solution s;
    const std::vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    int collected_water = s.trap(height);
    assert(collected_water == 6);
}