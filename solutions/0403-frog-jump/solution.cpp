/**
 * Problem: 403. Frog Jump
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming, Binary Search, Hash Table
 * LeetCode Link: https://leetcode.com/problems/frog-jump/
 * 
 * Time Complexity:  O(N^2) - At most N*(N+1)/2 reachable (stone, jump) states with O(1) transitions
 * Space Complexity: O(N^2) - Flat contiguous boolean DP table of size N x N (approx. 4 MB for N=2000)
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdint>
#include <cassert>

using namespace std;

class Solution {
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        if (n < 2) return true;
        // The first jump from stone 0 must be 1 unit to stone 1
        if (stones[1] != 1) return false;
        if (n == 2) return true;

        // Map stone position to its index for O(1) average lookup
        unordered_map<int, int> posToIndex;
        posToIndex.reserve(n * 2);
        for (int i = 0; i < n; ++i) {
            posToIndex[stones[i]] = i;
        }

        // dp[i * n + k] is true if stone i can be reached with a jump of size k
        // At stone index i, maximum possible incoming jump is bounded by i
        vector<uint8_t> dp(n * n, 0);
        dp[1 * n + 1] = 1; // Base case: reached stone 1 with jump k = 1

        for (int i = 1; i < n - 1; ++i) {
            for (int k = 1; k <= i; ++k) {
                if (!dp[i * n + k]) continue;

                // Try next jump lengths: k - 1, k, k + 1
                for (int delta = -1; delta <= 1; ++delta) {
                    int nextJump = k + delta;
                    if (nextJump <= 0) continue;

                    int targetPos = stones[i] + nextJump;
                    auto it = posToIndex.find(targetPos);
                    if (it != posToIndex.end()) {
                        int j = it->second;
                        if (j == n - 1) return true; // Early exit upon reaching last stone
                        dp[j * n + nextJump] = 1;
                    }
                }
            }
        }

        return false;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1 (Reachable)
    {
        vector<int> stones = {0, 1, 3, 5, 6, 8, 12, 17};
        bool result = solver.canCross(stones);
        cout << "Test 1 - stones = [0,1,3,5,6,8,12,17] -> Expected: 1, Got: " << result << endl;
        assert(result == true);
    }

    // Test Case 2: Standard Example 2 (Unreachable due to large gap)
    {
        vector<int> stones = {0, 1, 2, 3, 4, 8, 9, 11};
        bool result = solver.canCross(stones);
        cout << "Test 2 - stones = [0,1,2,3,4,8,9,11] -> Expected: 0, Got: " << result << endl;
        assert(result == false);
    }

    // Test Case 3: Minimal 2 stones (Valid jump 1)
    {
        vector<int> stones = {0, 1};
        bool result = solver.canCross(stones);
        cout << "Test 3 - stones = [0,1] -> Expected: 1, Got: " << result << endl;
        assert(result == true);
    }

    // Test Case 4: Minimal 2 stones (Invalid first jump != 1)
    {
        vector<int> stones = {0, 2};
        bool result = solver.canCross(stones);
        cout << "Test 4 - stones = [0,2] -> Expected: 0, Got: " << result << endl;
        assert(result == false);
    }

    // Test Case 5: Triangular numbers (Strictly increasing jump sizes: 1, 2, 3, 4, 5, 6)
    {
        vector<int> stones = {0, 1, 3, 6, 10, 15, 21};
        bool result = solver.canCross(stones);
        cout << "Test 5 - Triangular stones -> Expected: 1, Got: " << result << endl;
        assert(result == true);
    }

    // Test Case 6: Increasing then decreasing jump sizes (1, 2, 3, 2, 1)
    {
        vector<int> stones = {0, 1, 3, 6, 8, 9};
        bool result = solver.canCross(stones);
        cout << "Test 6 - Up and down jump stones -> Expected: 1, Got: " << result << endl;
        assert(result == true);
    }

    // Test Case 7: Unreachable early gap
    {
        vector<int> stones = {0, 1, 5, 6, 7};
        bool result = solver.canCross(stones);
        cout << "Test 7 - stones = [0,1,5,6,7] -> Expected: 0, Got: " << result << endl;
        assert(result == false);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
