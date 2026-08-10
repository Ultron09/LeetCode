# [3700. Number of ZigZag Arrays II](https://leetcode.com/problems/number-of-zigzag-arrays-ii/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Math & Geometry](../../topics/math-and-geometry.md)

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
- $3 \le n \le 10^9$
- $1 \le l < r \le 75$

---

## 💡 Intuition & Approach

### 1. State Representation
Let $M = r - l + 1$ be the number of available integer values, mapped to $\{0, 1, \dots, M-1\}$.

The condition "no three consecutive elements form a monotonic sequence" requires that the direction of movement must strictly alternate at each step:
- If step $i-1 \to i$ was **increasing (Up)**, then step $i \to i+1$ must be **decreasing (Down)**.
- If step $i-1 \to i$ was **decreasing (Down)**, then step $i \to i+1$ must be **increasing (Up)**.

Thus, we can encode the state at length $i$ with $2M$ states:
- $\text{Up}(v)$: reached value $v$ via an increasing step ($0 \le v < M$).
- $\text{Down}(v)$: reached value $v$ via a decreasing step ($M \le M + v < 2M$).

### 2. Transition Rules & Matrix Formulation
- From $\text{Up}(v)$, the next value $w$ must be strictly smaller ($w < v$), transitioning to state $\text{Down}(w)$:
  $$T[M + w][v] = 1 \quad \forall \; 0 \le w < v < M$$
- From $\text{Down}(v)$, the next value $w$ must be strictly larger ($w > v$), transitioning to state $\text{Up}(w)$:
  $$T[w][M + v] = 1 \quad \forall \; 0 \le v < w < M$$

### 3. Base Vector at $n = 2$
For length 2, any pair $(u, v)$ with $u \ne v$:
- If $u < v \implies$ state is $\text{Up}(v)$, number of valid $u < v$ is $v$.
- If $u > v \implies$ state is $\text{Down}(v)$, number of valid $u > v$ is $M - 1 - v$.

Base state vector $V_2$ of size $2M$:
$$V_2[v] = v, \quad V_2[M + v] = M - 1 - v$$

### 4. Matrix Exponentiation for Large $n$
Since $n \le 10^9$, we compute:
$$V_n = T^{n - 2} \times V_2 \pmod{10^9 + 7}$$
using binary matrix exponentiation in $\mathcal{O}((2M)^3 \log n)$ time.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}((2M)^3 \log n)$
  - With $M \le 75$, the matrix dimension is $S = 2M \le 150$.
  - Matrix multiplication costs $S^3 = 150^3 \approx 3.375 \times 10^6$ operations.
  - Exponentiation requires $\approx 30$ multiplications $\implies \approx 10^8$ operations total ($< 40$ ms in C++).
- **Space Complexity:** $\mathcal{O}((2M)^2)$ for the transition and result matrices.

---

## 🔍 Edge Cases Considered

- **$M = 2$ (Binary choices)**: Handled correctly with size $4 \times 4$ matrices.
- **Large $n = 10^9$**: Handled efficiently with logarithmic fast-power multiplication.
- **Cache Locality**: Loops ordered $(i, k, j)$ with early-exit zero skipping for optimal CPU pipeline throughput.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
