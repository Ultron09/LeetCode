# [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Graphs](../../topics/graphs.md), [Trees & BST](../../topics/trees.md)

---

## 📌 Problem Statement

Given an `m x n` integers `matrix`, return the length of the longest increasing path in `matrix`.

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

### Example 1:
```
Input: matrix = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].
```

### Example 2:
```
Input: matrix = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
```

### Example 3:
```
Input: matrix = [[1]]
Output: 1
```

### Constraints:
- $m == \text{matrix.length}$
- $n == \text{matrix}[i].\text{length}$
- $1 \le m, n \le 200$
- $0 \le \text{matrix}[i][j] \le 2^{31} - 1$

---

## 💡 Intuition & Approach

### 1. Modeling the Matrix as a Directed Acyclic Graph (DAG)
- Consider each cell $(r, c)$ in the $m \times n$ matrix as a vertex in a directed graph.
- Add a directed edge from $(r, c) \to (nr, nc)$ if and only if $(nr, nc)$ is an orthogonally adjacent valid cell and $\text{matrix}[nr][nc] > \text{matrix}[r][c]$.
- **Acyclicity Property**: Since all transitions require moving to a strictly greater integer value, a path can never revisit an already traversed cell. Therefore, the resulting graph is guaranteed to be a **Directed Acyclic Graph (DAG)**. There is no risk of infinite cycles, and no explicit `visited` set is required for cycle prevention.

### 2. Top-Down Dynamic Programming with Memoization (DFS)
Let $DP[r][c]$ be the length of the longest increasing path starting at cell $(r, c)$:

$$DP[r][c] = 1 + \max \left(\{0\} \cup \{ DP[nr][nc] \mid (nr, nc) \in \text{adj}(r, c) \land \text{matrix}[nr][nc] > \text{matrix}[r][c] \}\right)$$

1. **Memoization Table**: Initialize a table `memo[m][n]` filled with zeros.
2. **Recursive Function `dfs(r, c)`**:
   - If `memo[r][c] != 0`, return the cached result.
   - Initialize `maxLength = 1`.
   - Explore all 4 orthogonal directions: up, down, left, right.
   - For each valid neighbor $(nr, nc)$ with $\text{matrix}[nr][nc] > \text{matrix}[r][c]$, update:
     $$\text{maxLength} = \max(\text{maxLength}, 1 + \text{dfs}(nr, nc))$$
   - Store and return `memo[r][c] = maxLength`.
3. **Global Maximum**: The final answer is $\max_{0 \le r < m, 0 \le c < n} DP[r][c]$.

### 3. Alternative: Kahn's Algorithm / Topological Sort (Bottom-Up BFS)
We can also calculate the in-degrees (number of strictly smaller adjacent neighbors) for all $m \times n$ cells, push all cells with in-degree 0 (local minima) into a queue, and peel off levels layer by layer. The number of BFS layers traversed equals the longest increasing path length. The memoized DFS approach is simpler, more direct, and has minimal memory overhead.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \cdot N)$
  - The graph has $V = M \cdot N$ vertices.
  - Each cell has at most 4 outgoing edges ($E \le 4 \cdot M \cdot N$).
  - With memoization, each state $(r, c)$ is computed exactly once, visiting each edge at most once.
  - Total time is $\mathcal{O}(V + E) = \mathcal{O}(M \cdot N)$.
- **Space Complexity:** $\mathcal{O}(M \cdot N)$
  - $\mathcal{O}(M \cdot N)$ space for the `memo` lookup matrix.
  - $\mathcal{O}(M \cdot N)$ worst-case call stack depth for a strictly increasing snake/spiral path spanning all cells.

---

## 🔍 Edge Cases Considered

- **Single Cell Matrix ($M = 1, N = 1$)**: Returns 1 (base path length).
- **All Equal Values**: No neighbor has a strictly greater value; all cells return 1.
- **Strictly Decreasing / Increasing Matrix**: Correctly traces the entire monotonic diagonal or snake path from minimum to maximum.
- **Large Values up to $2^{31} - 1$**: Handled natively with standard integer comparisons.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
