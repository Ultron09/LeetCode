/**
 * Problem: 488. Zuma Game
 * Difficulty: Hard
 * Topics: String, Dynamic Programming, Backtracking, Breadth-First Search
 * LeetCode Link: https://leetcode.com/problems/zuma-game/
 * 
 * Time Complexity:  O(B * H * (|B| + |H|) * V) where B = |board| <= 16, H = |hand| <= 5, and V is the number of reachable states
 * Space Complexity: O(V * (|B| + |H|)) - Hash set and BFS queue for state space exploration
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    // Repeatedly collapses any contiguous run of 3 or more identical colored balls
    string collapse(string s) {
        int i = 0;
        while (i < (int)s.size()) {
            int j = i;
            while (j < (int)s.size() && s[j] == s[i]) {
                j++;
            }
            if (j - i >= 3) {
                s.erase(i, j - i);
                i = 0; // Restart scan from the beginning to process chain reactions
            } else {
                i = j;
            }
        }
        return s;
    }

    struct State {
        string board;
        string hand;
        int steps;
    };

public:
    int findMinStep(string board, string hand) {
        // Sort hand so identical balls are clustered and state representation is canonical
        sort(hand.begin(), hand.end());

        queue<State> q;
        unordered_set<string> visited;

        q.push({board, hand, 0});
        visited.insert(board + "#" + hand);

        while (!q.empty()) {
            auto [currB, currH, steps] = q.front();
            q.pop();

            if (currB.empty()) {
                return steps;
            }
            if (currH.empty()) {
                continue;
            }

            int bLen = currB.size();
            int hLen = currH.size();

            for (int i = 0; i <= bLen; ++i) {
                for (int j = 0; j < hLen; ++j) {
                    // Avoid branching on duplicate hand characters at the same insertion point
                    if (j > 0 && currH[j] == currH[j - 1]) {
                        continue;
                    }

                    char c = currH[j];

                    // Pruning Rules:
                    // 1. Insert adjacent to a ball of the same color
                    // 2. OR insert between two balls of identical color (different from c) to set up split chain reactions
                    bool shouldInsert = false;
                    if (i > 0 && currB[i - 1] == c) {
                        shouldInsert = true;
                    } else if (i < bLen && currB[i] == c) {
                        shouldInsert = true;
                    } else if (i > 0 && i < bLen && currB[i - 1] == currB[i] && currB[i] != c) {
                        shouldInsert = true;
                    }

                    if (!shouldInsert) {
                        continue;
                    }

                    string newB = collapse(currB.substr(0, i) + c + currB.substr(i));
                    string newH = currH.substr(0, j) + currH.substr(j + 1);
                    string stateKey = newB + "#" + newH;

                    if (!visited.count(stateKey)) {
                        visited.insert(stateKey);
                        q.push({newB, newH, steps + 1});
                    }
                }
            }
        }

        return -1;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Impossible to clear
    {
        string board = "WRRBBW";
        string hand = "RB";
        int result = solver.findMinStep(board, hand);
        cout << "Test 1 - board=\"WRRBBW\", hand=\"RB\" -> Expected: -1, Got: " << result << endl;
        assert(result == -1);
    }

    // Test Case 2: Chain reaction clear
    {
        string board = "WWRRBBWW";
        string hand = "WRBRW";
        int result = solver.findMinStep(board, hand);
        cout << "Test 2 - board=\"WWRRBBWW\", hand=\"WRBRW\" -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 3: Simple repeated insertions
    {
        string board = "G";
        string hand = "GGGGG";
        int result = solver.findMinStep(board, hand);
        cout << "Test 3 - board=\"G\", hand=\"GGGGG\" -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 4: Split-insertion combo
    {
        string board = "RRWWRRBBRR";
        string hand = "WB";
        int result = solver.findMinStep(board, hand);
        cout << "Test 4 - board=\"RRWWRRBBRR\", hand=\"WB\" -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
