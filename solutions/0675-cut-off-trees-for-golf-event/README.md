# [675. Cut Off Trees for Golf Event](https://leetcode.com/problems/cut-off-trees-for-golf-event/)

**Difficulty:** `Hard`  
**Topics:** [Breadth-First Search](../../topics/graphs.md), [Graphs](../../topics/graphs.md), [Array](../../topics/arrays-and-hashing.md), [Matrix](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an `m x n` matrix. In this matrix:
- `0` means the cell cannot be walked through (obstacle).
- `1` represents an empty cell that can be walked through.
- A number greater than `1` represents a tree with that height (which can also be walked through).

You must cut off the trees in **strictly increasing order of their height**. When you cut off a tree, the value at its cell becomes `1` (an empty walkable cell).

Starting from `(0, 0)`, return the **minimum steps** you need to walk to cut off all the trees. If you cannot cut off all the trees, return `-1`.

### Example 1:
```
Input: forest = [
  [1, 2, 3],
  [0, 0, 4],
  [7, 6, 5]
]
Output: 6
Explanation:
Start at (0,0) -> cut tree 2 at (0,1) [1 step]
-> cut tree 3 at (0,2) [1 step]
-> cut tree 4 at (1,2) [1 step]
-> cut tree 5 at (2,2) [1 step]
-> cut tree 6 at (2,1) [1 step]
-> cut tree 7 at (2,0) [1 step]
Total steps = 6.
```

### Example 2:
```
Input: forest = [
  [1, 2, 3],
  [0, 0, 0],
  [7, 6, 5]
]
Output: -1
Explanation: Trees in the bottom row cannot be reached due to obstacles in the middle row.
```

### Example 3:
```
Input: forest = [
  [2, 3, 4],
  [0, 0, 5],
  [8, 7, 6]
]
Output: 6
Explanation: You can cut off the first tree at (0, 0) in 0 steps before moving.
```

### Constraints:
- `m == forest.length`
- `n == forest[i].length`
- $1 \le m, n \le 50$
- $0 \le \text{forest}[i][j] \le 10^9$
- Heights of all trees are distinct.

---

## 💡 Intuition & Approach

### 1. Deterministic Target Ordering
Because trees must be cut in strictly ascending order of their heights:
1. Scan the entire grid and extract all tree cells `(height, row, col)` where `forest[r][c] > 1`.
2. Sort all extracted tree tuples in ascending order of `height`.
3. The sequence of destinations is fixed and unique: $\text{Tree}_1 \to \text{Tree}_2 \to \dots \to \text{Tree}_K$.

### 2. Multi-Stage BFS Shortest Path
Between each consecutive pair of waypoints $\text{curr} \to \text{target}$:
- Run standard unweighted Breadth-First Search (BFS) on the grid graph.
- A cell $(r, c)$ is walkable if $\text{forest}[r][c] \neq 0$ (cells with uncut or cut trees are both walkable).
- If any target is unreachable ($\text{BFS} = -1$), the entire mission is impossible; return `-1` immediately.
- Accumulate the shortest path steps into `totalSteps`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(T \cdot M \cdot N) = \mathcal{O}(M^2 \cdot N^2)$
  - Number of trees $T \le M \cdot N \le 2500$.
  - Each BFS visits at most $M \cdot N \le 2500$ cells.
  - Sorting trees takes $\mathcal{O}(T \log T)$.
  - Total operations $\le 2500 \times 2500 \approx 6.25 \times 10^6 \implies < 40\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(M \cdot N)$
  - BFS visited matrix and queue.

---

## 🔍 Edge Cases Considered

- **Tree at $(0, 0)$**: Initial BFS evaluates in $0$ steps without moving.
- **Starting on an Obstacle (`forest[0][0] == 0`)**: Any tree $> 0$ will immediately return `-1`.
- **Single Tree in Forest**: Handled in $\mathcal{O}(M \cdot N)$ with single BFS.
- **Disconnected Components**: Unreachable trees immediately abort and return `-1`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
