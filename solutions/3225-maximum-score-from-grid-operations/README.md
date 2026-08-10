# [3225. Maximum Score From Grid Operations](https://leetcode.com/problems/maximum-score-from-grid-operations/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given a 2D matrix `grid` of size $n \times n$. Initially, all cells are colored white.

In one operation, you can select any cell $(i, j)$ and color black all cells in the $j$-th column from the top row ($0$) down to the $i$-th row.

The **grid score** is the sum of all `grid[i][j]` such that cell $(i, j)$ is **white** and has a **horizontally adjacent black cell**.

Return the **maximum score** achievable after performing any number of operations.

### Example 1:
```
Input: grid = [[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]
Output: 11
Explanation:
- Column 1 colored down to row 3.
- Column 4 colored down to the last row.
- Score = grid[3][0] + grid[1][2] + grid[3][3] = 5 + 3 + 3 = 11.
```

### Example 2:
```
Input: grid = [[10,9,0,0,15],[7,1,0,8,0],[5,20,0,11,0],[0,0,0,1,2],[8,12,1,10,3]]
Output: 94
```

### Constraints:
- $1 \le n == \text{grid.length} == \text{grid}[i].\text{length} \le 100$
- $0 \le \text{grid}[i][j] \le 10^9$

---

## 💡 Intuition & Approach

### 1. Column State Formulation
Since operations color top-down, each column $i$ is uniquely characterized by its **black height** $h_i \in [0, n]$ (the first $h_i$ cells are black, and the remaining $n - h_i$ cells are white).

A white cell at $(r, i)$ gets scored if $h_{i-1} > r$ or $h_{i+1} > r$. Thus, the score of column $i$ depends on three consecutive column heights: $(h_{i-1}, h_i, h_{i+1})$.

### 2. State Definition & $O(n^4) \to O(n^3)$ Optimization
Let `dp[h_curr][h_prev]` be the maximum score up to the current column $i$ with heights $h_{curr}$ for column $i$ and $h_{prev}$ for column $i - 1$.

- **Case 1: $h_{curr} \le h_{prev}$**
  $$dp[i][h_{curr}][h_{prev}] = \max_{0 \le k \le n} dp[i-1][h_{prev}][k] + S_{i, h_{prev}} - S_{i, h_{curr}}$$
  Using precomputed suffix maximums `prevSuffixMax[h_prev][0]`, this evaluates in $\mathcal{O}(1)$.

- **Case 2: $h_{curr} > h_{prev}$**
  When transitioning from height $k$ of column $i - 2$:
  - For $k > h_{curr}$: no additional white cells are newly covered $\implies$ covered by `prevSuffixMax[h_prev][h_{curr}]`.
  - For $k \le h_{curr}$: the newly covered region contributes $(S_{i-1, h_{curr}} - S_{i-1, h_{prev}})$, while subtracting any overlap from $k$ $\implies$ covered by `prevMax[h_prev][h_{curr}]`.
  $$\max\left(\text{prevSuffixMax}[h_{prev}][h_{curr}], \, \text{prevMax}[h_{prev}][h_{curr}] + S_{i-1, h_{curr}} - S_{i-1, h_{prev}}\right)$$

By maintaining `prevMax` and `prevSuffixMax` arrays for each column, all inner state transitions run in $\mathcal{O}(1)$, reducing total time complexity from $\mathcal{O}(n^4)$ to **$\mathcal{O}(n^3)$**.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(n^3)$
  - $n+1$ column iterations.
  - In each column, precomputing `prevMax` and `prevSuffixMax` takes $\mathcal{O}(n^2)$.
  - Updating all $(h_{curr}, h_{prev})$ states takes $\mathcal{O}(n^2)$.
  - Total operations $\le 100^3 = 10^6$ ($< 5$ ms in C++).
- **Space Complexity:** $\mathcal{O}(n^2)$
  - Rolling 2D DP array and auxiliary maximum tables of size $(n + 1) \times (n + 1)$.

---

## 🔍 Edge Cases Considered

- **$n = 1$**: Single cell matrix returns 0 (no adjacent columns).
- **First column ($i = 1$) and last virtual column ($i = n + 1$)**: Handled seamlessly by setting boundaries to 0.
- **Large Cell Values ($\le 10^9$)**: Handled using `long long` for all DP states and prefix sums to avoid 64-bit overflow.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
