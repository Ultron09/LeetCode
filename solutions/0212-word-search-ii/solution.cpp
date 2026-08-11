/**
 * Problem: 212. Word Search II
 * Difficulty: Hard
 * Topics: Array, String, Backtracking, Trie, Matrix
 * LeetCode Link: https://leetcode.com/problems/word-search-ii/
 * 
 * Time Complexity:  O(M * N * 3^L + W * L) where M, N <= 12, L <= 10 (max word length), W = words.size()
 * Space Complexity: O(W * L) for the Trie data structure
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

struct TrieNode {
    TrieNode* children[26];
    string word;
    int childCount;

    TrieNode() : word(""), childCount(0) {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

class Solution {
private:
    void insert(TrieNode* root, const string& w) {
        TrieNode* curr = root;
        for (char ch : w) {
            int idx = ch - 'a';
            if (curr->children[idx] == nullptr) {
                curr->children[idx] = new TrieNode();
                curr->childCount++;
            }
            curr = curr->children[idx];
        }
        curr->word = w;
    }

    void dfs(vector<vector<char>>& board, int r, int c, TrieNode* parent, int parentChildIdx,
             vector<string>& result) {
        char ch = board[r][c];
        int idx = ch - 'a';
        TrieNode* currNode = parent->children[idx];

        if (!currNode) return;

        // If a word ends at this node, record it and clear to prevent duplicates
        if (!currNode->word.empty()) {
            result.push_back(currNode->word);
            currNode->word.clear();
        }

        // Temporarily mark cell as visited
        board[r][c] = '#';

        static const int dr[4] = {-1, 1, 0, 0};
        static const int dc[4] = {0, 0, -1, 1};
        int m = static_cast<int>(board.size());
        int n = static_cast<int>(board[0].size());

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] != '#') {
                int nextIdx = board[nr][nc] - 'a';
                if (currNode->children[nextIdx] != nullptr) {
                    dfs(board, nr, nc, currNode, nextIdx, result);
                }
            }
        }

        // Backtrack: restore character
        board[r][c] = ch;

        // Trie pruning: if this node is now a leaf and has no associated word, unlink it
        if (currNode->childCount == 0 && currNode->word.empty()) {
            parent->children[parentChildIdx] = nullptr;
            parent->childCount--;
            delete currNode;
        }
    }

    void freeTrie(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                freeTrie(node->children[i]);
            }
        }
        delete node;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (const string& w : words) {
            insert(root, w);
        }

        vector<string> result;
        int m = static_cast<int>(board.size());
        int n = static_cast<int>(board[0].size());

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                int idx = board[r][c] - 'a';
                if (root->children[idx] != nullptr) {
                    dfs(board, r, c, root, idx, result);
                }
            }
        }

        freeTrie(root);
        return result;
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
        vector<vector<char>> board = {
            {'o', 'a', 'a', 'n'},
            {'e', 't', 'a', 'e'},
            {'i', 'h', 'k', 'r'},
            {'i', 'f', 'l', 'v'}
        };
        vector<string> words = {"oath", "pea", "eat", "rain"};
        auto result = solver.findWords(board, words);
        sort(result.begin(), result.end());
        vector<string> expected = {"eat", "oath"};
        assert(result == expected);
        cout << "Test 1 Passed: [\"eat\", \"oath\"] found!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<vector<char>> board = {
            {'a', 'b'},
            {'c', 'd'}
        };
        vector<string> words = {"abcb"};
        auto result = solver.findWords(board, words);
        assert(result.empty());
        cout << "Test 2 Passed: [\"abcb\"] not found!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
