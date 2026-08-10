# [3336. Find the Number of Subsequences With Equal GCD](https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Math & Geometry](../../topics/math-and-geometry.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an integer array `nums`.

Your task is to find the number of pairs of non-empty subsequences `(seq1, seq2)` of `nums` that satisfy the following conditions:
1. The subsequences `seq1` and `seq2` are **disjoint**, meaning no index of `nums` is common between them.
2. The GCD of the elements of `seq1` is equal to the GCD of the elements of `seq2`.

Return the total number of such pairs modulo $10^9 + 7$.

### Example 1:
```
Input: nums = [1,2,3,4]
Output: 10
Explanation:
The subsequence pairs which have the GCD of their elements equal to 1 are:
- ([1], [1]), ([1, 2], [1, 2]), etc.
Total valid disjoint pairs = 10.
```

### Example 2:
```
Input: nums = [10,20,30]
Output: 2
Explanation:
The subsequence pairs with GCD equal to 10 are:
- ([10, 20], [30]), ([20], [10, 30])
```

### Example 3:
```
Input: nums = [1,1,1,1]
Output: 50
```

### Constraints:
- $1 \le \text{nums.length} \le 200$
- $1 \le \text{nums}[i] \le 200$

---

## 💡 Intuition & Approach

### 1. State Definition
Given the constraints ($N \le 200$, $\text{nums}[i] \le 200$), the maximum possible GCD value is $M = \max(\text{nums}) \le 200$.

For each element in `nums`, we make a 3-way decision for disjoint subsequences:
1. **Add to `seq1`**: Updates $\text{GCD}_1 \leftarrow \gcd(\text{GCD}_1, \text{num})$.
2. **Add to `seq2`**: Updates $\text{GCD}_2 \leftarrow \gcd(\text{GCD}_2, \text{num})$.
3. **Skip `num`**: Both $\text{GCD}_1$ and $\text{GCD}_2$ remain unchanged.

Let $\text{dp}[g_1][g_2]$ be the number of disjoint subsequence pairs such that:
- $\text{GCD}(\text{seq}_1) = g_1$ (where $g_1 = 0$ represents that $\text{seq}_1$ is currently empty).
- $\text{GCD}(\text{seq}_2) = g_2$ (where $g_2 = 0$ represents that $\text{seq}_2$ is currently empty).

### 2. State Transitions
Initialize $\text{dp}[0][0] = 1$.

For each number $x \in \text{nums}$, iterate over all $(g_1, g_2)$ with $\text{dp}[g_1][g_2] > 0$:
- **Skip $x$**: $\text{next\_dp}[g_1][g_2] += \text{dp}[g_1][g_2]$
- **Add $x$ to $\text{seq}_1$**: $\text{next\_dp}[\gcd(g_1, x)][g_2] += \text{dp}[g_1][g_2]$ (with $\gcd(0, x) = x$)
- **Add $x$ to $\text{seq}_2$**: $\text{next\_dp}[g_1][\gcd(g_2, x)] += \text{dp}[g_1][g_2]$ (with $\gcd(0, x) = x$)

### 3. Final Answer
Sum all pairs where both subsequences are non-empty and have identical GCDs:
$$\text{Total} = \sum_{g=1}^M \text{dp}[g][g] \pmod{10^9 + 7}$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \times M^2)$
  - $N \le 200$, $M \le 200$.
  - State space per element is $(M + 1)^2 \approx 4 \times 10^4$.
  - Precomputing `gcdTable[201][201]` ensures $\mathcal{O}(1)$ transitions.
  - Total operations: $200 \times 40,000 \approx 8 \times 10^6$ operations ($< 10$ ms in C++).
- **Space Complexity:** $\mathcal{O}(M^2)$
  - Two 2D tables of size $(M+1) \times (M+1)$ ($\approx 320$ KB, highly cache-friendly).

---

## 🔍 Edge Cases Considered

- **$N = 1$**: No two disjoint non-empty subsequences can be formed, returns $0$.
- **All elements identical (e.g. `[1, 1, 1, 1]`)**: Correctly enumerates disjoint partitions with matching GCD $1$.
- **Modulo Arithmetic**: Correctly applies modulo $10^9 + 7$ on all cumulative transitions.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
