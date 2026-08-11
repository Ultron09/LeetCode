/**
 * Problem: 354. Russian Doll Envelopes
 * Difficulty: Hard
 * Topics: Array, Binary Search, Dynamic Programming, Sorting
 * LeetCode Link: https://leetcode.com/problems/russian-doll-envelopes/
 * 
 * Time Complexity:  O(N log N) - Sorting + patience-sort LIS via binary search
 * Space Complexity: O(N) - Tails array for LIS
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = static_cast<int>(envelopes.size());
        if (n <= 1) return n;

        // Sort by width ascending; for equal widths, sort by height descending.
        // Descending height for same width prevents selecting two envelopes
        // with the same width in the LIS on heights.
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });

        // Patience-sort LIS on the height dimension
        vector<int> tails; // tails[i] = smallest tail element for IS of length i+1
        for (int i = 0; i < n; ++i) {
            int h = envelopes[i][1];
            auto it = lower_bound(tails.begin(), tails.end(), h);
            if (it == tails.end()) {
                tails.push_back(h);
            } else {
                *it = h;
            }
        }

        return static_cast<int>(tails.size());
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: envelopes = [[5,4],[6,4],[6,7],[2,3]]
    {
        vector<vector<int>> envelopes = {{5,4},{6,4},{6,7},{2,3}};
        int result = solver.maxEnvelopes(envelopes);
        assert(result == 3);
        cout << "Test 1 Passed: [[5,4],[6,4],[6,7],[2,3]] -> 3" << endl;
    }

    // Test Case 2: All identical envelopes
    {
        vector<vector<int>> envelopes = {{1,1},{1,1},{1,1}};
        int result = solver.maxEnvelopes(envelopes);
        assert(result == 1);
        cout << "Test 2 Passed: [[1,1],[1,1],[1,1]] -> 1" << endl;
    }

    // Test Case 3: Single envelope
    {
        vector<vector<int>> envelopes = {{1,1}};
        int result = solver.maxEnvelopes(envelopes);
        assert(result == 1);
        cout << "Test 3 Passed: [[1,1]] -> 1" << endl;
    }

    // Test Case 4: Strictly increasing chain
    {
        vector<vector<int>> envelopes = {{1,2},{3,4},{5,6},{7,8}};
        int result = solver.maxEnvelopes(envelopes);
        assert(result == 4);
        cout << "Test 4 Passed: [[1,2],[3,4],[5,6],[7,8]] -> 4" << endl;
    }

    // Test Case 5: Same width, varying heights
    {
        vector<vector<int>> envelopes = {{1,1},{1,2},{1,3},{1,4}};
        int result = solver.maxEnvelopes(envelopes);
        assert(result == 1);
        cout << "Test 5 Passed: [[1,1],[1,2],[1,3],[1,4]] -> 1" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
