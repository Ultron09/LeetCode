/**
 * Problem: 440. K-th Smallest in Lexicographical Order
 * Difficulty: Hard
 * Topics: Trie, Math, Prefix Tree
 * LeetCode Link: https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/
 * 
 * Time Complexity:  O((log10(N))^2) - At most log10(N) levels, taking O(log10(N)) steps calculation per transition
 * Space Complexity: O(1) - Constant auxiliary space
 */

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    /**
     * Counts the total number of integers in [1, n] that have prefix 'curr'.
     * This corresponds to the size of the subtree rooted at 'curr' in the 10-ary Trie.
     */
    long long countSteps(long long curr, long long n) {
        long long steps = 0;
        long long first = curr;
        long long last = curr + 1;

        while (first <= n) {
            steps += min(n + 1, last) - first;
            first *= 10;
            last *= 10;
        }

        return steps;
    }

public:
    int findKthNumber(int n, int k) {
        long long curr = 1;
        k -= 1; // 1-indexed: 1 is the 1st smallest number

        while (k > 0) {
            long long steps = countSteps(curr, n);

            if (steps <= k) {
                // The k-th number is NOT in the subtree of 'curr'.
                // Skip the entire subtree and move to the right sibling.
                k -= steps;
                curr += 1;
            } else {
                // The k-th number IS in the subtree of 'curr'.
                // Descend into the leftmost child of 'curr'.
                k -= 1;
                curr *= 10;
            }
        }

        return static_cast<int>(curr);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1 (n = 13, k = 2 -> 10)
    {
        int n = 13, k = 2;
        int result = solver.findKthNumber(n, k);
        cout << "Test 1 - n = 13, k = 2 -> Expected: 10, Got: " << result << endl;
        assert(result == 10);
    }

    // Test Case 2: Standard Example 2 (n = 1, k = 1 -> 1)
    {
        int n = 1, k = 1;
        int result = solver.findKthNumber(n, k);
        cout << "Test 2 - n = 1, k = 1 -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    // Test Case 3: n = 2, k = 2 -> 2
    {
        int n = 2, k = 2;
        int result = solver.findKthNumber(n, k);
        cout << "Test 3 - n = 2, k = 2 -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 4: n = 100, k = 10 -> 17
    {
        int n = 100, k = 10;
        int result = solver.findKthNumber(n, k);
        cout << "Test 4 - n = 100, k = 10 -> Expected: 17, Got: " << result << endl;
        assert(result == 17);
    }

    // Test Case 5: n = 100, k = 90 -> 9
    {
        int n = 100, k = 90;
        int result = solver.findKthNumber(n, k);
        cout << "Test 5 - n = 100, k = 90 -> Expected: 9, Got: " << result << endl;
        assert(result == 9);
    }

    // Test Case 6: Large constraint boundary (n = 10^9, k = 10^9)
    {
        int n = 1000000000, k = 1000000000;
        int result = solver.findKthNumber(n, k);
        cout << "Test 6 - n = 10^9, k = 10^9 -> Expected: 999999999, Got: " << result << endl;
        assert(result == 999999999);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
