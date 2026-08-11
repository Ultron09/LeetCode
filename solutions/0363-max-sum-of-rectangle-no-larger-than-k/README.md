# [363. Max Sum of Rectangle No Larger Than K](https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Dynamic Programming](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an $m \times n$ matrix and an integer $k$, return the max sum of a rectangle in the matrix such that its sum is no larger than $k$.

It is guaranteed that there will be a rectangle with a sum no larger than $k$.

### Example 1:
```
Input: matrix = [[1,0,1],[0,-2,3]], k = 2
Output: 2
Explanation: The sum of rectangle [[0,1],[-2,3]] is 2, and 2 is the max number no larger than k.
```

### Example 2:
```
Input: matrix = [[2,2,-1]], k = 3
Output: 3
```

### Constraints:
- $m == \text{matrix.length}$
- $n == \text{matrix}[i].\text{length}$
- $1 \le m, n \le 100$
- $-100 \le \text{matrix}[i][j] \le 100$
- $-10^5 \le k \le 10^5$

### Follow-up:
*What if the number of rows is much larger than the number of columns?*

---

## 💡 Intuition & Approach

### 1. Column Compression — Reducing 2D to 1D
Fix a pair of columns $(l, r)$. Compress rows by maintaining a 1D array `rowSum[i]` = sum of `matrix[i][l..r]`. Now the problem reduces to: **find the max subarray sum ≤ k in a 1D array**.

### 2. Ordered Set for Constrained Max Subarray Sum
For the 1D problem with constraint $\le k$:
1. Compute prefix sums: $\text{currSum} = \sum_{j=0}^{i} \text{rowSum}[j]$.
2. We want: $\max(\text{currSum} - \text{prevSum})$ such that $\text{currSum} - \text{prevSum} \le k$.
3. Rearranging: $\text{prevSum} \ge \text{currSum} - k$.
4. Use `std::set::lower_bound(currSum - k)` to find the smallest qualifying prefix sum in $\mathcal{O}(\log m)$.

### 3. Answering the Follow-up
If rows $\gg$ columns, iterate over column pairs in $\mathcal{O}(n^2)$ and sweep rows in $\mathcal{O}(m \log m)$, giving $\mathcal{O}(n^2 \cdot m \log m)$. If columns $\gg$ rows, transpose the matrix and iterate over the original rows as columns. The solution automatically transposes when $m < n$ to always iterate over $\min(m, n)^2$ pairs.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\min(m,n)^2 \cdot \max(m,n) \cdot \log(\max(m,n)))$
  - $\mathcal{O}(\min(m,n)^2)$ column (or row) pairs.
  - For each pair: $\mathcal{O}(\max(m,n))$ to accumulate row sums + $\mathcal{O}(\max(m,n) \log(\max(m,n)))$ for prefix sum BST lookups.
- **Space Complexity:** $\mathcal{O}(\max(m,n))$
  - `rowSum` array + `std::set` for prefix sums.

---

## 🔍 Edge Cases Considered

- **Single Element Matrix**: Returns `matrix[0][0]` if it is $\le k$.
- **All Negative Matrix**: The BST correctly finds the largest (least negative) subarray sum $\le k$.
- **Exact Match ($\text{result} == k$)**: Early exit optimization — no better solution exists.
- **Follow-up Optimization**: Auto-transposition ensures the smaller dimension is always in the $\mathcal{O}(d^2)$ outer loop.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
