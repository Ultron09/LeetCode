/**
 * Problem: 3093. Longest Common Suffix Queries
 * Difficulty: Hard
 * Topics: Array, String, Trie
 * LeetCode Link: https://leetcode.com/problems/longest-common-suffix-queries/
 * 
 * Time Complexity:  O(Sum(|wordsContainer[i]|) + Sum(|wordsQuery[i]|))
 * Space Complexity: O(Sum(|wordsContainer[i]|) * 26) for Flat Vector Trie Pool
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
    struct Node {
        int children[26] = {};
        int bestIdx = -1;
        int minLen = INT_MAX;
    };

    vector<Node> trie;

    int createNode() {
        trie.emplace_back();
        return static_cast<int>(trie.size()) - 1;
    }

    void insert(const string& word, int index) {
        int curr = 0; // Root is index 0
        int len = static_cast<int>(word.size());

        // Update root best index if this word is shorter
        if (len < trie[curr].minLen) {
            trie[curr].minLen = len;
            trie[curr].bestIdx = index;
        }

        // Insert reversed characters (suffix -> prefix)
        for (int i = len - 1; i >= 0; --i) {
            int c = word[i] - 'a';
            if (trie[curr].children[c] == 0) {
                int nextNode = createNode();
                trie[curr].children[c] = nextNode;
            }
            curr = trie[curr].children[c];

            // Update best index at this suffix node
            if (len < trie[curr].minLen) {
                trie[curr].minLen = len;
                trie[curr].bestIdx = index;
            }
        }
    }

public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        trie.clear();
        createNode(); // Root node at index 0

        // 1. Insert all container words into the suffix Trie
        for (int i = 0; i < static_cast<int>(wordsContainer.size()); ++i) {
            insert(wordsContainer[i], i);
        }

        // 2. Process each query by matching characters from right to left
        vector<int> ans;
        ans.reserve(wordsQuery.size());

        for (const auto& query : wordsQuery) {
            int curr = 0;
            int best = trie[0].bestIdx;

            for (int i = static_cast<int>(query.size()) - 1; i >= 0; --i) {
                int c = query[i] - 'a';
                if (trie[curr].children[c] == 0) {
                    break;
                }
                curr = trie[curr].children[c];
                best = trie[curr].bestIdx;
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

    // Test Case 3: Stress Test with repetitive long strings
    {
        string longA(5000, 'a');
        vector<string> wordsContainer = {longA};
        vector<string> wordsQuery(1000, "a");
        vector<int> expected(1000, 0);
        assert(solver.stringIndices(wordsContainer, wordsQuery) == expected);
        cout << "Test 3 (Stress Test) Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
