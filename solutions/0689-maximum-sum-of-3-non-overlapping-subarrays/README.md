# [689. Maximum Sum of 3 Non-Overlapping Subarrays](https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Array](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an integer array `nums` and an integer `k`, find three non-overlapping subarrays of length `k` with maximum sum and return them.

Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the **lexicographically smallest** one.

### Example 1:
```
Input: nums = [1,2,1,2,6,7,5,1], k = 2
Output: [0,3,5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to starting indices [0, 3, 5].
```

### Example 2:
```
Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
Output: [0,2,4]
```

### Constraints:
- $1 \le \text{nums.length} \le 2 \times 10^4$
- $1 \le \text{nums}[i] < 2^{16}$
- $1 \le k \le \lfloor \text{nums.length} / 3 \rfloor$

---

## 💡 Intuition & Approach

### 1. Middle-Anchor Decomposition
Rather than exploring all $\mathcal{O}(N^3)$ combinations of three non-overlapping subarrays, we **anchor the middle subarray**:
- Suppose the middle subarray begins at index $j$ ($k \le j \le N - 2k$).
- The left subarray must start at some index $l \in [0, j - k]$.
- The right subarray must start at some index $r \in [j + k, N - k]$.

By precomputing the best single subarray starting index for all valid left prefixes and right suffixes, each choice of middle index $j$ can be evaluated in $\mathcal{O}(1)$ time.

### 2. Prefix & Suffix Optimal Window Precomputation
Let $\text{windowSum}[i]$ be the sum of `nums[i ... i + k - 1]`.
1. **Left Optimal Array (`leftMax[i]`)**:
   - Best starting index in $[0, i]$ maximizing `windowSum`.
   - Forward sweep: update best index if $\text{windowSum}[i] > \text{windowSum}[\text{bestLeft}]$.
   - *Strict inequality (`>`) guarantees picking the smallest index on ties.*
2. **Right Optimal Array (`rightMax[i]`)**:
   - Best starting index in $[i, M - 1]$ maximizing `windowSum`.
   - Backward sweep: update best index if $\text{windowSum}[i] \ge \text{windowSum}[\text{bestRight}]$.
   - *Non-strict inequality (`>=`) guarantees picking the earlier (smaller) index on ties.*

### 3. Linear Middle-Window Sweep
Iterate $j$ from $k$ to $M - 1 - k$:
- Query $l = \text{leftMax}[j - k]$ and $r = \text{rightMax}[j + k]$.
- Calculate $\text{total} = \text{windowSum}[l] + \text{windowSum}[j] + \text{windowSum}[r]$.
- If $\text{total} > \text{maxSum}$, update answer triplet $(l, j, r)$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - Computing window sums: $\mathcal{O}(N)$.
  - Building `leftMax` and `rightMax`: $\mathcal{O}(N)$.
  - Middle window sweep: $\mathcal{O}(N)$.
  - Total time is strictly linear $\mathcal{O}(N)$.
- **Space Complexity:** $\mathcal{O}(N)$
  - Storage for $\text{windowSum}$, $\text{leftMax}$, and $\text{rightMax}$ arrays of size $N - k + 1$.

---

## 🔍 Edge Cases Considered

- **Minimum Length Array ($N = 3k$)**: Exactly one valid configuration $[0, k, 2k]$.
- **Identical Window Sums**: Strict/non-strict comparator design guarantees lexicographical tie-breaking.
- **Large Array ($N = 2 \times 10^4$)**: Linear $\mathcal{O}(N)$ completes in $< 5\text{ ms}$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
