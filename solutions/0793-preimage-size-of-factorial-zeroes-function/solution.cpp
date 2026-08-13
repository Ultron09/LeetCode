/**
 * Problem: 793. Preimage Size of Factorial Zeroes Function
 * Difficulty: Hard
 * Topics: Math, Binary Search
 * LeetCode Link: https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/
 *
 * Approach: Binary Search + Legendre's Formula
 *
 * Key Insight:
 *   1. The number of trailing zeroes of x!, denoted as f(x), is determined by the 
 *      number of factors of 5 in the numbers from 1 to x. This is given by Legendre's 
 *      formula: f(x) = floor(x/5) + floor(x/25) + floor(x/125) + ...
 *   2. f(x) is a monotonically non-decreasing function.
 *   3. Since x! only gains factors of 5 when x is a multiple of 5, the values of x 
 *      that yield the same f(x) ALWAYS come in blocks of exactly 5 
 *      (e.g., x=0,1,2,3,4 all yield f(x)=0).
 *   4. However, when x is a multiple of a higher power of 5 (e.g., 25), f(x) jumps 
 *      by more than 1. This means some values of k are skipped entirely.
 *   5. Therefore, the number of integers x such that f(x) = k is ALWAYS either 5 or 0.
 *
 * Algorithm:
 *   - Use Binary Search to find if there exists ANY x such that f(x) == k.
 *   - Search range: left = 0, right = 5L * (k + 1). (Since f(x) is at least x/5).
 *   - If we find an x where f(x) == k, return 5.
 *   - If binary search finishes without finding such an x, return 0.
 *
 * Time Complexity:  O(log^2 K) - Binary search takes O(log K) steps, and calculating f(x) takes O(log x) steps.
 * Space Complexity: O(1)
 */

#include <iostream>
#include <cassert>

using namespace std;

class Solution {
    long long trailingZeroes(long long x) {
        long long count = 0;
        while (x > 0) {
            count += x / 5;
            x /= 5;
        }
        return count;
    }
    
public:
    int preimageSizeFZF(int k) {
        long long left = 0;
        long long right = 5LL * (k + 1);
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            long long zeroes = trailingZeroes(mid);
            
            if (zeroes == k) {
                return 5;
            } else if (zeroes < k) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return 0;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    {
        int res = solver.preimageSizeFZF(0);
        assert(res == 5);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        int res = solver.preimageSizeFZF(5);
        assert(res == 0);
        cout << "Test 2 Passed! Result: " << res << endl;
    }
    
    // Test Case 3
    {
        int res = solver.preimageSizeFZF(3);
        assert(res == 5);
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
