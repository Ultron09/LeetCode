/**
 * Problem: 691. Stickers to Spell Word
 * Difficulty: Hard
 * Topics: Dynamic Programming, Bit Manipulation
 * LeetCode Link: https://leetcode.com/problems/stickers-to-spell-word/
 *
 * Approach: Bitmask DP over subsets of target characters.
 *   - State: dp[mask] = minimum stickers to cover the subset of target
 *            positions indicated by the set bits in 'mask'.
 *   - Transition: For each state, find the lowest uncovered bit position,
 *                 then only try stickers that contain that character (pruning).
 *                 For each such sticker, greedily match its letters against
 *                 uncovered positions to produce a new mask.
 *   - Answer: dp[(1 << T) - 1], or -1 if unreachable.
 *
 * Time Complexity:  O(2^T * N * T) — T = target.length (≤15), N = #stickers
 * Space Complexity: O(2^T) — for the dp array
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int T = target.size();
        int full = (1 << T) - 1;

        // Pre-compute letter frequencies for each sticker
        int N = stickers.size();
        vector<vector<int>> stickerFreq(N, vector<int>(26, 0));
        for (int i = 0; i < N; i++) {
            for (char c : stickers[i]) {
                stickerFreq[i][c - 'a']++;
            }
        }

        // dp[mask] = min stickers to cover the subset 'mask' of target positions
        vector<int> dp(full + 1, INT_MAX);
        dp[0] = 0;

        for (int mask = 0; mask <= full; mask++) {
            if (dp[mask] == INT_MAX) continue;  // unreachable state

            // Find the lowest uncovered position (first 0-bit in mask, within T bits)
            int lowestUncovered = -1;
            for (int b = 0; b < T; b++) {
                if (!(mask & (1 << b))) {
                    lowestUncovered = b;
                    break;
                }
            }
            // If all covered, lowestUncovered stays -1 → mask == full, skip
            if (lowestUncovered == -1) continue;

            char needed = target[lowestUncovered];

            // Try only stickers that contain the needed character
            for (int s = 0; s < N; s++) {
                if (stickerFreq[s][needed - 'a'] == 0) continue;

                // Simulate using sticker s: greedily match its letters
                // against uncovered positions in target (left to right).
                vector<int> avail = stickerFreq[s]; // copy of sticker's freq
                int newMask = mask;

                for (int b = 0; b < T; b++) {
                    if (newMask & (1 << b)) continue;  // already covered
                    int ch = target[b] - 'a';
                    if (avail[ch] > 0) {
                        avail[ch]--;
                        newMask |= (1 << b);
                    }
                }

                dp[newMask] = min(dp[newMask], dp[mask] + 1);
            }
        }

        return dp[full] == INT_MAX ? -1 : dp[full];
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: stickers = ["with","example","science"], target = "thehat"
    {
        vector<string> stickers = {"with", "example", "science"};
        string target = "thehat";
        int result = solver.minStickers(stickers, target);
        assert(result == 3);
        cout << "Test 1 Passed! (result = " << result << ")" << endl;
    }

    // Test Case 2: stickers = ["notice","possible"], target = "basicbasic"
    {
        vector<string> stickers = {"notice", "possible"};
        string target = "basicbasic";
        int result = solver.minStickers(stickers, target);
        assert(result == -1);
        cout << "Test 2 Passed! (result = " << result << ")" << endl;
    }

    // Test Case 3: Single sticker matches target exactly
    {
        vector<string> stickers = {"abc"};
        string target = "abc";
        int result = solver.minStickers(stickers, target);
        assert(result == 1);
        cout << "Test 3 Passed! (result = " << result << ")" << endl;
    }

    // Test Case 4: Need multiple copies of one sticker
    {
        vector<string> stickers = {"ab"};
        string target = "aabb";
        int result = solver.minStickers(stickers, target);
        assert(result == 2);
        cout << "Test 4 Passed! (result = " << result << ")" << endl;
    }

    // Test Case 5: Single character target
    {
        vector<string> stickers = {"a", "b"};
        string target = "a";
        int result = solver.minStickers(stickers, target);
        assert(result == 1);
        cout << "Test 5 Passed! (result = " << result << ")" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
