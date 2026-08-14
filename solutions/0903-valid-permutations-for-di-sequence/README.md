# [903. Valid Permutations for DI Sequence](https://leetcode.com/problems/valid-permutations-for-di-sequence/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

You are given a string `s` of length `n` where `s[i]` is either:
- `'D'` means decreasing, or
- `'I'` means increasing.

A permutation `perm` of `n + 1` integers of all the integers in the range `[0, n]` is called a valid permutation if for all valid `i`:
- If `s[i] == 'D'`, then `perm[i] > perm[i + 1]`, and
- If `s[i] == 'I'`, then `perm[i] < perm[i + 1]`.

Return the number of valid permutations `perm`. Since the answer may be large, return it modulo `10^9 + 7`.

### Example 1:
```
Input: s = "DID"
Output: 5
Explanation: The 5 valid permutations of (0, 1, 2, 3) are:
(1, 0, 3, 2)
(2, 0, 3, 1)
(2, 1, 3, 0)
(3, 0, 2, 1)
(3, 1, 2, 0)
```

### Example 2:
```
Input: s = "D"
Output: 1
```

### Constraints:
- `n == s.length`
- `1 <= n <= 200`
- `s[i]` is either `'I'` or `'D'`.

---

## 💡 Intuition & Approach

This problem asks for the number of permutations satisfying certain relative order constraints. A powerful technique for such problems is tracking the "relative rank" of the newly added number.

We can define a dynamic programming state `dp[i][j]` which represents the number of valid permutations of the first `i + 1` elements (using the numbers $0$ to $i$) such that the last element added is the $j$-th smallest element among them (i.e., its relative rank is $j$, where $0 \le j \le i$).

When we extend the permutation to length `i + 2` (adding a new element $k$ where $0 \le k \le i + 1$):
- Imagine all existing elements in the permutation that are $\ge k$ get incremented by 1. This perfectly preserves their relative order and leaves exactly the value $k$ available for the new element.
- If $s[i] == \text{'I'}$, the new element $k$ must be greater than the previous element $j$. Because $j$ doesn't get incremented (since $k > j$), the new element $k$ can be anything from $j + 1$ to $i + 1$. 
  Thus, $dp[i+1][k] = \sum_{j=0}^{k-1} dp[i][j]$.
- If $s[i] == \text{'D'}$, the new element $k$ must be less than the previous element $j$. Because $j$ gets incremented (since $k \le j$), the new element $k$ can be anything from $0$ to $j$.
  Thus, $dp[i+1][k] = \sum_{j=k}^{i} dp[i][j]$.

To optimize the transition from $\mathcal{O}(N)$ to $\mathcal{O}(1)$ (making the overall algorithm $\mathcal{O}(N^2)$), we can maintain a running sum as we iterate to populate the next DP state.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$ — We iterate through the string of length $N$, and for each state we update $N$ values using a running prefix/suffix sum, making each inner step $\mathcal{O}(1)$.
- **Space Complexity:** $\mathcal{O}(N)$ — We only need the DP row from the previous iteration, allowing us to drop the first dimension and use a pair of 1D arrays of size up to $N + 1$.

---

## 🔍 Edge Cases Considered

- `s` consists of all `'I'`s or all `'D'`s (results in exactly 1 valid permutation).
- Very short string `n = 1`.
- Fast modulo arithmetic to prevent integer overflow during the prefix sum accumulations.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
