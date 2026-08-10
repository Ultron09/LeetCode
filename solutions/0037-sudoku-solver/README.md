# [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)

**Difficulty:** `Hard`  
**Topics:** [Backtracking](../../topics/backtracking.md), [Bit Manipulation](../../topics/bit-manipulation.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:
1. Each of the digits `1-9` must occur exactly once in each row.
2. Each of the digits `1-9` must occur exactly once in each column.
3. Each of the digits `1-9` must occur exactly once in each of the 9 `3x3` sub-boxes of the grid.

The `'.'` character indicates empty cells.

### Example 1:
```
Input: board = [
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]

Output: [
  ["5","3","4","6","7","8","9","1","2"],
  ["6","7","2","1","9","5","3","4","8"],
  ["1","9","8","3","4","2","5","6","7"],
  ["8","5","9","7","6","1","4","2","3"],
  ["4","2","6","8","5","3","7","9","1"],
  ["7","1","3","9","2","4","8","5","6"],
  ["9","6","1","5","3","7","2","8","4"],
  ["2","8","7","4","1","9","6","3","5"],
  ["3","4","5","2","8","6","1","7","9"]
]
```

### Constraints:
- `board.length == 9`
- `board[i].length == 9`
- `board[i][j]` is a digit `'1'-'9'` or `'.'`.
- It is guaranteed that the input board has **only one solution**.

---

## 💡 Intuition & Approach

### 1. Bitmask State Representation
Maintain 9-bit bitmasks for each row, column, and $3 \times 3$ box:
- `rowMask[r]`, `colMask[c]`, `boxMask[(r/3)*3 + (c/3)]`
- Available candidate digits for cell $(r, c)$ are calculated in $\mathcal{O}(1)$ via:
  $$\text{cand} = \sim(\text{rowMask}[r] \mid \text{colMask}[c] \mid \text{boxMask}[\text{box}]) \ \& \ 0\text{x}1\text{FF}$$

### 2. Minimum Remaining Values (MRV) Heuristic
Rather than scanning cells linearly in row-major order, pick the unassigned cell with the **fewest candidate digits** (`__builtin_popcount(cand)`):
- If any cell has 0 available candidates, immediately backtrack (fail fast).
- Cells with only 1 candidate are filled deterministically first, drastically cutting down the search branching factor.

### 3. Bit Manipulation Choice Iteration
- Extract least significant bit `lsb = cand & -cand` and calculate digit `__builtin_ctz(lsb)`.
- Set bit in row/column/box masks and recursively search.
- Backtrack by XORing the bitmask upon return.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(9^M)$ where $M \le 81$ is the number of blank cells. With bitmask MRV pruning, typical boards solve in $< 1$ ms.
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space (maximum recursion depth bounded by 81 on a fixed $9 \times 9$ grid).

---

## 🔍 Edge Cases Considered

- **Board with single choice cells**: MRV resolves them immediately without branching.
- **Backtrack branch failure**: Cleanly restores board state and bitmasks.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
