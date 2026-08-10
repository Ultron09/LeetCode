/**
 * Problem: 3093. Longest Common Suffix Queries
 * Difficulty: Hard
 * Topics: Array, String, Trie
 * LeetCode Link: https://leetcode.com/problems/longest-common-suffix-queries/
 * 
 * Time Complexity:  O(Sum(|wordsContainer[i]|) + Sum(|wordsQuery[i]|))
 * Space Complexity: O(Sum(|wordsContainer[i]|) * 26) for Trie
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
private:
    struct TrieNode {
        TrieNode* children[26];
        int bestIdx;
        int minLen;

        TrieNode() : bestIdx(-1), minLen(INT_MAX) {
            fill(begin(children), end(children), nullptr);
        }
    };

    TrieNode* root;

    void insert(const string& word, int index) {
        TrieNode* curr = root;
        int len = word.size();

        // Update root best index if this word is shorter
        if (len < curr->minLen) {
            curr->minLen = len;
            curr->bestIdx = index;
        }

        // Insert reversed characters (suffix -> prefix)
        for (int i = len - 1; i >= 0; --i) {
            int c = word[i] - 'a';
            if (!curr->children[c]) {
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];

            // Update best index at this prefix/suffix node
            if (len < curr->minLen) {
                curr->minLen = len;
                curr->bestIdx = index;
            }
        }
    }

public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        root = new TrieNode();

        // 1. Insert all container words into the suffix Trie
        for (int i = 0; i < static_cast<int>(wordsContainer.size()); ++i) {
            insert(wordsContainer[i], i);
        }

        // 2. Process each query by matching characters from right to left
        vector<int> ans;
        ans.reserve(wordsQuery.size());

        for (const auto& query : wordsQuery) {
            TrieNode* curr = root;
            int best = root->bestIdx;

            for (int i = static_cast<int>(query.size()) - 1; i >= 0; --i) {
                int c = query[i] - 'a';
                if (!curr->children[c]) {
                    break;
                }
                curr = curr->children[c];
                best = curr->bestIdx;
            }

            ans.push_back(best);
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
        vector<string> wordsContainer = {"abcd", "bcd", "xbcd"};
        vector<string> wordsQuery = {"cd", "bcd", "xyz"};
        vector<int> expected = {1, 1, 1};
        assert(solver.stringIndices(wordsContainer, wordsQuery) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<string> wordsContainer = {"abcdefgh", "poiuygh", "ghghgh"};
        vector<string> wordsQuery = {"gh", "acbfgh", "acbfegh"};
        vector<int> expected = {2, 0, 2};
        assert(solver.stringIndices(wordsContainer, wordsQuery) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
