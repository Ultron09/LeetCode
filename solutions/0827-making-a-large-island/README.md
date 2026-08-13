# [827. Making A Large Island](https://leetcode.com/problems/making-a-large-island/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an `n x n` binary matrix `grid`. You are allowed to change **at most one** `0` to be `1`.

Return the size of the largest island in `grid` after applying this operation.

An **island** is a 4-directionally connected group of `1`s.

### Example 1:
```
Input: grid = [[1,0],[0,1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
```

### Example 2:
```
Input: grid = [[1,1],[1,0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
```

### Example 3:
```
Input: grid = [[1,1],[1,1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.
```

### Constraints:
- `n == grid.length`
- `n == grid[i].length`
- `1 <= n <= 500`
- `grid[i][j]` is either `0` or `1`.

---

## 💡 Intuition & Approach

This is a classic connected components problem that we can solve perfectly using a two-pass BFS/DFS mapping strategy.

1. **Pass 1 - Component Labeling & Area Calculation:**
   Traverse the grid. Every time an unvisited `1` is encountered, run a BFS (or DFS) to map the entire connected island.
   Instead of just marking the cell as `visited`, we assign the cells a unique `component_id` (starting from 2, so it doesn't clash with the original `0` and `1`). 
   During the BFS, we count the total `area` of that island and store the result in an array mapped by `component_id`: `area[component_id] = current_area`.
   We also track the maximum island area encountered just in case the grid is already fully connected without flips.

2. **Pass 2 - Evaluating Flips:**
   Iterate through the grid again, this time looking at all the `0`s.
   For each `0`, we can tentatively flip it to a `1`. 
   If we do, the new island area will be `1` (for the flipped cell itself) plus the sum of the areas of any neighboring islands.
   We inspect the cell's 4 adjacent neighbors (Up, Down, Left, Right). For any valid neighbor that belongs to an island, we collect its `component_id`. 
   *Crucial Detail:* Since an island might wrap around and touch multiple sides of our `0`, we must use a small hash set (or a manual `seen` array) to deduplicate the neighboring `component_id`s. We only add an island's area to our total **once**.
   We evaluate the potential area for every `0` and return the global maximum found.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$ — Each cell in the `N x N` grid is processed a constant number of times during the BFS traversal and constant number of times during the flip check.
- **Space Complexity:** $\mathcal{O}(N^2)$ — The space is determined by the size of the BFS queue (which could theoretically hold $\approx N^2 / 2$ elements for a checkerboard matrix) and the sizes of the `area` mapping array ($\approx N^2 / 2$).

---

## 🔍 Edge Cases Considered

- **The grid is filled entirely with `1`s**: The first pass detects an island of size $N^2$. The second pass is skipped. Yields $N^2$.
- **The grid is filled entirely with `0`s**: The first pass detects nothing. The second pass evaluates flips on all cells yielding $1$. Yields $1$.
- **A `0` is adjacent to the same island from multiple sides**: The `seen` duplicate-filtering effectively handles this, preventing the area from being double-counted.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
