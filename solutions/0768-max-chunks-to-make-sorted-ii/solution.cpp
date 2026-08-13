/**
 * Problem: 768. Max Chunks To Make Sorted II
 * Difficulty: Hard
 * Topics: Arrays & Hashing, Greedy
 * LeetCode Link: https://leetcode.com/problems/max-chunks-to-make-sorted-ii/
 *
 * Approach: Max of Left <= Min of Right
 *
 * Key Insight:
 *   If we want to partition the array at index `i` (meaning the left chunk is from 
 *   index 0 to i, and the right chunk starts at i + 1), it must be true that EVERY 
 *   element in the left chunk is less than or equal to EVERY element in the right chunk.
 *   
 *   This is equivalent to saying:
 *   `max(arr[0..i]) <= min(arr[i+1..N-1])`
 *
 *   We can precompute the minimums of the right suffixes in an array `minOfRight` 
 *   in O(N) time. Then, we iterate through the array from left to right, maintaining 
 *   the running maximum `maxOfLeft`. Whenever `maxOfLeft <= minOfRight[i + 1]`, we 
 *   can safely make a cut after index `i`.
 *
 * Time Complexity:  O(N) - Two linear passes over the array.
 * Space Complexity: O(N) - To store the suffix minimums.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        
        // minOfRight[i] will store the minimum element in arr[i...n-1]
        vector<int> minOfRight(n + 1, INT_MAX);
        for (int i = n - 1; i >= 0; --i) {
            minOfRight[i] = min(minOfRight[i + 1], arr[i]);
        }
        
        int chunks = 0;
        int maxOfLeft = INT_MIN;
        
        for (int i = 0; i < n; ++i) {
            maxOfLeft = max(maxOfLeft, arr[i]);
            
            // If the maximum so far is <= the minimum of the remaining elements,
            // we can make a valid cut here.
            if (maxOfLeft <= minOfRight[i + 1]) {
                chunks++;
            }
        }
        
        return chunks;
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
        vector<int> arr = {5, 4, 3, 2, 1};
        int res = solver.maxChunksToSorted(arr);
        assert(res == 1);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        vector<int> arr = {2, 1, 3, 4, 4};
        int res = solver.maxChunksToSorted(arr);
        assert(res == 4);
        cout << "Test 2 Passed! Result: " << res << endl;
    }
    
    // Test Case 3: Sorted array
    {
        vector<int> arr = {1, 2, 3, 4, 5};
        int res = solver.maxChunksToSorted(arr);
        assert(res == 5);
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
