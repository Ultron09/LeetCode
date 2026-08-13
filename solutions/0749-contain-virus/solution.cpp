/**
 * Problem: 749. Contain Virus
 * Difficulty: Hard
 * Topics: Graphs, DFS, BFS, Simulation
 * LeetCode Link: https://leetcode.com/problems/contain-virus/
 *
 * Approach: Simulation with DFS/BFS
 *
 * Key Insight:
 *   The problem requires simulating the spread of a virus day by day.
 *   Each day, we need to:
 *   1. Find all continuous viral regions (connected components of 1s).
 *   2. For each region, find the uninfected cells (0s) it threatens (its perimeter of 0s).
 *   3. Also calculate the number of walls needed to contain each region. Note that 
 *      the number of walls is the number of edges between 1s in the region and 0s, 
 *      which can be greater than the number of unique 0s threatened (e.g., a 0 surrounded by three 1s needs 3 walls).
 *   4. Select the region that threatens the most unique 0s and quarantine it (mark as contained, e.g., value 2).
 *   5. For all other regions, simulate the virus spread by turning their threatened 0s into 1s.
 *   6. Repeat until no new cells are threatened.
 *
 * Time Complexity:  O((M * N)^2) - In the worst case, we might contain one cell at a time. Each day takes O(M * N) to scan and spread.
 * Space Complexity: O(M * N) - For visited arrays and storing regions.
 */

#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

class Solution {
public:
    int containVirus(vector<vector<int>>& isInfected) {
        int m = isInfected.size();
        int n = isInfected[0].size();
        int totalWalls = 0;
        
        vector<int> dirs = {-1, 0, 1, 0, -1};
        
        while (true) {
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            vector<vector<pair<int, int>>> regions;
            vector<set<pair<int, int>>> frontiers;
            vector<int> walls;
            
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (isInfected[i][j] == 1 && !visited[i][j]) {
                        vector<pair<int, int>> region;
                        set<pair<int, int>> frontier;
                        int wallCount = 0;
                        
                        vector<pair<int, int>> q;
                        q.push_back({i, j});
                        visited[i][j] = true;
                        
                        int head = 0;
                        while (head < q.size()) {
                            auto [r, c] = q[head++];
                            region.push_back({r, c});
                            
                            for (int d = 0; d < 4; ++d) {
                                int nr = r + dirs[d], nc = c + dirs[d+1];
                                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                                    if (isInfected[nr][nc] == 1 && !visited[nr][nc]) {
                                        visited[nr][nc] = true;
                                        q.push_back({nr, nc});
                                    } else if (isInfected[nr][nc] == 0) {
                                        frontier.insert({nr, nc});
                                        wallCount++;
                                    }
                                }
                            }
                        }
                        
                        regions.push_back(region);
                        frontiers.push_back(frontier);
                        walls.push_back(wallCount);
                    }
                }
            }
            
            if (regions.empty()) break;
            
            int quarantineIdx = -1;
            int maxThreat = 0;
            
            for (int i = 0; i < frontiers.size(); ++i) {
                if (frontiers[i].size() > maxThreat) {
                    maxThreat = frontiers[i].size();
                    quarantineIdx = i;
                }
            }
            
            if (quarantineIdx == -1) break; // No more 0s threatened
            
            totalWalls += walls[quarantineIdx];
            
            for (int i = 0; i < regions.size(); ++i) {
                if (i == quarantineIdx) {
                    for (auto& cell : regions[i]) {
                        isInfected[cell.first][cell.second] = 2; // contained
                    }
                } else {
                    for (auto& cell : frontiers[i]) {
                        isInfected[cell.first][cell.second] = 1; // spread
                    }
                }
            }
        }
        
        return totalWalls;
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
        vector<vector<int>> grid = {
            {0,1,0,0,0,0,0,1},
            {0,1,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0}
        };
        assert(solver.containVirus(grid) == 10);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> grid = {
            {1,1,1},
            {1,0,1},
            {1,1,1}
        };
        assert(solver.containVirus(grid) == 4);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3
    {
        vector<vector<int>> grid = {
            {1,1,1,0,0,0,0,0,0},
            {1,0,1,0,1,1,1,1,1},
            {1,1,1,0,0,0,0,0,0}
        };
        assert(solver.containVirus(grid) == 13);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
