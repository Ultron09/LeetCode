# [668. Kth Smallest Number in Multiplication Table](https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

Nearly everyone has used the Multiplication Table. The multiplication table of size `m x n` is an integer matrix `mat` where `mat[i][j] == i * j` (1-indexed).

Given three integers `m`, `n`, and `k`, return the **$k^{\text{th}}$ smallest element** in the `m x n` multiplication table.

### Example 1:
```
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
| 2 | 4 | 6 |
+---+---+---+
| 3 | 6 | 9 |
+---+---+---+

Input: m = 3, n = 3, k = 5
Output: 3
Explanation: The 5th smallest number is 3 (elements in sorted order: [1, 2, 2, 3, 3, 4, 6, 6, 9]).
```

### Example 2:
```
Input: m = 2, n = 3, k = 6
Output: 6
Explanation: The 6th smallest number is 6.
```

### Constraints:
- $1 \le m, n \le 3 \times 10^4$
- $1 \le k \le m \times n$

---

## 💡 Intuition & Approach

### 1. Search on Answer (Monotonic Counting)
Directly sorting or generating the entire table of size $m \times n \le 9 \times 10^8$ is infeasible due to time and memory limits.

However, the problem exhibits a powerful **monotonic property**:
- Let $f(x)$ be the number of elements in the multiplication table that are $\le x$.
- As $x$ increases from $1$ to $m \times n$, $f(x)$ is **monotonically non-decreasing**.
- The $k^{\text{th}}$ smallest number is the smallest integer $x$ such that $f(x) \ge k$.

### 2. $\mathcal{O}(\min(m, n))$ Counting Predicate
In row $i$ ($1 \le i \le m$), the values are $i \times 1, i \times 2, \dots, i \times n$.
The number of elements $\le x$ in row $i$ is:
$$\text{count}_i = \min\left(n, \left\lfloor \frac{x}{i} \right\rfloor\right)$$

Summing across all rows gives:
$$f(x) = \sum_{i=1}^{m} \min\left(n, \left\lfloor \frac{x}{i} \right\rfloor\right)$$

By swapping $m$ and $n$ if $m > n$, we evaluate $f(x)$ in $\mathcal{O}(\min(m, n))$ steps.

### 3. Binary Search Range
- $\text{low} = 1$, $\text{high} = m \times n$.
- At each step, test $\text{mid} = \text{low} + \lfloor(\text{high} - \text{low}) / 2\rfloor$.
- If $f(\text{mid}) \ge k$, record $\text{mid}$ as a candidate answer and search lower ($\text{high} = \text{mid} - 1$).
- Otherwise, search higher ($\text{low} = \text{mid} + 1$).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\min(m, n) \cdot \log(m \cdot n))$
  - The binary search interval $[1, m \cdot n]$ requires $\log_2(9 \times 10^8) \approx 30$ iterations.
  - Each iteration performs $\min(m, n) \le 3 \times 10^4$ operations.
  - Total operations $\approx 30 \times 3 \times 10^4 = 9 \times 10^5 \implies < 5\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space.

---

## 🔍 Edge Cases Considered

- **$m = 1$ or $n = 1$**: Handled trivially in $\mathcal{O}(\log n)$ time.
- **$k = 1$**: Minimum element $1$ returned immediately.
- **$k = m \times n$**: Maximum element $m \times n$ returned.
- **Asymmetric Dimensions ($m \gg n$ or $n \gg m$)**: Swap optimization ensures minimal iterations.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
