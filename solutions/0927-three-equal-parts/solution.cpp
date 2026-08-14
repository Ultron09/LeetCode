    /**
    * Problem: 927. Three Equal Parts
    * Difficulty: Hard
    * Topics: Array, Math
    * LeetCode Link: https://leetcode.com/problems/three-equal-parts/
    * 
    * Time Complexity:  O(N) - We make a few passes over the array of size N.
    * Space Complexity: O(1) - Constant extra space used.
    */

    #include <iostream>
    #include <vector>
    #include <numeric>
    #include <cassert>

    using namespace std;

    class Solution {
    public:
        vector<int> threeEqualParts(vector<int>& arr) {
            int n = arr.size();
            int total_ones = 0;
            for (int num : arr) {
                if (num == 1) total_ones++;
            }
            
            if (total_ones % 3 != 0) {
                return {-1, -1};
            }
            
            if (total_ones == 0) {
                return {0, 2}; // Any valid partition works when it's all zeros
            }
            
            int target_ones = total_ones / 3;
            int p1 = -1, p2 = -1, p3 = -1;
            int current_ones = 0;
            
            for (int i = 0; i < n; ++i) {
                if (arr[i] == 1) {
                    current_ones++;
                    if (current_ones == 1) p1 = i;
                    else if (current_ones == target_ones + 1) p2 = i;
                    else if (current_ones == 2 * target_ones + 1) p3 = i;
                }
            }
            
            int match_len = n - p3;
            
            // Ensure that p1 and p2 have enough room for match_len
            if (p1 + match_len > p2 || p2 + match_len > p3) {
                return {-1, -1};
            }
            
            // Check if all three parts are identical
            for (int i = 0; i < match_len; ++i) {
                if (arr[p1 + i] != arr[p3 + i] || arr[p2 + i] != arr[p3 + i]) {
                    return {-1, -1};
                }
            }
            
            return {p1 + match_len - 1, p2 + match_len};
        }
    };

    // ==========================================
    // Local Test Runner (Guarded for LeetCode Submission)
    // ==========================================
    #ifdef LOCAL_TEST
    int main() {
        Solution solver;

        // Test Case 1
        vector<int> arr1 = {1,0,1,0,1};
        vector<int> exp1 = {0, 3};
        assert(solver.threeEqualParts(arr1) == exp1);
        cout << "Test 1 Passed!" << endl;

        // Test Case 2
        vector<int> arr2 = {1,1,0,1,1};
        vector<int> exp2 = {-1, -1};
        assert(solver.threeEqualParts(arr2) == exp2);
        cout << "Test 2 Passed!" << endl;

        // Test Case 3
        vector<int> arr3 = {1,1,0,0,1};
        vector<int> exp3 = {0, 2};
        assert(solver.threeEqualParts(arr3) == exp3);
        cout << "Test 3 Passed!" << endl;

        cout << "All test cases passed successfully!" << endl;
        return 0;
    }
    #endif
