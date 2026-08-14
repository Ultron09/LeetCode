/**
 * Problem: 964. Least Operators to Express Number
 * Difficulty: Hard
 * Topics: Math, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/least-operators-to-express-number/
 * 
 * Time Complexity:  O(log_x(target)) because at each step we divide the target by x, 
 *                   branching at most twice, and many states overlap and are memoized.
 * Space Complexity: O(log_x(target)) for the memoization map and recursion stack.
 */

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    unordered_map<long long, int> memo;

    // The number of 'x's required to form a term of x^i.
    // For i == 0, x^0 = x / x, which requires 2 'x's.
    // For i > 0, x^i requires i 'x's (e.g., x^3 = x * x * x uses 3 'x's).
    int cost(int i) {
        return i == 0 ? 2 : i;
    }

    int dfs(int target, int i, int x) {
        if (target == 0) return 0;
        if (target == 1) return cost(i);

        // State uniquely identified by target and current power index `i`.
        // Since i <= 30 (because target <= 2 * 10^8), shifting target by 6 bits is perfectly safe.
        long long key = ((long long)target << 6) | i;
        if (memo.count(key)) return memo[key];

        int d = target % x;
        int res;
        
        if (d == 0) {
            // No remainder, perfectly divisible, just move to the next power of x.
            res = dfs(target / x, i + 1, x);
        } else {
            // Option 1: Add d * x^i
            int opt1 = d * cost(i) + dfs(target / x, i + 1, x);
            
            // Option 2: Subtract (x - d) * x^i, and carry over 1 to x^{i+1}
            int opt2 = (x - d) * cost(i) + dfs(target / x + 1, i + 1, x);
            
            res = min(opt1, opt2);
        }

        return memo[key] = res;
    }

public:
    int leastOpsExpressTarget(int x, int target) {
        // We find the minimal number of 'x's used.
        // If an expression uses N 'x's, it will have exactly N - 1 operators.
        return dfs(target, 0, x) - 1;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    assert(solver.leastOpsExpressTarget(3, 19) == 5);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    assert(solver.leastOpsExpressTarget(5, 501) == 8);
    cout << "Test 2 Passed!" << endl;

    // Test Case 3
    assert(solver.leastOpsExpressTarget(100, 100000000) == 3);
    cout << "Test 3 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
