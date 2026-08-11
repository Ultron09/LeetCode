# [174. Dungeon Game](https://leetcode.com/problems/dungeon-game/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Matrix](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of `m x n` rooms laid out in a 2D grid. Our valiant knight was initially positioned in the top-left room and must fight his way through dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to `0` or below, he dies immediately.

Some of the rooms are guarded by demons (negative integers), so the knight loses health upon entering these rooms; other rooms are either empty (`0`) or contain magic orbs that increase the knight's health (positive integers).

To reach the princess as quickly as possible, the knight decides to move **only rightward or downward** in each step.

Return the **knight's minimum initial health** so that he can rescue the princess.

### Example 1:
```
Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
Output: 7
Explanation: The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.
```

### Example 2:
```
Input: dungeon = [[0]]
Output: 1
```

### Constraints:
- $m == \text{dungeon.length}$
- $n == \text{dungeon}[i]\text{.length}$
- $1 \le m, n \le 200$
- $-1000 \le \text{dungeon}[i][j] \le 1000$

---

## 💡 Intuition & Approach

### 1. Why Reverse Dynamic Programming?
In forward DP from $(0, 0)$ to $(m - 1, n - 1)$, we face a state conflict: maximizing accumulated health does not necessarily minimize the initial health required at the start because early severe drops might be fatal.

Working backwards from the destination $(m - 1, n - 1)$ to the starting point $(0, 0)$ resolves this cleanly:
- Let $dp[i][j]$ denote the minimum health points the knight must possess **immediately before entering** room $(i, j)$ to safely complete the quest.
- Upon leaving room $(i, j)$, the knight moves either to $(i + 1, j)$ or $(i, j + 1)$, requiring at least:
  $$\text{minExitHP} = \min(dp[i + 1][j], dp[i][j + 1])$$
- Inside cell $(i, j)$, the health change is $\text{dungeon}[i][j]$. Therefore, before entering $(i, j)$, the knight must have:
  $$dp[i][j] = \max(1, \text{minExitHP} - \text{dungeon}[i][j])$$
- The $\max(1, \cdot)$ constraint guarantees the knight's HP never drops $\le 0$.

### 2. Space Optimization to $\mathcal{O}(N)$
Since $dp[i][j]$ depends only on $dp[i + 1][j]$ (the previous row) and $dp[i][j + 1]$ (the current row), we can compress the 2D matrix into a 1D rolling array of size $n + 1$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \cdot N)$ where $M, N \le 200$ (each grid cell processed in $\mathcal{O}(1)$ time).
- **Space Complexity:** $\mathcal{O}(N)$ auxiliary space using 1D DP table.

---

## 🔍 Edge Cases Considered

- **Single Room**: Handled $\implies \max(1, 1 - \text{dungeon}[0][0])$.
- **All Negative Values**: Accumulates necessary buffer without underflow.
- **Large Positive Buffs**: Correctly clamped by $\max(1, \cdot)$ so required initial health never falls below 1.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
