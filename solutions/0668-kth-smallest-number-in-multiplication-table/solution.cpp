/**
 * Problem: 668. Kth Smallest Number in Multiplication Table
 * Difficulty: Hard
 * Topics: Math, Binary Search
 * LeetCode Link: https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
 * 
 * Time Complexity:  O(min(M, N) * log(M * N)) where M, N <= 3 * 10^4
 * Space Complexity: O(1) auxiliary memory
 */

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    // Counts the number of elements in the m x n multiplication table that are <= x
    int countLessEqual(int m, int n, int x) {
        int count = 0;
        for (int i = 1; i <= m; ++i) {
            count += min(n, x / i);
        }
        return count;
    }

public:
    int findKthNumber(int m, int n, int k) {
        // Ensure m <= n to minimize the number of row iterations
        if (m > n) {
            swap(m, n);
        }

        int low = 1;
        int high = m * n;
        int answer = high;

        // Binary search on the value domain [1, m * n]
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (countLessEqual(m, n, mid) >= k) {
                answer = mid;       // Candidate answer found; try smaller values
                high = mid - 1;
            } else {
                low = mid + 1;      // Not enough elements <= mid; search right
            }
        }

        return answer;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1 (m=3, n=3, k=5)
    {
        int m = 3, n = 3, k = 5;
        int result = solver.findKthNumber(m, n, k);
        cout << "Test 1 - m=3, n=3, k=5 -> Expected: 3, Got: " << result << endl;
        assert(result == 3);
    }

    // Test Case 2: Example 2 (m=2, n=3, k=6)
    {
        int m = 2, n = 3, k = 6;
        int result = solver.findKthNumber(m, n, k);
        cout << "Test 2 - m=2, n=3, k=6 -> Expected: 6, Got: " << result << endl;
        assert(result == 6);
    }

    // Test Case 3: Single element (m=1, n=1, k=1)
    {
        int m = 1, n = 1, k = 1;
        int result = solver.findKthNumber(m, n, k);
        cout << "Test 3 - m=1, n=1, k=1 -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    // Test Case 4: Maximum boundary (m=30000, n=30000, k=900000000)
    {
        int m = 30000, n = 30000, k = 900000000;
        int result = solver.findKthNumber(m, n, k);
        cout << "Test 4 - Largest element -> Expected: 900000000, Got: " << result << endl;
        assert(result == 900000000);
    }

    // Test Case 5: Large test case (m=9895, n=28405, k=100000000)
    {
        int m = 9895, n = 28405, k = 100000000;
        int result = solver.findKthNumber(m, n, k);
        cout << "Test 5 - Large table query -> Expected: 31306500, Got: " << result << endl;
        assert(result == 31306500);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
