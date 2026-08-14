# [960. Delete Columns to Make Sorted III](https://leetcode.com/problems/delete-columns-to-make-sorted-iii/)

**Difficulty:** `Hard`  
**Topics:** [Array](../../topics/arrays-and-hashing.md), [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

You are given an array of $n$ strings `strs`, all of the same length.

We may choose any deletion indices, and we delete all the characters in those indices for each string.

Suppose we chose a set of deletion indices `answer` such that after deletions, the final array has every string (row) in lexicographic order. (i.e., `strs[0][0] <= strs[0][1] <= ... <= strs[0][strs[0].length - 1]`, and so on). Return the minimum possible value of `answer.length`.

### Example 1:
```
Input: strs = ["babca","bbazb"]
Output: 3
Explanation: After deleting columns 0, 1, and 4, the final array is strs = ["bc", "az"].
Both these rows are individually in lexicographic order.
```

### Example 2:
```
Input: strs = ["edcba"]
Output: 4
Explanation: If we delete less than 4 columns, the only row will not be lexicographically sorted.
```

### Constraints:
- `n == strs.length`
- `1 <= n <= 100`
- `1 <= strs[i].length <= 100`
- `strs[i]` consists of lowercase English letters.

---

## 💡 Intuition & Approach

Instead of trying to find the minimum number of columns to *delete*, we can reframe the problem to find the **maximum number of columns to KEEP**. This changes the problem into finding the **Longest Increasing Subsequence (LIS)** of columns.

1. **Condition to Keep**:
   For a column `j` to appear immediately before column `i` in our final configuration, it must be true that for **every single string** `s` in `strs`, `s[j] <= s[i]`. If even one string violates this, we cannot place column `j` before column `i`.

2. **DP State**:
   Let `dp[i]` be the maximum number of columns we can keep such that the chosen sequence of columns ends precisely at index `i`.

3. **Base Case & Transitions**:
   - Initialize `dp[i] = 1` for all `0 <= i < m`, since a single column by itself is always sorted.
   - For every column `i` from `1` to `m-1`, check all previous columns `j` from `0` to `i-1`.
   - If `strs[k][j] <= strs[k][i]` holds for all `0 <= k < n`, we can transition:
     `dp[i] = max(dp[i], dp[j] + 1)`

4. **Result**:
   The maximum number of columns we can keep is `max(dp)`. The minimum number of columns to delete is simply `m - max(dp)` where `m` is the total number of columns.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M^2 \times N)$ where $M$ is the length of each string and $N$ is the number of strings. The DP requires two nested loops over $M$, and an inner loop over $N$ to validate characters. With $M \le 100$ and $N \le 100$, this takes at most $100^2 \times 100 = 1,000,000$ operations, which is incredibly fast.
- **Space Complexity:** $\mathcal{O}(M)$ to store the DP array.

---

## 🔍 Edge Cases Considered

- Strings are already sorted: Returns 0.
- All characters in strings are strictly descending: Returns $M - 1$ since we can keep at most 1 column.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
