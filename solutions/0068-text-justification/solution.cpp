/**
 * Problem: 68. Text Justification
 * Difficulty: Hard
 * Topics: Array, String, Simulation, Greedy
 * LeetCode Link: https://leetcode.com/problems/text-justification/
 * 
 * Time Complexity:  O(Total Characters) - linear pass over words and characters
 * Space Complexity: O(maxWidth) auxiliary buffer per line
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = static_cast<int>(words.size());
        int i = 0;

        while (i < n) {
            // 1. Determine how many words fit in the current line
            int lineLen = static_cast<int>(words[i].length());
            int j = i + 1;

            while (j < n && lineLen + 1 + static_cast<int>(words[j].length()) <= maxWidth) {
                lineLen += 1 + static_cast<int>(words[j].length());
                ++j;
            }

            int numWords = j - i;
            int numGaps = numWords - 1;

            // Calculate total word character count (excluding spaces)
            int wordChars = 0;
            for (int k = i; k < j; ++k) {
                wordChars += static_cast<int>(words[k].length());
            }

            int totalSpaces = maxWidth - wordChars;
            string lineStr = "";

            // 2. Format line based on justification rules
            // Case A: Last line OR single word in line -> Left-justified
            if (j == n || numGaps == 0) {
                for (int k = i; k < j; ++k) {
                    if (k > i) lineStr += " ";
                    lineStr += words[k];
                }
                // Pad trailing spaces
                lineStr += string(maxWidth - lineStr.length(), ' ');
            } else {
                // Case B: Fully-justified line
                int baseSpaces = totalSpaces / numGaps;
                int extraSpaces = totalSpaces % numGaps;

                for (int k = i; k < j - 1; ++k) {
                    int currentGap = baseSpaces + ((k - i) < extraSpaces ? 1 : 0);
                    lineStr += words[k];
                    lineStr += string(currentGap, ' ');
                }
                // Append the last word in the line
                lineStr += words[j - 1];
            }

            result.push_back(lineStr);
            i = j;
        }

        return result;
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
        vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
        int maxWidth = 16;
        vector<string> expected = {
            "This    is    an",
            "example  of text",
            "justification.  "
        };
        assert(solver.fullJustify(words, maxWidth) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<string> words = {"What", "must", "be", "acknowledgment", "shall", "be"};
        int maxWidth = 16;
        vector<string> expected = {
            "What   must   be",
            "acknowledgment  ",
            "shall be        "
        };
        assert(solver.fullJustify(words, maxWidth) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3
    {
        vector<string> words = {
            "Science", "is", "what", "we", "understand", "well", "enough", "to",
            "explain", "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do"
        };
        int maxWidth = 20;
        vector<string> expected = {
            "Science  is  what we",
            "understand      well",
            "enough to explain to",
            "a  computer.  Art is",
            "everything  else  we",
            "do                  "
        };
        assert(solver.fullJustify(words, maxWidth) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
