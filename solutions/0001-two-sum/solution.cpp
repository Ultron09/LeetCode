/**
 * Problem: 1. Two Sum
 * Difficulty: Easy
 * Topics: Arrays & Hashing
 * LeetCode Link: https://leetcode.com/problems/two-sum/
 *
 * Approach: One-pass Hash Table
 *
 * Key Insight:
 *   Instead of checking all pairs O(N^2), we can iterate through the array once.
 *   For each element `nums[i]`, we calculate its complement `target - nums[i]`.
 *   If the complement exists in our hash table, we have found a solution.
 *   If not, we add the current element to the hash table and continue.
 *
 * Time Complexity:  O(N) - We traverse the list containing n elements exactly once.
 * Space Complexity: O(N) - The extra space required depends on the number of items stored in the hash table.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numMap; // val -> index
        
        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            
            if (numMap.find(complement) != numMap.end()) {
                return {numMap[complement], i};
            }
            
            numMap[nums[i]] = i;
        }
        
        return {}; // Should not reach here as per problem constraints
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
        vector<int> nums = {2, 7, 11, 15};
        int target = 9;
        vector<int> result = solver.twoSum(nums, target);
        assert(result[0] == 0 && result[1] == 1);
        cout << "Test 1 Passed! [2,7,11,15], target 9 -> " << result[0] << ", " << result[1] << endl;
    }

    // Test Case 2
    {
        vector<int> nums = {3, 2, 4};
        int target = 6;
        vector<int> result = solver.twoSum(nums, target);
        assert(result[0] == 1 && result[1] == 2);
        cout << "Test 2 Passed! [3,2,4], target 6 -> " << result[0] << ", " << result[1] << endl;
    }

    // Test Case 3
    {
        vector<int> nums = {3, 3};
        int target = 6;
        vector<int> result = solver.twoSum(nums, target);
        assert(result[0] == 0 && result[1] == 1);
        cout << "Test 3 Passed! [3,3], target 6 -> " << result[0] << ", " << result[1] << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
