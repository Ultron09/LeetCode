# [87. Scramble String](https://leetcode.com/problems/scramble-string/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Interval DP](../../topics/dynamic-programming.md), [Recursion with Memoization](../../topics/dynamic-programming.md), [String](../../topics/sliding-window.md)

---

## 📌 Problem Statement

We can scramble a string `s` to get a string `t` using the following algorithm:
1. If the length of the string is 1, stop.
2. If the length is $> 1$:
   - Split the string into two non-empty substrings at any index: $s = x + y$.
   - Randomly decide to swap the two substrings or keep them in the same order: $s = x + y$ or $s = y + x$.
   - Recursively apply the algorithm to each substring $x$ and $y$.

Given two strings `s1` and `s2` of the same length, return `true` if `s2` is a scrambled string of `s1`, otherwise return `false`.

### Example 1:
```
Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scrambling sequence:
"great" -> "gr/eat" -> "g/r / e/at" -> "r/g / e/at" -> "rgeat".
```

### Example 2:
```
Input: s1 = "abcde", s2 = "caebd"
Output: false
```

### Example 3:
```
Input: s1 = "a", s2 = "a"
Output: true
```

### Constraints:
- $\text{s1.length} == \text{s2.length}$
- $1 \le \text{s1.length} \le 30$
- `s1` and `s2` consist of lowercase English letters.

---

## 💡 Intuition & Approach

### 1. Interval DP / Substring Memoization
For substrings $s_1[i_1 \dots i_1 + len - 1]$ and $s_2[i_2 \dots i_2 + len - 1]$:
- **Base Case**: If substrings are equal, return `true`.
- **Pruning**: If character frequency counts do not match across the 26 lowercase English letters, they can never be scrambled versions of each other $\implies$ return `false` immediately.
- **Branching for Split $k \in [1, len - 1]$**:
  1. **Unswapped Branch**:
     $$\text{solve}(i_1, i_2, k) \land \text{solve}(i_1 + k, i_2 + k, len - k)$$
  2. **Swapped Branch**:
     $$\text{solve}(i_1, i_2 + len - k, k) \land \text{solve}(i_1 + k, i_2, len - k)$$

### 2. State Cache
Since $N \le 30$, a compact 3D array `memo[31][31][31]` initialized with $-1$ avoids all hashing overhead and provides $\mathcal{O}(1)$ lookup times.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^4)$ where $N \le 30$ ($N^3$ states, each testing up to $N$ split points).
- **Space Complexity:** $\mathcal{O}(N^3)$ for the memoization table.

---

## 🔍 Edge Cases Considered

- **Identical strings**: Matched immediately at base case.
- **Anagram mismatches**: Pruned in $\mathcal{O}(len)$ before checking recursive splits.
- **Single character strings**: Handled without recursion.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
