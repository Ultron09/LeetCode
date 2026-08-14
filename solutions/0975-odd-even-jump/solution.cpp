/**
 * Problem: 975. Odd Even Jump
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming, Stack, Monotonic Stack, Ordered Set
 * LeetCode Link: https://leetcode.com/problems/odd-even-jump/
 * 
 * Time Complexity:  O(N log N) where N is the length of the array, due to the map insertions and binary searches.
 * Space Complexity: O(N) to store the DP state arrays and the balanced BST (map).
 */

#include <iostream>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return n;
        
        // higher[i] = true if we can reach the end starting from i with an odd jump
        // lower[i] = true if we can reach the end starting from i with an even jump
        vector<bool> higher(n, false);
        vector<bool> lower(n, false);
        higher[n - 1] = true;
        lower[n - 1] = true;
        
        // Ordered map to store <value, smallest_index_seen_so_far>
        map<int, int> mp;
        mp[arr[n - 1]] = n - 1;
        
        int good_starts = 1;
        
        // Traverse backwards to construct the DP state
        for (int i = n - 2; i >= 0; --i) {
            // Odd jump: next index j is the smallest index such that arr[i] <= arr[j] and arr[j] is as small as possible
            auto it_odd = mp.lower_bound(arr[i]);
            if (it_odd != mp.end()) {
                higher[i] = lower[it_odd->second];
            }
            
            // Even jump: next index j is the smallest index such that arr[i] >= arr[j] and arr[j] is as large as possible
            auto it_even = mp.upper_bound(arr[i]);
            if (it_even != mp.begin()) {
                --it_even; // Move iterator back by one to get the largest value <= arr[i]
                lower[i] = higher[it_even->second];
            }
            
            // The 1st jump is an odd jump, so we count if starting from `i` with an odd jump reaches the end
            if (higher[i]) {
                good_starts++;
            }
            
            // Update map. Overwriting is intended because we are traversing right-to-left,
            // so we always want the leftmost (smallest) index for any given value.
            mp[arr[i]] = i;
        }
        
        return good_starts;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    vector<int> arr1 = {10, 13, 12, 14, 15};
    assert(solver.oddEvenJumps(arr1) == 2);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    vector<int> arr2 = {2, 3, 1, 1, 4};
    assert(solver.oddEvenJumps(arr2) == 3);
    cout << "Test 2 Passed!" << endl;

    // Test Case 3
    vector<int> arr3 = {5, 1, 3, 4, 2};
    assert(solver.oddEvenJumps(arr3) == 3);
    cout << "Test 3 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
