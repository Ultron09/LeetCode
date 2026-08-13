/**
 * Problem: 810. Chalkboard XOR Game
 * Difficulty: Hard
 * Topics: Array, Math, Bit Manipulation, Game Theory
 * LeetCode Link: https://leetcode.com/problems/chalkboard-xor-game/
 *
 * Approach: Game Theory & Bit Manipulation
 * 
 * Key Insight:
 *   Let X be the XOR sum of all elements.
 *   If X == 0 initially, Alice wins immediately.
 *   If X != 0, Alice has to make a move. She loses if all possible moves make the new XOR sum 0.
 *   Removing an element `x` makes the new XOR sum `X ^ x`.
 *   For the new XOR sum to be 0 for ALL choices, it must be that `X ^ x = 0` for all `x`.
 *   This means `x = X` for all elements. Thus, all elements are equal to X.
 *   
 *   If all elements are equal to X, what is the total XOR sum?
 *   If the array size N is EVEN, the XOR sum of an even number of identical elements is 0.
 *   But we assumed X != 0! This is a contradiction.
 *   Therefore, if N is EVEN, it is IMPOSSIBLE for all elements to be X.
 *   This means that when N is even and X != 0, a player can ALWAYS find at least one 
 *   element to remove that does NOT make the XOR sum 0.
 *
 *   Since Alice starts when N is even, she can always make a safe move. 
 *   This leaves Bob with an odd number of elements. Bob might be forced to lose. 
 *   If Bob survives, he leaves an even number of elements for Alice, and she can again survive.
 *   Because the game is finite, Bob will eventually be forced to make the XOR sum 0 and lose.
 *
 *   Thus, Alice wins if and only if X == 0 initially OR the array size N is even.
 *
 * Time Complexity:  O(N) to compute the XOR sum.
 * Space Complexity: O(1).
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int xor_sum = 0;
        for (int x : nums) {
            xor_sum ^= x;
        }
        
        // Alice wins if the initial XOR sum is 0, OR if the number of elements is even.
        return xor_sum == 0 || nums.size() % 2 == 0;
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
        vector<int> nums = {1, 1, 2};
        bool res = solver.xorGame(nums);
        assert(res == false);
        cout << "Test 1 Passed! Result: false" << endl;
    }

    // Test Case 2
    {
        vector<int> nums = {0, 1};
        bool res = solver.xorGame(nums);
        assert(res == true);
        cout << "Test 2 Passed! Result: true" << endl;
    }

    // Test Case 3
    {
        vector<int> nums = {1, 2, 3};
        bool res = solver.xorGame(nums);
        assert(res == true);
        cout << "Test 3 Passed! Result: true" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
