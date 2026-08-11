# [629. K Inverse Pairs Array](https://leetcode.com/problems/k-inverse-pairs-array/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Prefix Sum](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

For an integer array `nums`, an **inverse pair** is a pair of integers `[i, j]` where $0 \le i < j < \text{nums.length}$ and $\text{nums}[i] > \text{nums}[j]$.

Given two integers `n` and `k`, return the number of different arrays consisting of numbers from $1$ to $n$ such that there are **exactly `k` inverse pairs**. Since the answer can be huge, return it **modulo $10^9 + 7$**.

### Example 1:
```
Input: n = 3, k = 0
Output: 1
Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pairs.
```

### Example 2:
```
Input: n = 3, k = 1
Output: 2
Explanation: The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
```

### Constraints:
- $1 \le n \le 1000$
- $0 \le k \le 1000$

---

## 💡 Intuition & Approach

### 1. Combinatorial Insertion Principle
Consider inserting the largest number $i$ into an existing permutation of $[1 \dots i - 1]$:
- If placed at position $i - 1$ (the end), it adds $0$ inversions because it is larger than all elements preceding it.
- If placed at position $i - 2$, it jumps over $1$ smaller element, adding $1$ inversion.
- $\dots$
- If placed at position $0$ (the front), it jumps over all $i - 1$ smaller elements, adding $i - 1$ inversions.

Thus, inserting element $i$ into a permutation of length $i - 1$ can add any number of inversions $p \in [0, i - 1]$.

### 2. Base DP Recurrence
Let $\text{dp}[i][j]$ be the number of permutations of length $i$ with exactly $j$ inverse pairs:
$$\text{dp}[i][j] = \sum_{p=0}^{\min(j, i - 1)} \text{dp}[i - 1][j - p] = \sum_{m=\max(0, j - (i - 1))}^{j} \text{dp}[i - 1][m]$$

Naive summation takes $\mathcal{O}(N \cdot K^2)$ or $\mathcal{O}(N^2 K)$, which is too slow for $N, K \le 1000$.

### 3. Prefix-Sum / Sliding Window Optimization
Notice the algebraic relationship between adjacent states:
$$\text{dp}[i][j] = \text{dp}[i - 1][j] + \text{dp}[i - 1][j - 1] + \dots + \text{dp}[i - 1][j - (i - 1)]$$
$$\text{dp}[i][j - 1] = \text{dp}[i - 1][j - 1] + \dots + \text{dp}[i - 1][j - i]$$
Subtracting $\text{dp}[i][j - 1]$ from $\text{dp}[i][j]$ yields the $\mathcal{O}(1)$ transition:
$$\text{dp}[i][j] = \text{dp}[i][j - 1] + \text{dp}[i - 1][j] - \text{dp}[i - 1][j - i] \quad (\text{for } j \ge i)$$

### 4. Space Optimization
Since computing row $i$ only depends on row $i - 1$ and the current prefix of row $i$, we compress the table to a 1D rolling array of size $K + 1$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot K)$
  - With the sliding window prefix optimization, each cell $\text{dp}[i][j]$ is computed in $\mathcal{O}(1)$ time.
  - Total operations for $N, K \le 1000$: $1000 \times 1000 = 10^6$ operations ($< 5\text{ ms}$).
- **Space Complexity:** $\mathcal{O}(K)$
  - Rolling 1D DP vector of size $K + 1$.

---

## 🔍 Edge Cases Considered

- **$K = 0$**: Always returns $1$ (the uniquely sorted permutation $[1, 2, \dots, n]$).
- **$K > \frac{n(n-1)}{2}$**: Maximum inversions possible for length $n$ is $\binom{n}{2}$; any larger $k$ naturally evaluates to $0$.
- **Modulo Subtraction**: Negative intermediate values protected via `(val % MOD + MOD) % MOD`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
