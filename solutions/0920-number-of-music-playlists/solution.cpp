/**
 * Problem: 920. Number of Music Playlists
 * Difficulty: Hard
 * Topics: Math, Dynamic Programming, Combinatorics
 * LeetCode Link: https://leetcode.com/problems/number-of-music-playlists/
 * 
 * Time Complexity:  O(goal * n) - We fill a DP table of size goal * n.
 * Space Complexity: O(n) - We only need the previous row of the DP table.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {
        int MOD = 1e9 + 7;
        
        // dp[j] will store the number of playlists of length i with j unique songs
        // We only need the current and previous states (i and i-1)
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= goal; ++i) {
            vector<long long> next_dp(n + 1, 0);
            for (int j = 1; j <= min(i, n); ++j) {
                // Option 1: Play a new song.
                // We choose 1 song from the remaining (n - (j - 1)) songs.
                next_dp[j] = (next_dp[j] + dp[j - 1] * (n - j + 1)) % MOD;
                
                // Option 2: Play a song we've already played.
                // We can choose any of the j songs, except the k most recently played ones.
                if (j > k) {
                    next_dp[j] = (next_dp[j] + dp[j] * (j - k)) % MOD;
                }
            }
            dp = next_dp;
        }
        
        return dp[n];
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    assert(solver.numMusicPlaylists(3, 3, 1) == 6);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    assert(solver.numMusicPlaylists(2, 3, 0) == 6);
    cout << "Test 2 Passed!" << endl;

    // Test Case 3
    assert(solver.numMusicPlaylists(2, 3, 1) == 2);
    cout << "Test 3 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
