# [980. Unique Paths III](https://leetcode.com/problems/unique-paths-iii/)

**Difficulty:** `Hard`  
**Topics:** [Array](../../topics/arrays-and-hashing.md), [Backtracking](../../topics/backtracking.md), [Bit Manipulation](../../topics/bit-manipulation.md), Matrix

---

## 📌 Problem Statement

You are given an `m x n` integer array `grid` where `grid[i][j]` could be:
- `1` representing the starting square. There is exactly one starting square.
- `2` representing the ending square. There is exactly one ending square.
- `0` representing empty squares we can walk over.
- `-1` representing obstacles that we cannot walk over.

Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.

### Example 1:
```
Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
```

### Constraints:
- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 20`
- `1 <= m * n <= 20`
- `-1 <= grid[i][j] <= 2`
- There is exactly one starting cell and one ending cell.

---

## 💡 Intuition & Approach

The constraints hint heavily at a brute force or **Backtracking (DFS)** solution. With `m * n <= 20`, the grid is tiny enough that we can explicitly search every valid Hamiltonian Path across the empty squares.

1. **Pre-computation**: First, traverse the entire grid to count the total number of empty squares (`0`s). Also, pinpoint the starting coordinates `(start_x, start_y)`.
2. **Backtracking (DFS)**:
   - Start exploring from `(start_x, start_y)`, carrying down a counter initialized to `zeros + 1` (accounting for the start cell itself).
   - Upon moving into a new empty cell, safely decrement the target step counter.
   - Prevent infinite loops or self-intersection by temporarily turning the current square into an obstacle (`-1`) while traversing its 4 neighboring neighbors. Backtrack it afterwards.
3. **Completion**: If we step onto the end square `2`, immediately verify if our target counter has hit `0`. If so, we successfully touched all non-obstacle cells precisely once—register it as a valid path!

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(3^{M \times N})$ — In the absolute worst case, we possess up to 3 valid branching directions out of each cell after eliminating the single backtrack direction. Considering $M \times N \le 20$, $3^{20}$ is relatively large, but practically, the maze constraints and dead-ends prune this bound significantly.
- **Space Complexity:** $\mathcal{O}(M \times N)$ — To encompass the recursion stack proportional to the maximal depth (spanning the whole grid).

---

## 🔍 Edge Cases Considered

- Unreachable `2`: The DFS naturally prunes and eventually terminates yielding `0` routes.
- Walled off Empty Squares: The target zeroes left will strictly be $> 0$ once the DFS manages to hit `2`, appropriately discarding the incomplete paths.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
