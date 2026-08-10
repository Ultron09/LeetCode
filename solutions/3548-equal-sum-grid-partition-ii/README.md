# [3548. Equal Sum Grid Partition II](https://leetcode.com/problems/equal-sum-grid-partition-ii/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Prefix Sum](../../topics/arrays-and-hashing.md), [Matrix](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an $m \times n$ matrix `grid` of positive integers. Determine if it is possible to make either **one horizontal** or **one vertical cut** on the grid such that:
1. Each of the two resulting sections formed by the cut is **non-empty**.
2. The sum of elements in both sections is **equal**, or can be made equal by **discounting at most one single cell** in total (from either section).
3. If a cell is discounted, the rest of that section **must remain 4-directionally connected**.

Return `true` if such a partition exists; otherwise, return `false`.

### Example 1:
```
Input: grid = [[1,4],[2,3]]
Output: true
Explanation: Horizontal cut after row 0 gives 1+4 = 5 and 2+3 = 5.
```

### Example 2:
```
Input: grid = [[1,2],[3,4]]
Output: true
Explanation: Vertical cut after col 0 gives left=4 and right=6. Discounting 2 from the right section gives 6 - 2 = 4 (connected).
```

### Example 3:
```
Input: grid = [[1,2,4],[2,3,5]]
Output: false
Explanation: Discounting 3 from bottom [2,3,5] splits it into [2] and [5] (disconnected).
```

### Example 4:
```
Input: grid = [[4,1,8],[3,2,6]]
Output: false
```

### Constraints:
- $1 \le m == \text{grid.length} \le 10^5$
- $1 \le n == \text{grid}[i]\text{.length} \le 10^5$
- $2 \le m \times n \le 10^5$
- $1 \le \text{grid}[i][j] \le 10^5$

---

## 💡 Intuition & Approach

### 1. Unified Cut Evaluation via Transposition
A vertical cut on an $M \times N$ grid is identical to a horizontal cut on the $N \times M$ transposed grid. We only need to implement a robust `checkHorizontal` function.

### 2. Connectivity Rules for a Single Cell Discount
When discounting a cell with value $\text{diff} = |\text{topSum} - \text{botSum}|$ from an $R \times C$ rectangular block:
- **Case $R = 1, C > 1$ (1D Row)**:
  Only the two outer endpoints $(0, 0)$ and $(0, C - 1)$ keep the remaining $1 \times (C-1)$ cells connected.
- **Case $C = 1, R > 1$ (1D Column)**:
  Only the two outer endpoints $(0, 0)$ and $(R - 1, 0)$ keep the remaining $(R-1) \times 1$ cells connected.
- **Case $R \ge 2, C \ge 2$ (2D Rectangle)**:
  Removing **any single cell** leaves the remaining cells fully 4-directionally connected (the outer boundary ring and adjacent layers preserve paths around any removed cell). We simply check if $\text{diff}$ exists in the section's frequency map.

### 3. Prefix Sum and Frequency Tracking
- Maintain running prefix sums for top and bottom partitions.
- Use hash maps `topCount` and `bottomCount` to track available cell values as we sweep through row partition boundaries from top to bottom.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \cdot N)$
  - Computing initial sums and populating frequency map: $\mathcal{O}(M \cdot N)$.
  - Sweeping row cuts: each cell is inserted into `topCount` and erased from `bottomCount` exactly once $\implies \mathcal{O}(M \cdot N)$.
  - Transposition and second pass: $\mathcal{O}(M \cdot N)$.
  - Total time $< 15$ ms in C++.
- **Space Complexity:** $\mathcal{O}(M \cdot N)$ auxiliary space for frequency maps and transposed grid.

---

## 🔍 Edge Cases Considered

- **1D strips ($1 \times N$ or $M \times 1$)**: Strict endpoint validation prevents false-positive disconnected partitions.
- **Exact zero-discount cuts**: Handled immediately when $\text{topSum} == \text{botSum}$.
- **Large sums ($10^5 \times 10^5 = 10^{10}$)**: 64-bit `long long` accumulators avoid integer overflow.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
