/**
 * Problem: 3474. Lexicographically Smallest Generated String
 * Difficulty: Hard
 * Topics: String, Greedy, String Matching
 * LeetCode Link: https://leetcode.com/problems/lexicographically-smallest-generated-string/
 * 
 * Time Complexity:  O(N * M) where N = str1.length() <= 10^4, M = str2.length() <= 500
 * Space Complexity: O(N + M) auxiliary space for result string and fixed position tracking
 */

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <cassert>

using namespace std;

class Solution {
public:
    string generateString(string str1, string str2) {
        int n = static_cast<int>(str1.length());
        int m = static_cast<int>(str2.length());
        int sz = n + m - 1;

        string ans(sz, '\0');
        vector<bool> fixed(sz, false);

        // 1. Enforce all 'T' constraints
        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; ++j) {
                    if (ans[i + j] != '\0' && ans[i + j] != str2[j]) {
                        // Conflict between two 'T' requirements
                        return "";
                    }
                    ans[i + j] = str2[j];
                    fixed[i + j] = true;
                }
            }
        }

        // 2. Greedily fill all unfixed positions with 'a'
        for (int i = 0; i < sz; ++i) {
            if (ans[i] == '\0') {
                ans[i] = 'a';
            }
        }

        // 3. Handle 'F' constraints
        // If a substring equals str2, modify the rightmost unfixed character to 'b'
        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'F') {
                string_view sub(ans.data() + i, m);
                if (sub == str2) {
                    // Find the rightmost position in [i, i + m - 1] that was not fixed by 'T'
                    int pos = -1;
                    for (int j = i + m - 1; j >= i; --j) {
                        if (!fixed[j]) {
                            pos = j;
                            break;
                        }
                    }

                    if (pos == -1) {
                        // All positions are fixed by 'T', cannot satisfy 'F'
                        return "";
                    }

                    // Change from 'a' to 'b' (guaranteed != str2[pos - i] since str2[pos - i] was 'a')
                    ans[pos] = 'b';
                    fixed[pos] = true; // Mark as fixed so subsequent operations don't treat it as free
                }
            }
        }

        // 4. Final verification pass to ensure all 'T' and 'F' conditions hold
        for (int i = 0; i < n; ++i) {
            string_view sub(ans.data() + i, m);
            if (str1[i] == 'T' && sub != str2) {
                return "";
            }
            if (str1[i] == 'F' && sub == str2) {
                return "";
            }
        }

        return ans;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1
    {
        string str1 = "TFTF";
        string str2 = "ab";
        string expected = "ababa";
        assert(solver.generateString(str1, str2) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        string str1 = "TFTF";
        string str2 = "abc";
        string expected = "";
        assert(solver.generateString(str1, str2) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        string str1 = "F";
        string str2 = "d";
        string expected = "a";
        assert(solver.generateString(str1, str2) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    // Test Case 4: Single 'T'
    {
        string str1 = "T";
        string str2 = "z";
        string expected = "z";
        assert(solver.generateString(str1, str2) == expected);
        cout << "Test 4 Passed!" << endl;
    }

    // Test Case 5: Single 'F' with 'a'
    {
        string str1 = "F";
        string str2 = "a";
        string expected = "b";
        assert(solver.generateString(str1, str2) == expected);
        cout << "Test 5 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
