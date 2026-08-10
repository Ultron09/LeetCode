/**
 * Problem: 1840. Maximum Building Height
 * Difficulty: Hard
 * Topics: Array, Math, Greedy, Sorting
 * LeetCode Link: https://leetcode.com/problems/maximum-building-height/
 * 
 * Time Complexity:  O(R log R) where R = restrictions.size() <= 10^5
 * Space Complexity: O(R) for sorting restrictions
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        // 1. Add boundary condition: building 1 must have height 0
        restrictions.push_back({1, 0});

        // 2. Sort restrictions in ascending order of building id
        sort(restrictions.begin(), restrictions.end());

        // 3. Add boundary condition for building n if not explicitly given
        if (restrictions.back()[0] != n) {
            restrictions.push_back({n, n - 1});
        }

        int m = restrictions.size();

        // 4. Left-to-Right Pass: Propagate maximum allowable growth from left
        for (int i = 1; i < m; ++i) {
            int dist = restrictions[i][0] - restrictions[i - 1][0];
            restrictions[i][1] = min(restrictions[i][1], restrictions[i - 1][1] + dist);
        }

        // 5. Right-to-Left Pass: Propagate maximum allowable growth from right
        for (int i = m - 2; i >= 0; --i) {
            int dist = restrictions[i + 1][0] - restrictions[i][0];
            restrictions[i][1] = min(restrictions[i][1], restrictions[i + 1][1] + dist);
        }

        // 6. Calculate triangular peak height between each adjacent pair of restrictions
        int maxHeight = 0;
        for (int i = 1; i < m; ++i) {
            int x1 = restrictions[i - 1][0], h1 = restrictions[i - 1][1];
            int x2 = restrictions[i][0], h2 = restrictions[i][1];
            int peak = (x2 - x1 + h1 + h2) / 2;
            maxHeight = max(maxHeight, peak);
        }

        return maxHeight;
    }

    // Alias for backward compatibility
    int maxBuildingHeight(int n, vector<vector<int>>& restrictions) {
        return maxBuilding(n, restrictions);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1
    {
        int n = 5;
        vector<vector<int>> restrictions = {{2, 1}, {4, 1}};
        int expected = 2;
        assert(solver.maxBuilding(n, restrictions) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        int n = 6;
        vector<vector<int>> restrictions = {};
        int expected = 5;
        assert(solver.maxBuilding(n, restrictions) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        int n = 10;
        vector<vector<int>> restrictions = {{5, 3}, {2, 5}, {7, 4}, {10, 3}};
        int expected = 5;
        assert(solver.maxBuilding(n, restrictions) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
