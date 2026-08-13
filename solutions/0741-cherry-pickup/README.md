# [741. Cherry Pickup](https://leetcode.com/problems/cherry-pickup/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

You are given an `n × n` grid where each cell is `0` (empty), `1` (cherry), or `-1` (thorn).

- Travel from `(0, 0)` to `(n-1, n-1)` moving only **right** or **down**.
- Then return from `(n-1, n-1)` to `(0, 0)` moving only **left** or **up**.
- Cherries are picked up when you pass through them (cell becomes 0).
- If no valid path exists, return 0.

Return the **maximum number of cherries** collectible.

### Example 1:
```
Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
Output: 5
```

### Example 2:
```
Input: grid = [[1,1,-1],[1,-1,1],[-1,1,1]]
Output: 0
```

### Constraints:
- $1 \le n \le 50$
- `grid[i][j]` is `-1`, `0`, or `1`
- `grid[0][0] != -1`, `grid[n-1][n-1] != -1`

---

## 💡 Intuition & Approach

### 1. Why Greedy Fails

The naive approach — find the best path forward, pick cherries, then find the best path back — fails because the first path's greedy choice can block better combined pickups. Consider:

```
1 1 1 0 0
0 0 1 0 1
1 0 1 0 0
0 0 1 1 1
```

A greedy first path might take a route that leaves the return path with few cherries, even though a different pair of paths would collect more total.

### 2. Key Insight: Two Simultaneous Forward Paths

**The return trip (going left/up) is equivalent to a second forward trip (going right/down).** Instead of one round trip, model it as **two people walking simultaneously** from `(0,0)` to `(n-1,n-1)`, both moving only right or down. If they step on the same cherry cell, it's counted only once.

### 3. DP State Design

Since both persons take exactly $t = r + c$ steps to reach position $(r, c)$:

$$dp[t][r_1][r_2] = \text{max cherries when both have taken } t \text{ steps}$$

- Person 1 is at $(r_1, t - r_1)$
- Person 2 is at $(r_2, t - r_2)$
- $t$ ranges from $0$ to $2(n-1)$

**Symmetry optimization**: Since the two persons are interchangeable, we enforce $r_1 \le r_2$, cutting the state space roughly in half.

### 4. Transition

At each step, each person independently moves right (row stays) or down (row + 1):

$$dp[t][r_1][r_2] = \max_{(pr_1, pr_2) \in \text{prev}} dp[t-1][pr_1][pr_2] + \text{cherries}(r_1, r_2, t)$$

where `cherries` counts the cherry at both positions (once if they coincide).

### 5. Step-by-step on Example 1

```
Grid:  0 1 -1     t=0: dp[0][0] = 0 (grid[0][0]=0)
       1 0 -1     t=1: dp[1][0] = 1, dp[0][1] = 1+1 = 2 (both at diff cells)
       1 1  1     ...
                   t=4: dp[2][2] = 5 ✓
```

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^3)$
  - $2N - 1$ time steps × $N^2$ states per step × $O(1)$ transitions.
  - With $N = 50$: $\sim 99 \times 2500 = 247{,}500$ operations.
- **Space Complexity:** $\mathcal{O}(N^2)$
  - Rolling array: only keep the current and previous time step's $N \times N$ table.

---

## 🔍 Edge Cases Considered

- **No valid path** (`[[1,1,-1],[1,-1,1],[-1,1,1]]` → 0): All paths blocked by thorns.
- **1×1 grid** (`[[1]]` → 1): Start = end, pick the single cherry.
- **All zeros** (`[[0,0],[0,0]]` → 0): No cherries to collect.
- **All cherries** (`[[1,1,1],[1,1,1],[1,1,1]]` → 8): Two paths cover 8 of 9 cells.
- **Thorns at edges**: Handled by checking `grid[r][c] == -1` → skip state.

---

## 🔗 Related Problems

- [1463. Cherry Pickup II](https://leetcode.com/problems/cherry-pickup-ii/) — Two robots, same "simultaneous paths" idea but top-to-bottom
- [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) — Single-path grid DP (simpler variant)
- [174. Dungeon Game](../0174-dungeon-game/README.md) — Reverse-direction grid DP

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
