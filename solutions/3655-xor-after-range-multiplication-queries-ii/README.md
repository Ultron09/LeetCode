# [3655. XOR After Range Multiplication Queries II](https://leetcode.com/problems/xor-after-range-multiplication-queries-ii/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

You are given an integer array `nums` of length $n$ and a 2D integer array `queries` of size $q$, where `queries[i] = [li, ri, ki, vi]`.

For each query, apply the following operations:
1. Set `idx = li`.
2. While `idx <= ri`:
   - `nums[idx] = (nums[idx] * vi) % (10^9 + 7)`
   - `idx += ki`

Return the **bitwise XOR of all elements** in `nums` after processing all queries.

### Example 1:
```
Input: nums = [1,1,1], queries = [[0,2,1,4]]
Output: 4
Explanation: Array becomes [4, 4, 4]. XOR = 4 ^ 4 ^ 4 = 4.
```

### Example 2:
```
Input: nums = [2,3,1,5,4], queries = [[1,4,2,3],[0,2,1,2]]
Output: 31
Explanation:
- Query 1: [2, 9, 1, 15, 4]
- Query 2: [4, 18, 2, 15, 4]
XOR = 4 ^ 18 ^ 2 ^ 15 ^ 4 = 31.
```

### Constraints:
- $1 \le n == \text{nums.length} \le 10^5$
- $1 \le \text{nums}[i] \le 10^9$
- $1 \le q == \text{queries.length} \le 10^5$
- `queries[i] = [li, ri, ki, vi]`
- $0 \le l_i \le r_i < n$
- $1 \le k_i \le n$
- $1 \le v_i \le 10^5$

---

## 💡 Intuition & Approach

### 1. Square Root Decomposition on Step Size $k$
Queries jump with stride $k$. We choose a threshold $B = \lfloor \sqrt{n} \rfloor$:
- **Large Step Size ($k \ge B$)**:
  - Each query visits at most $n / k \le \sqrt{n}$ elements.
  - We execute these queries directly via simple brute force in $\mathcal{O}(\sqrt{n})$ time per query.
- **Small Step Size ($k < B$)**:
  - There are only $\sqrt{n}$ distinct values of $k$.
  - For each fixed $k$, queries update arithmetic progressions of the form $l + c \cdot k \le r$.
  - We use a **Multiplicative Difference Array** over stride $k$:
    - For query $(l, r, k, v)$, let $last = l + \lfloor \frac{r - l}{k} \rfloor \cdot k$.
    - Multiply `diff[l]` by $v \pmod{MOD}$.
    - Multiply `diff[last + k]` by $v^{-1} \pmod{MOD}$ (using Fermat's Little Theorem $v^{MOD - 2} \pmod{MOD}$).
    - After collecting all queries for this $k$, run a stride-$k$ prefix product sweep over each residue class $rem \in [0, k-1]$ in $\mathcal{O}(n)$ time.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}((N + Q)\sqrt{N} + Q \log(\text{MOD}))$
  - Large $k$ queries: $\mathcal{O}(Q \sqrt{N})$.
  - Small $k$ queries: at most $\sqrt{N}$ values of $k$, each processed in $\mathcal{O}(N)$ time $\implies \mathcal{O}(N \sqrt{N})$.
  - Modular inverse: $\mathcal{O}(Q \log(\text{MOD}))$.
  - Total operations $\approx 10^5 \times 320 \approx 3.2 \times 10^7$ ($< 45$ ms in C++).
- **Space Complexity:** $\mathcal{O}(N + Q)$ auxiliary space for query grouping and difference arrays.

---

## 🔍 Edge Cases Considered

- **$k > n$**: Only index $l$ is updated if $l \le r$.
- **$v = 1$**: Identity multiplication handled seamlessly without modifying state.
- **Modular Inverses**: Since $MOD = 10^9 + 7$ is prime and $1 \le v \le 10^5$, $\gcd(v, MOD) = 1$, ensuring valid unique multiplicative inverses.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
