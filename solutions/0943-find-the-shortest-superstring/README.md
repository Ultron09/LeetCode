# [943. Find the Shortest Superstring](https://leetcode.com/problems/find-the-shortest-superstring/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Bit Manipulation](../../topics/bit-manipulation.md), String, Bitmask DP

---

## 📌 Problem Statement

Given an array of strings `words`, return the smallest string that contains each string in `words` as a substring. If there are multiple valid strings of the smallest length, return any of them.

You may assume that no string in `words` is a substring of another string in `words`.

### Example 1:
```
Input: words = ["alex","loves","leetcode"]
Output: "alexlovesleetcode"
Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
```

### Example 2:
```
Input: words = ["catg","ctaagt","gcta","ttca","atgcatc"]
Output: "gctaagttcatgcatc"
```

### Constraints:
- `1 <= words.length <= 12`
- `1 <= words[i].length <= 20`
- `words[i]` consists of lowercase English letters.
- All the strings of `words` are unique

---

## 💡 Intuition & Approach

The constraint on `words.length <= 12` suggests a factorial time complexity like permutations $\mathcal{O}(N!)$ or an exponential time complexity like Bitmask Dynamic Programming $\mathcal{O}(N^2 \cdot 2^N)$. This problem is essentially a variation of the well-known **Travelling Salesperson Problem (TSP)**.

1. **Graph Representation (Overlap Calculation)**:
   Instead of minimizing the total length of the superstring directly, we can equivalently **maximize the total overlap** between adjacent words in our permutation.
   Let `overlap[i][j]` be the maximum length of a suffix of `words[i]` that exactly matches a prefix of `words[j]`. We can precompute this in $\mathcal{O}(N^2 \times L)$.

2. **Bitmask DP**:
   - **State**: Let `dp[mask][i]` be the maximum overlap achieved by using a subset of words represented by the bitmask `mask`, and ending the sequence with the word at index `i`.
   - **Transition**: `dp[mask][i] = max(dp[mask][i], dp[prev_mask][j] + overlap[j][i])` where `prev_mask = mask ^ (1 << i)` and `j` is any set bit in `prev_mask`.
   - **Path Tracking**: To reconstruct the optimal sequence of words, we also maintain a `parent[mask][i]` array that records which word `j` preceded word `i` to achieve the maximal overlap.

3. **Reconstruction**:
   - Find the best ending word for the full mask `(1 << N) - 1`.
   - Trace back through the `parent` array to find the optimal order (permutation) of the words.
   - Construct the final string by appending each subsequent word, omitting the overlapping prefix.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2 \cdot 2^N + N^2 \cdot L)$
  - Overlap precomputation takes $\mathcal{O}(N^2 \cdot L)$ where $L$ is the max string length (20).
  - The bitmask DP takes $\mathcal{O}(N^2 \cdot 2^N)$ since there are $2^N$ states, $N$ ending positions, and $N$ previous positions to transition from.
- **Space Complexity:** $\mathcal{O}(N \cdot 2^N)$ — We need to store the `dp` and `parent` arrays, each of size $2^N \times N$.

---

## 🔍 Edge Cases Considered

- Strings with absolutely zero overlap (concatenated purely side by side). Handled correctly as `overlap[i][j]` will simply be `0`.
- Early combinations performing identically to late ones; any valid shortest superstring works, so breaking ties arbitrarily is perfectly acceptable.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
