/**
 * Problem: 878. Nth Magical Number
 * Difficulty: Hard
 * Topics: Math, Binary Search
 * LeetCode Link: https://leetcode.com/problems/nth-magical-number/
 * 
 * Time Complexity:  O(log(N * min(A, B))) - Binary search over a range up to 4*10^13
 * Space Complexity: O(1) - Constant extra space
 */

#include <iostream>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        long long MOD = 1e9 + 7;
        
        long long L = min(a, b);
        long long R = (long long)n * min(a, b);
        long long lcm_ab = std::lcm((long long)a, (long long)b);
        
        long long ans = R;
        
        while (L <= R) {
            long long mid = L + (R - L) / 2;
            long long count = (mid / a) + (mid / b) - (mid / lcm_ab);
            
            if (count >= n) {
                ans = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        
        return ans % MOD;
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
        assert(solver.nthMagicalNumber(1, 2, 3) == 2);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        assert(solver.nthMagicalNumber(4, 2, 3) == 6);
        cout << "Test 2 Passed!" << endl;
    }
    
    // Test Case 3
    {
        assert(solver.nthMagicalNumber(1000000000, 40000, 40000) == 999720007);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
