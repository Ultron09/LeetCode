/**
 * Problem: 828. Count Unique Characters of All Substrings of a Given String
 * Difficulty: Hard
 * Topics: Hash Table, String, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/
 *
 * Approach:
 * Instead of generating all substrings (which would be O(N^2) and too slow), we can calculate 
 * the total answer by determining the "contribution" of each individual character in the string.
 *
 * For a character `s[i]` to be unique in a substring, the substring must contain `s[i]` exactly once.
 * This means the substring must start after the previous occurrence of `s[i]` (or at the beginning of `s` if none)
 * and must end before the next occurrence of `s[i]` (or at the end of `s` if none).
 *
 * Let `prev` be the index of the last occurrence of `s[i]` (or -1).
 * Let `next` be the index of the next occurrence of `s[i]` (or N).
 * The number of valid starting positions is `i - prev`.
 * The number of valid ending positions is `next - i`.
 * Total substrings where `s[i]` is unique = `(i - prev) * (next - i)`.
 * We simply sum this up for all characters.
 *
 * Time Complexity: O(N) where N is the length of the string.
 * Space Complexity: O(N) to store the positions of the characters.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.length();
        // Store indices of each character
        vector<int> pos[26];
        
        // Add a dummy -1 index at the beginning for boundaries
        for (int i = 0; i < 26; ++i) {
            pos[i].push_back(-1);
        }
        
        // Record all occurrences
        for (int i = 0; i < n; ++i) {
            pos[s[i] - 'A'].push_back(i);
        }
        
        // Add a dummy N index at the end for boundaries
        for (int i = 0; i < 26; ++i) {
            pos[i].push_back(n);
        }
        
        long long total = 0;
        
        // Calculate contribution of each character
        for (int i = 0; i < 26; ++i) {
            for (size_t j = 1; j < pos[i].size() - 1; ++j) {
                long long left_choices = pos[i][j] - pos[i][j - 1];
                long long right_choices = pos[i][j + 1] - pos[i][j];
                total += left_choices * right_choices;
            }
        }
        
        return total;
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
        string s = "ABC";
        int res = solver.uniqueLetterString(s);
        assert(res == 10);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        string s = "ABA";
        int res = solver.uniqueLetterString(s);
        assert(res == 8);
        cout << "Test 2 Passed! Result: " << res << endl;
    }

    // Test Case 3
    {
        string s = "LEETCODE";
        int res = solver.uniqueLetterString(s);
        assert(res == 92);
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
