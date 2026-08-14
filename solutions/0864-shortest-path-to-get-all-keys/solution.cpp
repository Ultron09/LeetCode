/**
 * Problem: 864. Shortest Path to Get All Keys
 * Difficulty: Hard
 * Topics: Graphs, Breadth-First Search (BFS), Bit Manipulation
 * LeetCode Link: https://leetcode.com/problems/shortest-path-to-get-all-keys/
 * 
 * Time Complexity:  O(M * N * 2^K) - Where M is rows, N is cols, and K is number of keys. Max 30*30*64 = 57,600 states.
 * Space Complexity: O(M * N * 2^K) - For the visited array and queue.
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int max_keys = 0;
        int start_r = -1, start_c = -1;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                char c = grid[i][j];
                if (c == '@') {
                    start_r = i;
                    start_c = j;
                } else if (c >= 'a' && c <= 'f') {
                    max_keys = max(max_keys, c - 'a' + 1);
                }
            }
        }
        
        int target_mask = (1 << max_keys) - 1;
        
        // Queue stores {row, col, key_mask, distance}
        queue<tuple<int, int, int, int>> q;
        // visited[row][col][mask]
        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(1 << max_keys, false)));
        
        q.push({start_r, start_c, 0, 0});
        visited[start_r][start_c][0] = true;
        
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [r, c, mask, dist] = q.front();
            q.pop();
            
            if (mask == target_mask) {
                return dist;
            }
            
            for (auto& d : dirs) {
                int nr = r + d[0];
                int nc = c + d[1];
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != '#') {
                    char cell = grid[nr][nc];
                    
                    int nmask = mask;
                    // If it's a key, pick it up
                    if (cell >= 'a' && cell <= 'f') {
                        nmask |= (1 << (cell - 'a'));
                    }
                    
                    // If it's a lock, we can only pass if we have the corresponding key
                    if (cell >= 'A' && cell <= 'F' && !(mask & (1 << (cell - 'A')))) {
                        continue;
                    }
                    
                    if (!visited[nr][nc][nmask]) {
                        visited[nr][nc][nmask] = true;
                        q.push({nr, nc, nmask, dist + 1});
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

    // Test Case 1
    {
        vector<string> grid = {"@.a..","###.#","b.A.B"};
        assert(solver.shortestPathAllKeys(grid) == 8);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<string> grid = {"@..aA","..B#.","....b"};
        assert(solver.shortestPathAllKeys(grid) == 6);
        cout << "Test 2 Passed!" << endl;
    }
    
    // Test Case 3
    {
        vector<string> grid = {"@Aa"};
        assert(solver.shortestPathAllKeys(grid) == -1);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
