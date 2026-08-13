# [778. Swim in Rising Water](https://leetcode.com/problems/swim-in-rising-water/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), [Heaps & Priority Queues](../../topics/heaps-and-priority-queues.md), Binary Search

---

## 📌 Problem Statement

You are given an `n x n` integer matrix `grid` where each value `grid[i][j]` represents the elevation at that point `(i, j)`.

It starts raining, and water gradually rises over time. At time `t`, the water level is `t`, meaning any cell with elevation less than equal to `t` is submerged or reachable.

You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most `t`. You can swim infinite distances in zero time. You must stay within the boundaries of the grid during your swim.

Return the minimum time until you can reach the bottom right square `(n - 1, n - 1)` if you start at the top left square `(0, 0)`.

### Example 1:
```
Input: grid = [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.
```

### Constraints:
- `n == grid.length`
- `n == grid[i].length`
- `1 <= n <= 50`
- `0 <= grid[i][j] < n^2`
- Each value `grid[i][j]` is unique.

---

## 💡 Intuition & Approach

This is a classic "Bottleneck Shortest Path" problem. We want to find a path from the start to the end that minimizes the maximum edge weight (or node elevation) encountered.

There are several ways to solve this: Binary Search + BFS/DFS, Union-Find by sorting the cells by elevation, or Dijkstra's Algorithm. Dijkstra's is generally the most robust and natural for this phrasing.

**Dijkstra's Algorithm with Priority Queue:**
1. Maintain a min-heap of vectors containing `{max_elevation_so_far, row, col}`.
2. Initialize the heap with `{grid[0][0], 0, 0}` and mark `(0,0)` as visited.
3. Continuously pop the cell with the minimum `max_elevation_so_far` from the heap. This guarantees that when we pop the destination cell, we have found the optimal (lowest possible maximum elevation) path to it.
4. If we haven't reached the end, look at all 4-directional unvisited neighbors. For each neighbor, the new path bottleneck is `max(current_max_elevation, grid[neighbor_row][neighbor_col])`. Push this new state into the heap and mark the neighbor as visited.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2 \log(N^2)) = \mathcal{O}(N^2 \log N)$ — There are $N^2$ cells. In the worst case, each cell is added to and removed from the priority queue once. Heap operations take logarithmic time with respect to the heap size (which is at most $N^2$).
- **Space Complexity:** $\mathcal{O}(N^2)$ — For the `visited` array and the Priority Queue which can grow up to the number of cells in the grid.

---

## 🔍 Edge Cases Considered

- **Start Cell is Highest**: If `grid[0][0]` happens to be the global maximum along the path, it is correctly captured right at initialization, and all subsequent `max()` comparisons handle it transparently.
- **Trivial/Small Grid**: `n=1` would conceptually be handled without iteration, though constraints say `n >= 1`. If `n=1`, the start is the target and the algorithm immediately returns.
- **Serpentine Paths**: A zig-zagging long path of low elevations is correctly favored over a short path blocked by a high elevation due to the greedy nature of Dijkstra's algorithm.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
