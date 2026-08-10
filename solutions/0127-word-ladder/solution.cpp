/**
 * Problem: 127. Word Ladder
 * Difficulty: Hard
 * Topics: Hash Table, String, Breadth-First Search, Graphs
 * LeetCode Link: https://leetcode.com/problems/word-ladder/
 * 
 * Time Complexity:  O(N * L * 26) where N = wordList.size(), L = word.length()
 * Space Complexity: O(N * L) for hash sets
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end()) {
            return 0;
        }

        // Bidirectional BFS with frontier swapping
        unordered_set<string> beginSet = {beginWord};
        unordered_set<string> endSet = {endWord};

        dict.erase(beginWord);
        dict.erase(endWord);

        int length = 1;
        int wordLen = static_cast<int>(beginWord.length());

        while (!beginSet.empty() && !endSet.empty()) {
            // Always expand from the smaller frontier for minimal branching
            if (beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }

            unordered_set<string> nextLevel;
            for (const string& word : beginSet) {
                string neighbor = word;
                for (int i = 0; i < wordLen; ++i) {
                    char origChar = neighbor[i];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == origChar) continue;
                        neighbor[i] = c;

                        // Check if frontiers meet
                        if (endSet.find(neighbor) != endSet.end()) {
                            return length + 1;
                        }

                        if (dict.find(neighbor) != dict.end()) {
                            nextLevel.insert(neighbor);
                            dict.erase(neighbor); // Avoid re-visiting
                        }
                    }
                    neighbor[i] = origChar;
                }
            }

            beginSet = move(nextLevel);
            length++;
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

    // Test Case 1: "hit" -> "cog" with valid dictionary -> 5
    {
        string beginWord = "hit";
        string endWord = "cog";
        vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
        assert(solver.ladderLength(beginWord, endWord, wordList) == 5);
        cout << "Test 1 Passed: [hit -> cog] = 5" << endl;
    }

    // Test Case 2: "hit" -> "cog" without endWord -> 0
    {
        string beginWord = "hit";
        string endWord = "cog";
        vector<string> wordList = {"hot", "dot", "dog", "lot", "log"};
        assert(solver.ladderLength(beginWord, endWord, wordList) == 0);
        cout << "Test 2 Passed: [hit -> cog] = 0" << endl;
    }

    // Test Case 3: "a" -> "c" -> 2
    {
        string beginWord = "a";
        string endWord = "c";
        vector<string> wordList = {"a", "b", "c"};
        assert(solver.ladderLength(beginWord, endWord, wordList) == 2);
        cout << "Test 3 Passed: [a -> c] = 2" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
