# [3753. Total Waviness of Numbers in Range II](https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

You are given two integers `num1` and `num2` representing an inclusive range $[num1, num2]$.

The **waviness** of a positive integer is the number of **peaks** and **valleys** formed by its digits:
- A digit $d_i$ ($1 < i < k$) is a **peak** if $d_{i-1} < d_i > d_{i+1}$.
- A digit $d_i$ ($1 < i < k$) is a **valley** if $d_{i-1} > d_i < d_{i+1}$.
- The first and last digits can never be peaks or valleys. Numbers with fewer than 3 digits have a waviness of 0.

Return the **total waviness** of all integers in the range $[num1, num2]$.

### Example 1:
```
Input: num1 = 1, num2 = 100
Output: 0
Explanation:
All numbers <= 100 have fewer than 3 digits with valid peaks/valleys, total waviness is 0.
```

### Example 2:
```
Input: num1 = 120, num2 = 122
Output: 2
Explanation:
- 120: '2' is a peak (1 < 2 > 0) -> waviness = 1
- 121: '2' is a peak (1 < 2 > 1) -> waviness = 1
- 122: '2' is not a peak (1 < 2 == 2) -> waviness = 0
Total = 1 + 1 + 0 = 2.
```

### Constraints:
- $1 \le num_1 \le num_2 \le 10^{15}$

---

## 💡 Intuition & Approach

### 1. Range Prefix Decomposition
We compute the answer using the standard prefix difference trick:
$$\text{ans} = \text{solve}(num_2) - \text{solve}(num_1 - 1)$$

### 2. Digit DP with Count & Sum Propagation
During top-down memoized DFS, we process digits from left to right, maintaining:
- `pos`: current digit index ($0 \dots n - 1$).
- `prev`: the digit at position $pos - 2$ (or $-1$ if not placed).
- `curr`: the digit at position $pos - 1$ (or $-1$ if in leading zero stage).
- `isLimit`: whether current choices are bounded by the input prefix.
- `isLeading`: whether we are still in the leading zero stage.

Each DFS state returns a pair $(count, sum)$:
- `count`: number of valid integers formed by the suffix.
- `sum`: total waviness contributed by the suffix.

### 3. Contribution Counting Insight
When evaluating transition from $(prev, curr)$ to placing $digit$:
- If $curr$ forms a peak ($prev < curr > digit$) or a valley ($prev > curr < digit$), **every valid number in the subtree rooted at this step receives $+1$ waviness**.
- Thus, instead of storing individual numbers, we directly add `subCount` to the accumulated `totalSum`:
  $$\text{totalSum} \leftarrow \text{totalSum} + \text{subCount}$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(D^3 \log_{10}(num_2))$ where base $D = 10$
  - Number of states: $\le 16 \times 10 \times 10 = 1600$.
  - Transitions per state: $10$.
  - Total operations $\le 16000$ per `solve` call ($< 1$ ms in C++).
- **Space Complexity:** $\mathcal{O}(D^2 \log_{10}(num_2))$
  - Memoization tables `memo_cnt` and `memo_sum` of size $20 \times 11 \times 11$.

---

## 🔍 Edge Cases Considered

- **$num < 100$**: Numbers with $< 3$ digits cannot have peaks/valleys $\implies$ return 0 immediately.
- **$num_1 = 1$**: Handled properly via $\text{solve}(0) = 0$.
- **Leading Zeros**: Handled by resetting `prev` and `curr` to $-1$ until the first non-zero digit is placed.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
