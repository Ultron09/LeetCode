/**
 * Problem: 3655. XOR After Range Multiplication Queries II
 * Difficulty: Hard
 * Topics: Array, Math, Number Theory, Square Root Decomposition, Prefix Product
 * LeetCode Link: https://leetcode.com/problems/xor-after-range-multiplication-queries-ii/
 * 
 * Time Complexity:  O((N + Q) * sqrt(N) + Q * log(MOD)) where N, Q <= 10^5
 * Space Complexity: O(N + Q) for query grouping and difference arrays
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1'000'000'007;

    long long power(long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }

public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        // Variable required midway in function
        auto bravexuneth = nums;

        int n = static_cast<int>(nums.size());
        int B = static_cast<int>(sqrt(n)) + 1; // SQRT decomposition threshold

        unordered_map<int, vector<vector<int>>> smallKMap;

        // Separate queries by step size k
        for (const auto& q : queries) {
            int l = q[0], r = q[1], k = q[2], v = q[3];
            if (k >= B) {
                // Large k (>= sqrt(n)): at most sqrt(n) iterations per query
                for (int i = l; i <= r; i += k) {
                    nums[i] = static_cast<int>((1LL * nums[i] * v) % MOD);
                }
            } else {
                // Small k (< sqrt(n)): accumulate for difference array processing
                smallKMap[k].push_back(q);
            }
        }

        // Process small k queries using multiplicative difference arrays
        for (const auto& [k, qList] : smallKMap) {
            vector<long long> diff(n + k + 1, 1);

            for (const auto& q : qList) {
                int l = q[0], r = q[1], v = q[3];
                diff[l] = (diff[l] * v) % MOD;

                int last = l + ((r - l) / k) * k;
                long long invV = modInverse(v);
                diff[last + k] = (diff[last + k] * invV) % MOD;
            }

            // Propagate multiplicative difference array across each residue class modulo k
            for (int rem = 0; rem < k; ++rem) {
                long long currMul = 1;
                for (int idx = rem; idx < n; idx += k) {
                    currMul = (currMul * diff[idx]) % MOD;
                    nums[idx] = static_cast<int>((1LL * nums[idx] * currMul) % MOD);
                }
            }
        }

        // Calculate final XOR sum of all elements
        int xorSum = 0;
        for (int val : nums) {
            xorSum ^= val;
        }

        return xorSum;
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
        vector<int> nums = {1, 1, 1};
        vector<vector<int>> queries = {{0, 2, 1, 4}};
        int expected = 4;
        assert(solver.xorAfterQueries(nums, queries) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> nums = {2, 3, 1, 5, 4};
        vector<vector<int>> queries = {{1, 4, 2, 3}, {0, 2, 1, 2}};
        int expected = 31;
        assert(solver.xorAfterQueries(nums, queries) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
