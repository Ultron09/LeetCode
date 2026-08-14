/**
 * Problem: 862. Shortest Subarray with Sum at Least K
 * Difficulty: Hard
 * Topics: Queue (Monotonic Deque), Prefix Sum, Sliding Window
 * LeetCode Link: https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
 * 
 * Time Complexity:  O(N) - We iterate through the prefix sums, and each index is pushed/popped from the deque at most once.
 * Space Complexity: O(N) - We store the prefix sums and the indices in the deque.
 */

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        
        int min_len = n + 1;
        deque<int> dq;
        
        for (int i = 0; i <= n; ++i) {
            // If the current prefix minus the smallest prefix we've seen so far >= k, we found a valid subarray
            while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
                min_len = min(min_len, i - dq.front());
                // We pop it because any future i will only yield a longer subarray length
                dq.pop_front(); 
            }
            
            // To keep the deque monotonic increasing in prefix sum, pop elements from the back
            // that are greater than or equal to the current prefix sum.
            // Why? If a prior prefix sum is larger, we would always prefer the current one since it's both smaller
            // (making it easier to reach sum >= k) and at a later index (making the resulting subarray shorter).
            while (!dq.empty() && prefix[i] <= prefix[dq.back()]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
        }
        
        return min_len <= n ? min_len : -1;
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
        vector<int> nums = {1};
        assert(solver.shortestSubarray(nums, 1) == 1);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<int> nums = {1, 2};
        assert(solver.shortestSubarray(nums, 4) == -1);
        cout << "Test 2 Passed!" << endl;
    }
    
    // Test Case 3
    {
        vector<int> nums = {2, -1, 2};
        assert(solver.shortestSubarray(nums, 3) == 3);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
