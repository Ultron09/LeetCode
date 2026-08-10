/**
 * Problem: 84. Largest Rectangle in Histogram
 * Difficulty: Hard
 * Topics: Array, Stack, Monotonic Stack
 * LeetCode Link: https://leetcode.com/problems/largest-rectangle-in-histogram/
 * 
 * Time Complexity:  O(N) - each index is pushed and popped at most once
 * Space Complexity: O(N) for the monotonic stack
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = static_cast<int>(heights.size());
        stack<int> st;
        int maxArea = 0;

        for (int i = 0; i <= n; ++i) {
            // Virtual trailing bar of height 0 at index n to flush the stack
            int currHeight = (i == n) ? 0 : heights[i];

            while (!st.empty() && heights[st.top()] >= currHeight) {
                int h = heights[st.top()];
                st.pop();

                // Width is bounded between current index i and the new stack top
                int w = st.empty() ? i : (i - st.top() - 1);
                maxArea = max(maxArea, h * w);
            }

            st.push(i);
        }

        return maxArea;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: heights = [2,1,5,6,2,3] -> 10
    {
        vector<int> heights = {2, 1, 5, 6, 2, 3};
        assert(solver.largestRectangleArea(heights) == 10);
        cout << "Test 1 Passed: heights = [2,1,5,6,2,3] -> 10" << endl;
    }

    // Test Case 2: heights = [2,4] -> 4
    {
        vector<int> heights = {2, 4};
        assert(solver.largestRectangleArea(heights) == 4);
        cout << "Test 2 Passed: heights = [2,4] -> 4" << endl;
    }

    // Test Case 3: Single element heights = [1] -> 1
    {
        vector<int> heights = {1};
        assert(solver.largestRectangleArea(heights) == 1);
        cout << "Test 3 Passed: heights = [1] -> 1" << endl;
    }

    // Test Case 4: Valley heights = [2,1,2] -> 3
    {
        vector<int> heights = {2, 1, 2};
        assert(solver.largestRectangleArea(heights) == 3);
        cout << "Test 4 Passed: heights = [2,1,2] -> 3" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
