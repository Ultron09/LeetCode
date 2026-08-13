/**
 * Problem: 730. Count Different Palindromic Subsequences
 * Difficulty: Hard
 * Topics: Dynamic Programming (Interval DP), String
 * LeetCode Link: https://leetcode.com/problems/count-different-palindromic-subsequences/
 *
 * Approach: Interval DP with Character-Anchored Decomposition
 *
 * Key Insight:
 *   Since s[i] ∈ {a, b, c, d} (only 4 characters), for each interval [i, j]
 *   we decompose palindromes by their outermost character c ∈ {a,b,c,d}:
 *
 *   For each character c, find:
 *     lo = first occurrence of c in s[i..j]
 *     hi = last  occurrence of c in s[i..j]
 *
 *   Case 1: c doesn't appear in [i, j]       → contributes 0
 *   Case 2: lo == hi (appears exactly once)   → contributes 1 (just "c")
 *   Case 3: lo < hi                           → contributes dp[lo+1][hi-1] + 2
 *     - The "+2" counts "c" itself and "cc"
 *     - dp[lo+1][hi-1] counts all distinct palindromic subsequences
 *       in the interior, each of which can be wrapped with c on both ends
 *       to form a new unique palindrome
 *
 *   dp[i][j] = Σ over c ∈ {a,b,c,d} of contribution(c, i, j)
 *
 *   We precompute next[i][c] and prev[i][c] for O(1) lookups.
 *
 * Time Complexity:  O(N²) — N² states × 4 characters × O(1) transitions
 * Space Complexity: O(N²) — for the dp table
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    int countPalindromicSubsequences(string s) {
        const int MOD = 1e9 + 7;
        int n = static_cast<int>(s.size());

        // Precompute: nxt[i][c] = first index >= i where s[index] == c
        //             prv[i][c] = last  index <= i where s[index] == c
        // -1 means not found
        vector<vector<int>> nxt(n + 1, vector<int>(4, n));  // sentinel = n (not found)
        vector<vector<int>> prv(n, vector<int>(4, -1));     // sentinel = -1 (not found)

        // Build nxt: scan right to left
        for (int i = n - 1; i >= 0; --i) {
            for (int c = 0; c < 4; ++c) {
                nxt[i][c] = nxt[i + 1][c];
            }
            nxt[i][s[i] - 'a'] = i;
        }

        // Build prv: scan left to right
        if (n > 0) {
            prv[0][s[0] - 'a'] = 0;
            for (int i = 1; i < n; ++i) {
                for (int c = 0; c < 4; ++c) {
                    prv[i][c] = prv[i - 1][c];
                }
                prv[i][s[i] - 'a'] = i;
            }
        }

        // dp[i][j] = number of distinct non-empty palindromic subsequences in s[i..j]
        vector<vector<long long>> dp(n, vector<long long>(n, 0));

        // Fill by increasing interval length
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                long long total = 0;

                for (int c = 0; c < 4; ++c) {
                    int lo = nxt[i][c];   // First occurrence of char c in [i, n)
                    int hi = prv[j][c];   // Last  occurrence of char c in [0, j]

                    // Verify lo and hi are within [i, j]
                    if (lo > j || hi < i) {
                        // Character c doesn't appear in [i, j]
                        continue;
                    }

                    // At least one occurrence of c exists
                    total += 1; // Count the single-character palindrome "c"

                    if (lo < hi) {
                        // Also count "cc" and all palindromes wrappable by c
                        total += dp[lo + 1][hi - 1] + 1;
                    }

                    total %= MOD;
                }

                dp[i][j] = total % MOD;
            }
        }

        return static_cast<int>(dp[0][n - 1]);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Basic example
    {
        string s = "bccb";
        int result = solver.countPalindromicSubsequences(s);
        assert(result == 6);
        cout << "Test 1 Passed! bccb → " << result << endl;
    }

    // Test Case 2: Large input with modular arithmetic
    {
        string s = "abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba";
        int result = solver.countPalindromicSubsequences(s);
        assert(result == 104860361);
        cout << "Test 2 Passed! large input → " << result << endl;
    }

    // Test Case 3: Single character
    {
        string s = "a";
        int result = solver.countPalindromicSubsequences(s);
        assert(result == 1);
        cout << "Test 3 Passed! a → " << result << endl;
    }

    // Test Case 4: All same characters
    {
        string s = "aaa";
        // Palindromes: "a", "aa", "aaa" → 3
        int result = solver.countPalindromicSubsequences(s);
        assert(result == 3);
        cout << "Test 4 Passed! aaa → " << result << endl;
    }

    // Test Case 5: Two characters
    {
        string s = "ab";
        // Palindromes: "a", "b" → 2
        int result = solver.countPalindromicSubsequences(s);
        assert(result == 2);
        cout << "Test 5 Passed! ab → " << result << endl;
    }

    // Test Case 6: Nested palindromes
    {
        string s = "abba";
        // Palindromes: a, b, aa, bb, aba, bab(?no, not subseq), abba → 
        // a, b, aa, bb, aba, abba → 6
        int result = solver.countPalindromicSubsequences(s);
        assert(result == 6);
        cout << "Test 6 Passed! abba → " << result << endl;
    }

    // Test Case 7: All four characters
    {
        string s = "abcd";
        // Only single characters: a, b, c, d → 4
        int result = solver.countPalindromicSubsequences(s);
        assert(result == 4);
        cout << "Test 7 Passed! abcd → " << result << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
