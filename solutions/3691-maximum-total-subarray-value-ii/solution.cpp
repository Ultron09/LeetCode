/**
 * Problem: 3691. Maximum Total Subarray Value II
 * Difficulty: Hard
 * Topics: Array, Heap (Priority Queue), Sparse Table / Segment Tree, RMQ, Greedy
 * LeetCode Link: https://leetcode.com/problems/maximum-total-subarray-value-ii/
 * 
 * Time Complexity:  O((N + K) log N) where N <= 5 * 10^4, K <= 10^5
 * Space Complexity: O(N log N) for Sparse Table
 */

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    static constexpr int MAX_LOG = 17; // 2^16 = 65536 > 50000

    struct SubarrayNode {
        long long val;
        int l;
        int r;

        bool operator<(const SubarrayNode& other) const {
            return val < other.val; // Max-heap ordered by subarray value
        }
    };

public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0 || k == 0) return 0;

        // 1. Precompute log2 values
        vector<int> lg(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            lg[i] = lg[i / 2] + 1;
        }

        // 2. Build Sparse Table for RMQ (Max and Min)
        vector<vector<int>> st_max(MAX_LOG, vector<int>(n));
        vector<vector<int>> st_min(MAX_LOG, vector<int>(n));

        for (int i = 0; i < n; ++i) {
            st_max[0][i] = nums[i];
            st_min[0][i] = nums[i];
        }

        for (int j = 1; j < MAX_LOG; ++j) {
            int len = 1 << j;
            int half = 1 << (j - 1);
            for (int i = 0; i + len <= n; ++i) {
                st_max[j][i] = max(st_max[j - 1][i], st_max[j - 1][i + half]);
                st_min[j][i] = min(st_min[j - 1][i], st_min[j - 1][i + half]);
            }
        }

        // Helper lambda to query subarray value in O(1)
        auto getSubarrayValue = [&](int l, int r) -> long long {
            int j = lg[r - l + 1];
            int mx = max(st_max[j][l], st_max[j][r - (1 << j) + 1]);
            int mn = min(st_min[j][l], st_min[j][r - (1 << j) + 1]);
            return static_cast<long long>(mx) - mn;
        };

        // 3. Initialize Max-Heap with largest candidate for each left bound l (which is r = n - 1)
        priority_queue<SubarrayNode> pq;
        for (int l = 0; l < n; ++l) {
            int r = n - 1;
            pq.push({getSubarrayValue(l, r), l, r});
        }

        // 4. Greedily extract top-K subarray values
        long long totalValue = 0;
        while (k > 0 && !pq.empty()) {
            auto [val, l, r] = pq.top();
            pq.pop();

            totalValue += val;
            --k;

            // Push the next best subarray starting at index l (which is r - 1)
            if (r - 1 >= l) {
                pq.push({getSubarrayValue(l, r - 1), l, r - 1});
            }
        }

        return totalValue;
    }

    // Aliases for compatibility
    long long maximumTotalValue(vector<int>& nums, int k) {
        return maxTotalValue(nums, k);
    }

    long long maxTotalSubarrayValue(vector<int>& nums, int k) {
        return maxTotalValue(nums, k);
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
        vector<int> nums = {1, 3, 2};
        int k = 2;
        long long expected = 4;
        assert(solver.maxTotalValue(nums, k) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> nums = {4, 2, 5, 1};
        int k = 3;
        long long expected = 12;
        assert(solver.maxTotalValue(nums, k) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
