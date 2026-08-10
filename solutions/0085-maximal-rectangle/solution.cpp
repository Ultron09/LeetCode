/**
 * Problem: 85. Maximal Rectangle
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming, Stack, Matrix, Monotonic Stack
 * LeetCode Link: https://leetcode.com/problems/maximal-rectangle/
 * 
 * Time Complexity:  O(R * C) where R = rows, C = cols
 * Space Complexity: O(C) for column histograms and monotonic stack
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    int largestRectangleArea(const vector<int>& heights) {
        int n = static_cast<int>(heights.size());
        stack<int> st;
        int maxArea = 0;

        for (int i = 0; i <= n; ++i) {
            int currHeight = (i == n) ? 0 : heights[i];

            while (!st.empty() && heights[st.top()] >= currHeight) {
                int h = heights[st.top()];
                st.pop();

                int w = st.empty() ? i : (i - st.top() - 1);
                maxArea = max(maxArea, h * w);
            }

            st.push(i);
        }

        return maxArea;
    }

public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        int rows = static_cast<int>(matrix.size());
        int cols = static_cast<int>(matrix[0].size());
        vector<int> heights(cols, 0);
        int maxArea = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (matrix[r][c] == '1') {
                    heights[c] += 1;
                } else {
                    heights[c] = 0;
                }
            }
            maxArea = max(maxArea, largestRectangleArea(heights));
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

    // Test Case 1
    {
        vector<vector<char>> matrix = {
            {'1','0','1','0','0'},
            {'1','0','1','1','1'},
            {'1','1','1','1','1'},
            {'1','0','0','1','0'}
        };
        assert(solver.maximalRectangle(matrix) == 6);
        cout << "Test 1 Passed: matrix area -> 6" << endl;
    }

    // Test Case 2
    {
        vector<vector<char>> matrix = {{'0'}};
        assert(solver.maximalRectangle(matrix) == 0);
        cout << "Test 2 Passed: matrix area -> 0" << endl;
    }

    // Test Case 3
    {
        vector<vector<char>> matrix = {{'1'}};
        assert(solver.maximalRectangle(matrix) == 1);
        cout << "Test 3 Passed: matrix area -> 1" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
