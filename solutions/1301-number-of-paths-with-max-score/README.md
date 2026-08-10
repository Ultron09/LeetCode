# [1301. Number of Paths with Max Score](https://leetcode.com/problems/number-of-paths-with-max-score/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given a square `board` of characters. You can move on the board starting at the bottom right square marked with `'S'`.

You need to reach the top left square marked with `'E'`. The rest of the squares are labeled either with a numeric character `'1'`, `'2'`, ..., `'9'` or with an obstacle `'X'`.

In one move you can go **up**, **left** or **up-left (diagonally)** only if there is no obstacle there.

Return a list of two integers:
1. The **maximum sum** of numeric characters you can collect.
2. The **number of paths** that yield this maximum sum, taken modulo $10^9 + 7$.

If there is no valid path from `'S'` to `'E'`, return `[0, 0]`.

### Example 1:
```
Input: board = ["E23","2X2","12S"]
Output: [7,1]
Explanation:
- Path 1: S -> 2 -> X (blocked)
- Optimal Path: (2,2) -> (2,1)[2] -> (1,0)[2] -> (0,0)[E]: sum = 2 + 2 + 3 = 7, count = 1.
```

### Example 2:
```
Input: board = ["E12","1X1","21S"]
Output: [4,2]
Explanation:
Two distinct paths yield the maximum sum of 4:
- S -> (2,1)[1] -> (1,0)[1] -> (0,1)[1] -> E (sum = 4)
- S -> (1,2)[1] -> (0,2)[2] -> (0,1)[1] -> E (sum = 4)
```

### Example 3:
```
Input: board = ["E11","XXX","11S"]
Output: [0,0]
Explanation:
All paths from 'S' to 'E' are blocked by obstacles 'X'.
```

### Constraints:
- $2 \le \text{board.length} == \text{board}[i].\text{length} \le 100$

---

## 💡 Intuition & Approach

### 1. Dual-State Dynamic Programming
Each cell $(r, c)$ requires tracking two values simultaneously:
1. $\text{maxScore}(r, c)$: The maximum numeric sum obtainable from `'S'` to $(r, c)$.
2. $\text{ways}(r, c)$: The number of distinct paths that achieve $\text{maxScore}(r, c)$.

From any cell $(r, c)$, valid moves towards $(0, 0)$ are:
- $(r - 1, c)$ (up)
- $(r, c - 1)$ (left)
- $(r - 1, c - 1)$ (up-left)

Equivalently, arriving at $(r, c)$ from `'S'` $(n-1, n-1)$ can only come from its 3 bottom-right neighbors:
- $(r + 1, c)$ (down)
- $(r, c + 1)$ (right)
- $(r + 1, c + 1)$ (down-right)

### 2. State Transitions
Initialize $\text{dp}[n-1][n-1] = \{0, 1\}$ and all other cells to $\{-1, 0\}$ (unreachable).

Traverse the board from bottom-right $(n-1, n-1)$ to top-left $(0, 0)$:
1. If $\text{board}[r][c] == \text{'X'}$, skip.
2. Find the highest incoming score among reachable neighbors $(nr, nc) \in \{(r+1, c), (r, c+1), (r+1, c+1)\}$:
   $$\text{bestScore} = \max_{(nr, nc)} \text{dp}[nr][nc].\text{score}$$
3. Sum the path counts of all neighbors that match $\text{bestScore}$:
   $$\text{ways}(r, c) = \sum_{(nr, nc) : \text{score} == \text{bestScore}} \text{dp}[nr][nc].\text{ways} \pmod{10^9 + 7}$$
4. Add current cell numeric value:
   $$\text{score}(r, c) = \text{bestScore} + (\text{board}[r][c] == \text{'E'} ? 0 : \text{board}[r][c] - \text{'0'})$$

### 3. Result Formulation
- If $\text{dp}[0][0].\text{score} == -1$ (no path exists), return `[0, 0]`.
- Otherwise, return `[dp[0][0].score, dp[0][0].ways]`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$
  - $N \le 100 \implies N^2 \le 10^4$ cells.
  - Each cell performs at most $3$ constant-time neighbor checks.
  - Total operations $\approx 3 \times 10^4$ ($< 1$ ms in C++).
- **Space Complexity:** $\mathcal{O}(N^2)$ for the 2D DP table (can be optimized to $\mathcal{O}(N)$ using rolling rows).

---

## 🔍 Edge Cases Considered

- **Completely Blocked Board**: Handled cleanly by returning `[0, 0]` when top-left cell remains unreachable.
- **Multiple Equal-Score Paths Merging**: Correctly sums up path counts modulo $10^9 + 7$.
- **Starting/Destination Cells ('S' / 'E')**: Treated with numeric value $0$ without altering collected scores.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
