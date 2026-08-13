/**
 * Problem: 761. Special Binary String
 * Difficulty: Hard
 * Topics: String, Recursion, Sorting
 * LeetCode Link: https://leetcode.com/problems/special-binary-string/
 *
 * Approach: Recursion + Sorting (Isomorphic to Valid Parentheses / Trees)
 *
 * Key Insight:
 *   A "Special Binary String" is mathematically equivalent to a valid string of 
 *   parentheses (where '1' is '(' and '0' is ')'). 
 *   The swapping operation of two consecutive special substrings is equivalent 
 *   to swapping adjacent child subtrees of a node in the corresponding tree.
 *   Since we can swap ANY two consecutive adjacent subtrees, we can effectively 
 *   sort all sibling subtrees in any order we want. 
 *   To get the lexicographically largest string, we must sort the subtrees in 
 *   descending order.
 *
 * Algorithm:
 *   1. Split the string into "primitive" special strings (those that cannot be 
 *      split further without breaking the special property).
 *   2. For each primitive string, strip the outer '1' and '0' (which correspond 
 *      to the root's edges to this subtree).
 *   3. Recursively solve the inner string.
 *   4. Re-attach the '1' and '0' and collect the processed primitive strings.
 *   5. Sort the list of processed primitive strings in descending lexicographical order.
 *   6. Concatenate them to form the result.
 *
 * Time Complexity:  O(N^2) in the worst case (e.g., highly nested strings like "111...000"), 
 *                   due to substring operations and string concatenations. Since N <= 50, 
 *                   this easily passes.
 * Space Complexity: O(N) for recursion depth and storing substrings.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    string makeLargestSpecial(string s) {
        if (s.empty()) return "";
        
        vector<string> primitives;
        int count = 0;
        int start = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            count += (s[i] == '1' ? 1 : -1);
            if (count == 0) {
                // We found a primitive special string s[start..i]
                // The inner string is s[start+1 .. i-1]
                string inner = s.substr(start + 1, i - start - 1);
                
                // Recursively process the inner string
                string processed_inner = makeLargestSpecial(inner);
                
                // Re-wrap with '1' and '0'
                primitives.push_back("1" + processed_inner + "0");
                
                start = i + 1;
            }
        }
        
        // Sort in descending order to get the lexicographically largest combination
        sort(primitives.begin(), primitives.end(), greater<string>());
        
        string res = "";
        for (const string& p : primitives) {
            res += p;
        }
        
        return res;
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
        string s = "11011000";
        string expected = "11100100";
        string res = solver.makeLargestSpecial(s);
        assert(res == expected);
        cout << "Test 1 Passed! Output: " << res << endl;
    }

    // Test Case 2
    {
        string s = "10";
        string expected = "10";
        string res = solver.makeLargestSpecial(s);
        assert(res == expected);
        cout << "Test 2 Passed! Output: " << res << endl;
    }
    
    // Test Case 3: Nested multiple siblings
    {
        string s = "10110010";
        // Primitives: "10", "1100", "10"
        // Sorted desc: "1100", "10", "10"
        // Result: "11001010"
        string expected = "11001010";
        string res = solver.makeLargestSpecial(s);
        assert(res == expected);
        cout << "Test 3 Passed! Output: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
