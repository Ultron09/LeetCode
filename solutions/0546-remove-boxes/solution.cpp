/**
 * Problem: 546. Remove Boxes
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming, Memoization
 * LeetCode Link: https://leetcode.com/problems/remove-boxes/
 * 
 * Time Complexity:  O(N^4) worst case, O(N^3) average with aggressive run compression and pruning
 * Space Complexity: O(N^3) - 3D memoization table memo[l][r][k]
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    int memo[100][100][100];

    int solve(const vector<int>& boxes, int l, int r, int k) {
        if (l > r) {
            return 0;
        }

        // Compress consecutive identical elements at the left boundary
        while (l + 1 <= r && boxes[l + 1] == boxes[l]) {
            l++;
            k++;
        }

        if (memo[l][r][k] > 0) {
            return memo[l][r][k];
        }

        // Option 1: Remove boxes[l] and all its k attached identical predecessors
        int maxPoints = (k + 1) * (k + 1) + solve(boxes, l + 1, r, 0);

        // Option 2: Clear an intermediate subarray [l + 1 .. m - 1] to merge boxes[l] with boxes[m]
        for (int m = l + 1; m <= r; ++m) {
            if (boxes[m] == boxes[l]) {
                // Pruning optimization: Skip if the predecessor is identical to boxes[l],
                // as that state is already evaluated via the earlier contiguous compression
                if (boxes[m - 1] == boxes[l]) {
                    continue;
                }

                int points = solve(boxes, l + 1, m - 1, 0) + solve(boxes, m, r, k + 1);
                maxPoints = max(maxPoints, points);
            }
        }

        return memo[l][r][k] = maxPoints;
    }

public:
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        if (n == 0) return 0;
        memset(memo, 0, sizeof(memo));
        return solve(boxes, 0, n - 1, 0);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1
    {
        vector<int> boxes = {1, 3, 2, 2, 2, 3, 4, 3, 1};
        int result = solver.removeBoxes(boxes);
        cout << "Test 1 - {1, 3, 2, 2, 2, 3, 4, 3, 1} -> Expected: 23, Got: " << result << endl;
        assert(result == 23);
    }

    // Test Case 2: All identical elements
    {
        vector<int> boxes = {1, 1, 1};
        int result = solver.removeBoxes(boxes);
        cout << "Test 2 - {1, 1, 1} -> Expected: 9, Got: " << result << endl;
        assert(result == 9);
    }

    // Test Case 3: Single element
    {
        vector<int> boxes = {1};
        int result = solver.removeBoxes(boxes);
        cout << "Test 3 - {1} -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    // Test Case 4: Alternating sequence
    {
        vector<int> boxes = {1, 2, 1, 2, 1};
        int result = solver.removeBoxes(boxes);
        cout << "Test 4 - {1, 2, 1, 2, 1} -> Expected: 11, Got: " << result << endl;
        assert(result == 11);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
