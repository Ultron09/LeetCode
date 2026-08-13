/**
 * Problem: 798. Smallest Rotation with Highest Score
 * Difficulty: Hard
 * Topics: Array, Prefix Sum (Difference Array)
 * LeetCode Link: https://leetcode.com/problems/smallest-rotation-with-highest-score/
 *
 * Approach: Difference Array / Line Sweep
 *
 * Key Insight:
 *   For an element `nums[i]` at index `i`, if we rotate the array by `k`, its new 
 *   index becomes `j = (i - k + N) % N`.
 *   We score 1 point if `j >= nums[i]`.
 *   
 *   Let's find the valid range of `k` for which this condition holds.
 *   The new index `j` can range from `nums[i]` up to `N - 1`.
 *   - When `j = N - 1`, we get the minimum valid `k`: `k = (i - (N - 1) + N) % N = (i + 1) % N`.
 *   - When `j = nums[i]`, we get the maximum valid `k`: `k = (i - nums[i] + N) % N`.
 *   
 *   As `j` decreases from `N - 1` to `nums[i]`, `k` increases continuously. Thus, the valid 
 *   values of `k` form a contiguous range: `[ (i + 1) % N, (i - nums[i] + N) % N ]`.
 *   
 *   If the start of the range is less than or equal to the end, it's a standard interval.
 *   If the start is greater than the end, the interval wraps around the array, meaning it 
 *   covers `[start, N-1]` and `[0, end]`.
 *   
 *   We can use a Difference Array to add 1 to these intervals efficiently in O(1) per element.
 *   After processing all elements, a single pass of prefix sums over the difference array 
 *   will give us the total score for each `k`. We then simply pick the `k` with the maximum score.
 *
 * Time Complexity:  O(N) - One pass to build the difference array, one pass to compute prefix sums.
 * Space Complexity: O(N) - For the difference array.
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int bestRotation(vector<int>& nums) {
        int n = nums.size();
        vector<int> diff(n + 1, 0);
        
        for (int i = 0; i < n; ++i) {
            int left = (i + 1) % n;
            int right = (i - nums[i] + n) % n;
            
            if (left <= right) {
                diff[left]++;
                diff[right + 1]--;
            } else {
                // Wraps around
                diff[left]++;
                diff[n]--;
                diff[0]++;
                diff[right + 1]--;
            }
        }
        
        int best_k = 0;
        int max_score = -1;
        int current_score = 0;
        
        for (int k = 0; k < n; ++k) {
            current_score += diff[k];
            if (current_score > max_score) {
                max_score = current_score;
                best_k = k;
            }
        }
        
        return best_k;
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
        vector<int> nums = {2, 3, 1, 4, 0};
        int res = solver.bestRotation(nums);
        assert(res == 3);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        vector<int> nums = {1, 3, 0, 2, 4};
        int res = solver.bestRotation(nums);
        assert(res == 0);
        cout << "Test 2 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
