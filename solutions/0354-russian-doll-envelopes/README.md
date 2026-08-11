# [354. Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Binary Search](../../topics/binary-search.md)

---

## 📌 Problem Statement

You are given a 2D array of integers `envelopes` where `envelopes[i] = [wi, hi]` represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope are **greater than** the other envelope's width and height.

Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).

**Note:** You cannot rotate an envelope.

### Example 1:
```
Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
```

### Example 2:
```
Input: envelopes = [[1,1],[1,1],[1,1]]
Output: 1
```

### Constraints:
- $1 \le \text{envelopes.length} \le 10^5$
- $\text{envelopes}[i].\text{length} == 2$
- $1 \le w_i, h_i \le 10^5$

---

## 💡 Intuition & Approach

### 1. Reduction to 1D Longest Increasing Subsequence (LIS)

The 2D nesting constraint (**both** width and height must be strictly greater) makes direct comparison complex. The key insight is a dimension-reduction trick:

1. **Sort by width ascending**: This guarantees that any subsequence in sorted order has non-decreasing widths.
2. **For ties in width, sort by height descending**: This is the critical trick. If two envelopes share the same width, sorting their heights in descending order ensures that the LIS on heights can never select both — since heights are decreasing for the same width, `lower_bound` will replace rather than extend.
3. **Find the LIS on the heights array**: After the custom sort, the answer is exactly the length of the Longest Increasing Subsequence of the heights.

### 2. Why Descending Height for Equal Widths?

Consider envelopes `[3,3]` and `[3,5]`. With ascending height sort, both heights `3, 5` form an increasing subsequence, but width `3 == 3` means they can't nest. Sorting heights descending (`5, 3`) prevents `lower_bound` from extending the tails array with both.

### 3. Patience Sort (Binary Search LIS)

The classic $\mathcal{O}(N \log N)$ LIS algorithm:
- Maintain a `tails` array where `tails[i]` is the smallest tail element of any increasing subsequence of length $i + 1$.
- For each height $h$: use `lower_bound` to find the first position $\ge h$ in `tails`.
  - If found: replace that position with $h$ (smaller tail = more room for future elements).
  - If not found: append $h$ (extends the longest subsequence by 1).
- The answer is `tails.size()`.

### Worked Example
```
Input: [[5,4], [6,4], [6,7], [2,3]]

After sort (width asc, height desc for ties):
  [2,3], [5,4], [6,7], [6,4]

Heights: [3, 4, 7, 4]

LIS via patience sort:
  h=3 → tails=[3]
  h=4 → tails=[3,4]
  h=7 → tails=[3,4,7]
  h=4 → lower_bound finds 4 at idx 1 → tails=[3,4,7] (replace 4 with 4, no change)

Answer: 3
```

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$
  - $\mathcal{O}(N \log N)$ for sorting the envelopes.
  - $\mathcal{O}(N \log N)$ for the patience-sort LIS (each of $N$ elements does one `lower_bound` in $\mathcal{O}(\log N)$).
- **Space Complexity:** $\mathcal{O}(N)$
  - The `tails` array can grow up to $N$ elements.

---

## 🔍 Edge Cases Considered

- **All identical envelopes**: Heights are all the same after sort, so LIS = 1. ✓
- **Same width, different heights**: Descending height sort prevents false nesting. ✓
- **Single envelope**: Returns 1 immediately. ✓
- **Fully nested chain**: Every envelope strictly dominates the next → LIS = $N$. ✓

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
