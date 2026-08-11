/**
 * Problem: 363. Max Sum of Rectangle No Larger Than K
 * Difficulty: Hard
 * Topics: Array, Binary Search, Matrix, Prefix Sum, Ordered Set
 * LeetCode Link: https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/
 * 
 * Time Complexity:  O(min(m,n)^2 * max(m,n) * log(max(m,n)))
 * Space Complexity: O(max(m,n))
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = static_cast<int>(matrix.size());
        int n = static_cast<int>(matrix[0].size());

        // Optimize: iterate over the smaller dimension in the O(d^2) outer loop.
        // If rows < cols, transpose so that columns are the smaller dimension.
        bool transposed = false;
        if (m < n) {
            vector<vector<int>> T(n, vector<int>(m));
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j)
                    T[j][i] = matrix[i][j];
            matrix = move(T);
            swap(m, n);
            transposed = true;
        }

        int result = INT_MIN;

        // Fix left column l, right column r (O(n^2) pairs where n = min dimension)
        for (int l = 0; l < n; ++l) {
            // rowSum[i] = sum of matrix[i][l..r] for current r
            vector<int> rowSum(m, 0);

            for (int r = l; r < n; ++r) {
                // Accumulate column r into row sums
                for (int i = 0; i < m; ++i) {
                    rowSum[i] += matrix[i][r];
                }

                // Now find max subarray sum <= k in rowSum[0..m-1]
                // using prefix sums + ordered set (BST)
                set<int> prefixSet;
                prefixSet.insert(0); // empty prefix
                int currSum = 0;

                for (int i = 0; i < m; ++i) {
                    currSum += rowSum[i];

                    // We want max (currSum - prevSum) such that currSum - prevSum <= k
                    // i.e., prevSum >= currSum - k
                    auto it = prefixSet.lower_bound(currSum - k);
                    if (it != prefixSet.end()) {
                        result = max(result, currSum - *it);
                        if (result == k) return k; // Early exit: can't do better
                    }

                    prefixSet.insert(currSum);
                }
            }
        }

        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: matrix = [[1,0,1],[0,-2,3]], k = 2
    {
        vector<vector<int>> matrix = {{1,0,1},{0,-2,3}};
        int result = solver.maxSumSubmatrix(matrix, 2);
        assert(result == 2);
        cout << "Test 1 Passed: [[1,0,1],[0,-2,3]], k=2 -> 2" << endl;
    }

    // Test Case 2: matrix = [[2,2,-1]], k = 3
    {
        vector<vector<int>> matrix = {{2,2,-1}};
        int result = solver.maxSumSubmatrix(matrix, 3);
        assert(result == 3);
        cout << "Test 2 Passed: [[2,2,-1]], k=3 -> 3" << endl;
    }

    // Test Case 3: Single element
    {
        vector<vector<int>> matrix = {{5}};
        int result = solver.maxSumSubmatrix(matrix, 5);
        assert(result == 5);
        cout << "Test 3 Passed: [[5]], k=5 -> 5" << endl;
    }

    // Test Case 4: All negative
    {
        vector<vector<int>> matrix = {{-3,-2},{-1,-4}};
        int result = solver.maxSumSubmatrix(matrix, -1);
        assert(result == -1);
        cout << "Test 4 Passed: [[-3,-2],[-1,-4]], k=-1 -> -1" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
