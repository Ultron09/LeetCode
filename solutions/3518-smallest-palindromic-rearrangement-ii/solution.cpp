/**
 * Problem: 3518. Smallest Palindromic Rearrangement II
 * Difficulty: Hard
 * Topics: Math, Combinatorics, Greedy, String
 * LeetCode Link: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/
 * 
 * Time Complexity:  O(N * Sigma * (Sigma + min(N, log K))) where Sigma = 26
 * Space Complexity: O(N) for string construction and O(Sigma) for frequency counts
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
private:
    /**
     * Computes the number of unique permutations of remaining characters with frequencies in half_cnt.
     * Multinomial coefficient: rem! / (c1! * c2! * ... * cm!) = Product of C(rem - sum, ci)
     * Caps result at cap + 1 to prevent integer overflow.
     */
    long long countPermutations(const vector<int>& half_cnt, long long cap) {
        int rem = 0;
        for (int cnt : half_cnt) rem += cnt;

        long long total_p = 1;
        for (int cnt : half_cnt) {
            if (cnt == 0) continue;

            int r = min(cnt, rem - cnt);
            long long comb = 1;
            for (int j = 1; j <= r; ++j) {
                comb = comb * (rem - j + 1) / j;
                if (comb > cap || (total_p > 0 && comb > (cap + total_p - 1) / total_p)) {
                    return cap + 1;
                }
            }

            total_p *= comb;
            if (total_p > cap) {
                return cap + 1;
            }
            rem -= cnt;
        }
        return total_p;
    }

public:
    string smallestPalindrome(string s, int k) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        // 1. Validate palindrome feasibility and extract half-counts
        char mid_char = '\0';
        int odd_count = 0;
        vector<int> half_cnt(26, 0);

        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 != 0) {
                odd_count++;
                mid_char = 'a' + i;
            }
            half_cnt[i] = count[i] / 2;
        }

        if (odd_count > 1) return ""; // Invalid palindrome

        int m = n / 2;
        string left_half = "";
        long long current_k = k;

        // 2. Greedy trial-and-error construction of the left half
        for (int pos = 0; pos < m; ++pos) {
            bool placed = false;
            for (int c = 0; c < 26; ++c) {
                if (half_cnt[c] == 0) continue;

                // Try placing character ('a' + c) at current position
                half_cnt[c]--;
                long long p = countPermutations(half_cnt, current_k);

                if (p >= current_k) {
                    // The desired k-th permutation starts with character ('a' + c)
                    left_half.push_back('a' + c);
                    placed = true;
                    break;
                } else {
                    // Skip all p permutations beginning with this character
                    current_k -= p;
                    half_cnt[c]++; // Backtrack / restore
                }
            }

            if (!placed) return ""; // Fewer than k permutations exist
        }

        // 3. Reconstruct the full palindrome from the left half
        string right_half = left_half;
        reverse(right_half.begin(), right_half.end());

        if (n % 2 != 0) {
            return left_half + mid_char + right_half;
        }
        return left_half + right_half;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Simple odd-length palindrome
    {
        string s = "aba";
        int k = 1;
        string result = solver.smallestPalindrome(s, k);
        assert(result == "aba");
        cout << "Test 1 Passed: " << result << endl;
    }

    // Test Case 2: Out-of-bounds k
    {
        string s = "aba";
        int k = 2;
        string result = solver.smallestPalindrome(s, k);
        assert(result == "");
        cout << "Test 2 Passed (Empty string): " << result << endl;
    }

    // Test Case 3: Multiple permutations
    {
        string s = "ababbab"; // 3 'a's, 4 'b's -> half: 1 'a', 2 'b's, mid: 'a'
        assert(solver.smallestPalindrome(s, 1) == "abbabba");
        assert(solver.smallestPalindrome(s, 2) == "bababab");
        assert(solver.smallestPalindrome(s, 3) == "bbaaabb");
        assert(solver.smallestPalindrome(s, 4) == "");
        cout << "Test 3 Passed (Multiset permutations)!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
