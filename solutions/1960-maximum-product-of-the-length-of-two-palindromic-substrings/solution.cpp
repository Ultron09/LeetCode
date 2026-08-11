/**
 * Problem: 1960. Maximum Product of the Length of Two Palindromic Substrings
 * Difficulty: Hard
 * Topics: String, Manacher's Algorithm, Queue, Sliding Window, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/
 * 
 * Time Complexity:  O(N) - Linear time for Manacher's algorithm and two-pass monotonic queue scans
 * Space Complexity: O(N) - Arrays for palindrome radii, prefix/suffix max lengths, and monotonic queue
 */

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    long long maxProduct(string s) {
        int n = s.length();

        // 1. Manacher's Algorithm for odd-length palindromic substrings
        vector<int> P(n, 0); // P[i] = radius of longest odd palindrome centered at i
        int center = 0, right = 0;
        for (int i = 0; i < n; ++i) {
            int mirror = 2 * center - i;
            if (i < right) {
                P[i] = min(right - i, P[mirror]);
            }
            while (i - P[i] - 1 >= 0 && i + P[i] + 1 < n && s[i - P[i] - 1] == s[i + P[i] + 1]) {
                P[i]++;
            }
            if (i + P[i] > right) {
                center = i;
                right = i + P[i];
            }
        }

        // 2. Compute leftMax[e]: max odd palindrome length ending at or before index e
        vector<int> leftMax(n, 1);
        deque<int> q; // Stores center indices in increasing order
        int centerIdx = 0;

        for (int e = 0; e < n; ++e) {
            while (centerIdx < n && centerIdx <= e) {
                q.push_back(centerIdx);
                centerIdx++;
            }
            while (!q.empty() && q.front() + P[q.front()] < e) {
                q.pop_front();
            }
            if (!q.empty()) {
                leftMax[e] = 2 * (e - q.front()) + 1;
            }
            if (e > 0) {
                leftMax[e] = max(leftMax[e], leftMax[e - 1]);
            }
        }

        // 3. Compute rightMax[start]: max odd palindrome length starting at or after index start
        vector<int> rightMax(n, 1);
        q.clear();
        centerIdx = n - 1;

        for (int start = n - 1; start >= 0; --start) {
            while (centerIdx >= 0 && centerIdx >= start) {
                q.push_back(centerIdx);
                centerIdx--;
            }
            while (!q.empty() && q.front() - P[q.front()] > start) {
                q.pop_front();
            }
            if (!q.empty()) {
                rightMax[start] = 2 * (q.front() - start) + 1;
            }
            if (start < n - 1) {
                rightMax[start] = max(rightMax[start], rightMax[start + 1]);
            }
        }

        // 4. Find max product across all non-intersecting partition boundaries
        long long maxProd = 0;
        for (int t = 0; t < n - 1; ++t) {
            maxProd = max(maxProd, 1LL * leftMax[t] * rightMax[t + 1]);
        }

        return maxProd;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1
    {
        string s = "ababbb";
        long long result = solver.maxProduct(s);
        cout << "Test 1 - s=\"ababbb\" -> Expected: 9, Got: " << result << endl;
        assert(result == 9);
    }

    // Test Case 2: Standard Example 2
    {
        string s = "zaaaxbbby";
        long long result = solver.maxProduct(s);
        cout << "Test 2 - s=\"zaaaxbbby\" -> Expected: 9, Got: " << result << endl;
        assert(result == 9);
    }

    // Test Case 3: Minimal length 2
    {
        string s = "bb";
        long long result = solver.maxProduct(s);
        cout << "Test 3 - s=\"bb\" -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    // Test Case 4: Complex multi-palindrome string
    {
        string s = "babbbabb";
        long long result = solver.maxProduct(s);
        cout << "Test 4 - s=\"babbbabb\" -> Expected: 15, Got: " << result << endl;
        assert(result == 15);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
