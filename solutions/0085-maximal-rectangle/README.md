# [85. Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), [Dynamic Programming](../../topics/dynamic-programming.md), [Monotonic Stack](../../topics/stack-and-queue.md), [Matrix](../../topics/stack-and-queue.md)

---

## 📌 Problem Statement

Given a `rows x cols` binary `matrix` filled with `'0'`s and `'1'`s, find the largest rectangle containing only `'1'`s and return its area.

### Example 1:
```
Input: matrix = [
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 6
Explanation: The maximal rectangle is formed by the 2x3 block in rows 1-2, cols 2-4, giving area = 6.
```

### Example 2:
```
Input: matrix = [["0"]]
Output: 0
```

### Example 3:
```
Input: matrix = [["1"]]
Output: 1
```

### Constraints:
- $\text{rows} == \text{matrix.length}$
- $\text{cols} == \text{matrix}[i]\text{.length}$
- $1 \le \text{rows}, \text{cols} \le 200$
- $\text{matrix}[i][j]$ is `'0'` or `'1'`.

---

## 💡 Intuition & Approach

### 1. Reduction to Largest Rectangle in Histogram
We can model each row of the 2D matrix as the baseline of a 1D histogram:
- Maintain an array `heights` of size `cols`.
- For each row $r$, update `heights[c]`:
  - If $\text{matrix}[r][c] == \text{'1'}$, then $\text{heights}[c] = \text{heights}[c] + 1$.
  - If $\text{matrix}[r][c] == \text{'0'}$, the streak is broken, so $\text{heights}[c] = 0$.

### 2. Monotonic Stack per Row ($\mathcal{O}(R \times C)$ Total)
- For every row $r$, evaluate the maximum rectangular area in `heights` using a monotonic increasing stack in $\mathcal{O}(C)$ time.
- Global maximum across all rows yields the maximal rectangle.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(R \times C)$ where $R = \text{rows}$ and $C = \text{cols}$. Each cell is processed in $\mathcal{O}(1)$ time.
- **Space Complexity:** $\mathcal{O}(C)$ auxiliary space for the height array and monotonic stack.

---

## 🔍 Edge Cases Considered

- **Single cell matrices** (`[["0"]]` $\to 0$, `[["1"]]` $\to 1$).
- **Sparse matrices with no rectangles**: Handled with area $= 0$.
- **All ones matrix** ($R \times C \to R \cdot C$).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
