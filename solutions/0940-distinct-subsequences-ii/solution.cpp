/**
 * Problem: 940. Distinct Subsequences II
 * Difficulty: Hard
 * Topics: String, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/distinct-subsequences-ii/
 * 
 * Time Complexity:  O(N) - We iterate through the string once.
 * Space Complexity: O(1) - We use an array of size 26.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        vector<long long> last(26, 0);
        long long total_sum = 0;
        
        for (char c : s) {
            int idx = c - 'a';
            long long old_val = last[idx];
            long long new_val = (total_sum + 1) % MOD;
            
            last[idx] = new_val;
            
            // Update total_sum
            total_sum = (total_sum - old_val + new_val) % MOD;
            if (total_sum < 0) {
                total_sum += MOD;
            }
        }
        
        return total_sum;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    string s1 = "abc";
    assert(solver.distinctSubseqII(s1) == 7);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    string s2 = "aba";
    assert(solver.distinctSubseqII(s2) == 6);
    cout << "Test 2 Passed!" << endl;

    // Test Case 3
    string s3 = "aaa";
    assert(solver.distinctSubseqII(s3) == 3);
    cout << "Test 3 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
