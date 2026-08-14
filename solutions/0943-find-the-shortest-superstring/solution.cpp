/**
 * Problem: 943. Find the Shortest Superstring
 * Difficulty: Hard
 * Topics: Array, String, Dynamic Programming, Bit Manipulation, Bitmask DP
 * LeetCode Link: https://leetcode.com/problems/find-the-shortest-superstring/
 * 
 * Time Complexity:  O(N^2 * 2^N + N^2 * L) - We compute overlaps in N^2 * L and then run Bitmask DP.
 * Space Complexity: O(N * 2^N) - DP table and parent pointers.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();
        vector<vector<int>> overlap(n, vector<int>(n, 0));
        
        // Precompute overlaps between every pair of words
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    int len_i = words[i].length();
                    int len_j = words[j].length();
                    for (int k = min(len_i, len_j); k > 0; --k) {
                        if (words[i].substr(len_i - k) == words[j].substr(0, k)) {
                            overlap[i][j] = k;
                            break;
                        }
                    }
                }
            }
        }
        
        // DP variables
        int num_states = 1 << n;
        vector<vector<int>> dp(num_states, vector<int>(n, 0));
        vector<vector<int>> parent(num_states, vector<int>(n, -1));
        
        // DP transitions
        for (int mask = 1; mask < num_states; ++mask) {
            for (int i = 0; i < n; ++i) {
                if ((mask & (1 << i)) > 0) {
                    int prev_mask = mask ^ (1 << i);
                    if (prev_mask == 0) continue;
                    
                    for (int j = 0; j < n; ++j) {
                        if ((prev_mask & (1 << j)) > 0) {
                            int val = dp[prev_mask][j] + overlap[j][i];
                            if (val >= dp[mask][i]) {
                                dp[mask][i] = val;
                                parent[mask][i] = j;
                            }
                        }
                    }
                }
            }
        }
        
        // Find the ending word with the maximum overlap for the full mask
        int max_overlap = -1;
        int last = -1;
        int full_mask = num_states - 1;
        
        for (int i = 0; i < n; ++i) {
            if (dp[full_mask][i] > max_overlap) {
                max_overlap = dp[full_mask][i];
                last = i;
            }
        }
        
        // Reconstruct path
        vector<int> path;
        int curr_mask = full_mask;
        while (last != -1) {
            path.push_back(last);
            int prev = parent[curr_mask][last];
            curr_mask ^= (1 << last);
            last = prev;
        }
        reverse(path.begin(), path.end());
        
        // Build the shortest superstring
        string result = words[path[0]];
        for (int i = 1; i < n; ++i) {
            int prev = path[i - 1];
            int curr = path[i];
            result += words[curr].substr(overlap[prev][curr]);
        }
        
        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    vector<string> words1 = {"alex","loves","leetcode"};
    string res1 = solver.shortestSuperstring(words1);
    // Since any valid shortest superstring works, we just check its length.
    // Length of alexlovesleetcode is 4 + 5 + 8 = 17
    assert(res1.length() == 17);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    vector<string> words2 = {"catg","ctaagt","gcta","ttca","atgcatc"};
    string res2 = solver.shortestSuperstring(words2);
    // gctaagttcatgcatc is of length 16
    assert(res2.length() == 16);
    cout << "Test 2 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
