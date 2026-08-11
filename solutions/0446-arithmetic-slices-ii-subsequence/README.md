# [446. Arithmetic Slices II - Subsequence](https://leetcode.com/problems/arithmetic-slices-ii-subsequence/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an integer array `nums`, return the number of all the **arithmetic subsequences** of `nums`.

A sequence of numbers is called arithmetic if it consists of **at least three elements** and if the difference between any two consecutive elements is the same.

- For example, `[1, 3, 5, 7, 9]`, `[7, 7, 7, 7]`, and `[3, -1, -5, -9]` are arithmetic sequences.
- For example, `[1, 1, 2, 5, 7]` is not an arithmetic sequence.

A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.

The test cases are generated so that the answer fits in a 32-bit signed integer.

### Example 1:
```
Input: nums = [2,4,6,8,10]
Output: 7
Explanation: All arithmetic subsequence slices are:
[2,4,6], [4,6,8], [6,8,10], [2,4,6,8], [4,6,8,10], [2,4,6,8,10], [2,6,10]
```

### Example 2:
```
Input: nums = [7,7,7,7,7]
Output: 16
Explanation: Any subsequence of length >= 3 of this array is arithmetic.
```

### Constraints:
- $1 \le \text{nums.length} \le 1000$
- $-2^{31} \le \text{nums}[i] \le 2^{31} - 1$

---

## 💡 Intuition & Approach

### 1. State Representation
An arithmetic sequence of length $\ge 3$ requires at least 2 prior elements. Tracking all valid subsequences directly is complex because extending a 2-element sequence produces a 3-element arithmetic slice.

We define:
- `dp[i][d]`: The number of arithmetic subsequences of **length $\ge 2$** ending at index `i` with common difference `d`.

### 2. Transition Relation
For every pair $(j, i)$ with $0 \le j < i < n$:
1. Compute difference $d = \text{nums}[i] - \text{nums}[j]$ (stored as `long long` to prevent 32-bit signed overflow).
2. Retrieve `countAtJ = dp[j][d]` (the number of subsequences of length $\ge 2$ ending at $j$ with difference $d$).
3. **Extend to Length $\ge 3$**:
   - Appending $\text{nums}[i]$ to any of the `countAtJ` subsequences creates a valid arithmetic subsequence of length $\ge 3$.
   - Thus, we add `countAtJ` to our global answer:
     $$\text{totalCount} \gets \text{totalCount} + \text{countAtJ}$$
4. **Update `dp[i][d]`**:
   - The subsequences of length $\ge 2$ ending at $i$ with difference $d$ include all `countAtJ` extended sequences **plus** the new 2-element sequence $(\text{nums}[j], \text{nums}[i])$:
     $$\text{dp}[i][d] \gets \text{dp}[i][d] + \text{countAtJ} + 1$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$
  - There are $\frac{N(N - 1)}{2}$ index pairs $(j, i)$.
  - For each pair, hash map lookup and insertion take $\mathcal{O}(1)$ average time.
  - Overall time complexity is $\mathcal{O}(N^2)$. For $N = 1000$, $\approx 5 \times 10^5$ operations (well within the $1\text{s}$ limit).
- **Space Complexity:** $\mathcal{O}(N^2)$
  - Storing at most $\frac{N(N - 1)}{2}$ unique difference entries across the $N$ hash maps in `dp`.

---

## 🔍 Edge Cases Considered

- **$N < 3$**: Returns 0 immediately since no arithmetic subsequence of length $\ge 3$ can exist.
- **Identical Numbers**: Handled correctly; $d = 0$ accumulates all combinations of equal elements.
- **Large Difference Overflow**: Computing $\text{nums}[i] - \text{nums}[j]$ where values are near $\pm 2^{31}$ requires `long long` cast before subtraction to avoid integer underflow/overflow.
- **Non-Adjacent Elements**: The subsequence formulation naturally accounts for non-contiguous elements skipping arbitrary indices.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
