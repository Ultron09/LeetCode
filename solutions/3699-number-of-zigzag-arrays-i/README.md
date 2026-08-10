# [3699. Number of ZigZag Arrays I](https://leetcode.com/problems/number-of-zigzag-arrays-i/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given three integers `n`, `l`, and `r`.

A **ZigZag array** of length `n` is defined as follows:
1. Each element lies in the range $[l, r]$.
2. No two adjacent elements are equal ($a_i \ne a_{i+1}$).
3. No three consecutive elements form a strictly increasing or strictly decreasing sequence.

Return the total number of valid ZigZag arrays, modulo $10^9 + 7$.

### Example 1:
```
Input: n = 3, l = 4, r = 5
Output: 2
Explanation:
There are only 2 valid ZigZag arrays of length n = 3 using values in [4, 5]:
- [4, 5, 4]
- [5, 4, 5]
```

### Example 2:
```
Input: n = 3, l = 1, r = 3
Output: 10
Explanation:
There are 10 valid ZigZag arrays of length n = 3 using values in [1, 3]:
[1, 2, 1], [1, 3, 1], [1, 3, 2]
[2, 1, 2], [2, 1, 3], [2, 3, 1], [2, 3, 2]
[3, 1, 2], [3, 1, 3], [3, 2, 3]
```

### Constraints:
- $3 \le n \le 2000$
- $1 \le l < r \le 2000$

---

## 💡 Intuition & Approach

### 1. Dynamic Programming State Definition
Let $m = r - l + 1$ be the number of distinct choices in $[l, r]$, mapped to $\{0, 1, \dots, m-1\}$.

To enforce the alternating ZigZag condition, we track the direction of the last transition:
- $\text{dp}_0[j]$: Number of valid sequences of current length ending with value $j$ where the last transition was **decreasing** (from some $k > j$).
- $\text{dp}_1[j]$: Number of valid sequences of current length ending with value $j$ where the last transition was **increasing** (from some $k < j$).

### 2. State Transitions
Since direction must strictly alternate:
- A decreasing transition to $j$ must follow an increasing transition ending at some $k > j$:
  $$\text{next\_dp}_0[j] = \sum_{k = j + 1}^{m - 1} \text{dp}_1[k]$$
- An increasing transition to $j$ must follow a decreasing transition ending at some $k < j$:
  $$\text{next\_dp}_1[j] = \sum_{k = 0}^{j - 1} \text{dp}_0[k]$$

### 3. Prefix Sum Optimization in $\mathcal{O}(1)$
Direct summation of $k$ would take $\mathcal{O}(m)$ per state ($\mathcal{O}(n \cdot m^2)$ overall).
By computing prefix sums $\text{sum}_0$ and $\text{sum}_1$ where $\text{sum}_d[j] = \sum_{k=0}^{j-1} \text{dp}_d[k]$:
- $\text{next\_dp}_0[j] = \text{sum}_1[m] - \text{sum}_1[j + 1]$
- $\text{next\_dp}_1[j] = \text{sum}_0[j]$

Each transition executes in $\mathcal{O}(1)$ time, reducing the runtime to $\mathcal{O}(n \cdot m)$ with $\mathcal{O}(m)$ space using rolling arrays.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot M)$
  - Outer loop runs $N - 2$ times.
  - Each iteration computes prefix sums and updates arrays in $\mathcal{O}(M)$ time.
  - Total operations: $\le 2000 \times 2000 = 4 \times 10^6$ ($< 5$ ms in C++).
- **Space Complexity:** $\mathcal{O}(M)$
  - Rolling 1D arrays of size $M + 1$.

---

## 🔍 Edge Cases Considered

- **$m = 2$**: Minimum valid alphabet size ($l < r$).
- **$n = 3$**: Minimum valid sequence length.
- **Modulo Handling**: Added `+ MOD` before modulo subtraction to avoid negative results.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
