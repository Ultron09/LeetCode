/**
 * Problem: 780. Reaching Points
 * Difficulty: Hard
 * Topics: Math
 * LeetCode Link: https://leetcode.com/problems/reaching-points/
 *
 * Approach: Work Backwards with Modulo Arithmetic
 *
 * Key Insight:
 *   Working forwards from (sx, sy) branches out exponentially into a massive binary tree.
 *   However, working backwards from (tx, ty) is deterministic!
 *   If tx > ty, the previous point MUST have been (tx - ty, ty).
 *   If ty > tx, the previous point MUST have been (tx, ty - tx).
 *   If tx == ty, we can't go back further unless tx == sx and ty == sy.
 *   
 *   To optimize this and avoid TLE when tx is much larger than ty (e.g., tx = 10^9, ty = 1),
 *   we use modulo arithmetic. Instead of repeated subtraction, we can do `tx %= ty` or `ty %= tx`.
 *   
 *   Special Case:
 *   When one coordinate matches the starting coordinate (e.g., tx == sx), we just need to 
 *   check if the other coordinate can reach the start using the first coordinate.
 *   For example, if tx == sx, we check if `(ty - sy) % sx == 0`.
 *
 * Time Complexity:  O(log(max(tx, ty))) - Similar to the Euclidean Algorithm for GCD.
 * Space Complexity: O(1)
 */

#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        // Work backwards from (tx, ty) to (sx, sy)
        while (tx >= sx && ty >= sy) {
            if (tx == sx && ty == sy) {
                return true;
            }
            
            if (tx > ty) {
                if (ty > sy) {
                    tx %= ty;
                } else { // ty == sy
                    return (tx - sx) % ty == 0;
                }
            } else if (ty > tx) {
                if (tx > sx) {
                    ty %= tx;
                } else { // tx == sx
                    return (ty - sy) % tx == 0;
                }
            } else { // tx == ty
                break; // Unless tx == sx and ty == sy (handled above), this is a dead end.
            }
        }
        
        return false;
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
        bool res = solver.reachingPoints(1, 1, 3, 5);
        assert(res == true);
        cout << "Test 1 Passed! Result: " << (res ? "true" : "false") << endl;
    }

    // Test Case 2
    {
        bool res = solver.reachingPoints(1, 1, 2, 2);
        assert(res == false);
        cout << "Test 2 Passed! Result: " << (res ? "true" : "false") << endl;
    }
    
    // Test Case 3
    {
        bool res = solver.reachingPoints(1, 1, 1, 1);
        assert(res == true);
        cout << "Test 3 Passed! Result: " << (res ? "true" : "false") << endl;
    }

    // Test Case 4: Fast modulo needed
    {
        bool res = solver.reachingPoints(1, 1, 1000000000, 1);
        assert(res == true);
        cout << "Test 4 Passed! Result: " << (res ? "true" : "false") << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
