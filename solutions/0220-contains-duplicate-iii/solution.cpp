/**
 * Problem: 220. Contains Duplicate III
 * Difficulty: Hard
 * Topics: Array, Sliding Window, Bucket Sort, Ordered Set, Sorting
 * LeetCode Link: https://leetcode.com/problems/contains-duplicate-iii/
 * 
 * Time Complexity:  O(N) average via Bucket Sort / Hash Table (or O(N log(indexDiff)) via std::set)
 * Space Complexity: O(min(N, indexDiff)) auxiliary space for active buckets
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
private:
    long long getBucketId(long long x, long long w) {
        // Floor division for negative numbers:
        // [-w, -1] -> bucket -1, [-2w, -w-1] -> bucket -2, etc.
        return (x < 0) ? ((x + 1) / w - 1) : (x / w);
    }

public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        if (indexDiff <= 0 || valueDiff < 0) {
            return false;
        }

        // Bucket size is (valueDiff + 1) so that any two elements in the same bucket
        // have an absolute difference <= valueDiff.
        long long w = static_cast<long long>(valueDiff) + 1;
        unordered_map<long long, long long> buckets;

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            long long x = nums[i];
            long long bucketId = getBucketId(x, w);

            // Check if current bucket already contains an element
            if (buckets.find(bucketId) != buckets.end()) {
                return true;
            }

            // Check adjacent left bucket
            if (buckets.find(bucketId - 1) != buckets.end() &&
                abs(x - buckets[bucketId - 1]) <= valueDiff) {
                return true;
            }

            // Check adjacent right bucket
            if (buckets.find(bucketId + 1) != buckets.end() &&
                abs(x - buckets[bucketId + 1]) <= valueDiff) {
                return true;
            }

            // Insert element into current bucket
            buckets[bucketId] = x;

            // Maintain sliding window of size <= indexDiff
            if (i >= indexDiff) {
                long long oldBucketId = getBucketId(nums[i - indexDiff], w);
                buckets.erase(oldBucketId);
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

    // Test Case 1: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0 -> true
    {
        vector<int> nums = {1, 2, 3, 1};
        assert(solver.containsNearbyAlmostDuplicate(nums, 3, 0) == true);
        cout << "Test 1 Passed: Duplicate found within indexDiff!" << endl;
    }

    // Test Case 2: nums = [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3 -> false
    {
        vector<int> nums = {1, 5, 9, 1, 5, 9};
        assert(solver.containsNearbyAlmostDuplicate(nums, 2, 3) == false);
        cout << "Test 2 Passed: No pair satisfies conditions!" << endl;
    }

    // Test Case 3: Negative numbers: nums = [-3, -1], indexDiff = 1, valueDiff = 2 -> true
    {
        vector<int> nums = {-3, -1};
        assert(solver.containsNearbyAlmostDuplicate(nums, 1, 2) == true);
        cout << "Test 3 Passed: Negative numbers bucketed correctly!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
