/**
 * Problem: 42. Trapping Rain Water
 * Difficulty: Hard
 * Topics: Array, Two Pointers, Dynamic Programming, Stack, Monotonic Stack
 * LeetCode Link: https://leetcode.com/problems/trapping-rain-water/
 * 
 * Time Complexity:  O(N) where N = height.size() <= 2 * 10^4
 * Space Complexity: O(1) auxiliary space
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;

        int left = 0;
        int right = static_cast<int>(height.size()) - 1;
        int leftMax = 0;
        int rightMax = 0;
        int waterTrapped = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    waterTrapped += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    waterTrapped += rightMax - height[right];
                }
                right--;
            }
        }

        return waterTrapped;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    {
        vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        assert(solver.trap(height) == 6);
        cout << "Test 1 Passed: trap = 6" << endl;
    }

    // Test Case 2
    {
        vector<int> height = {4, 2, 0, 3, 2, 5};
        assert(solver.trap(height) == 9);
        cout << "Test 2 Passed: trap = 9" << endl;
    }

    // Test Case 3: Flat / Monotonic
    {
        vector<int> height = {3, 3, 3};
        assert(solver.trap(height) == 0);
        cout << "Test 3 Passed: flat array -> 0" << endl;
    }

    // Test Case 4: Single bar
    {
        vector<int> height = {5};
        assert(solver.trap(height) == 0);
        cout << "Test 4 Passed: single bar -> 0" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
