# [982. Triples with Bitwise AND Equal To Zero](https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/)

**Difficulty:** `Hard`  
**Topics:** [Array](../../topics/arrays-and-hashing.md), [Bit Manipulation](../../topics/bit-manipulation.md), Hash Table

---

## 📌 Problem Statement

Given an integer array `nums`, return the number of **AND triples**.

An AND triple is a triple of indices `(i, j, k)` such that:
- `0 <= i < nums.length`
- `0 <= j < nums.length`
- `0 <= k < nums.length`
- `nums[i] & nums[j] & nums[k] == 0`, where `&` represents the bitwise-AND operator.

### Example 1:
```
Input: nums = [2,1,3]
Output: 12
Explanation: We could choose the following i, j, k triples:
(i=0, j=0, k=1) : 2 & 2 & 1
(i=0, j=1, k=0) : 2 & 1 & 2
(i=0, j=1, k=1) : 2 & 1 & 1
(i=0, j=1, k=2) : 2 & 1 & 3
(i=0, j=2, k=1) : 2 & 3 & 1
(i=1, j=0, k=0) : 1 & 2 & 2
(i=1, j=0, k=1) : 1 & 2 & 1
(i=1, j=0, k=2) : 1 & 2 & 3
(i=1, j=1, k=0) : 1 & 1 & 2
(i=1, j=2, k=0) : 1 & 3 & 2
(i=2, j=0, k=1) : 3 & 2 & 1
(i=2, j=1, k=0) : 3 & 1 & 2
```

### Constraints:
- `1 <= nums.length <= 1000`
- `0 <= nums[i] < 2^16`

---

## 💡 Intuition & Approach

Finding every unique $(i, j, k)$ sequentially forces an $\mathcal{O}(N^3)$ complexity, computing heavily around $10^9$ operations which edges toward Time Limit Exceeded limits. However, recognizing the severe constraint that elements fall exclusively inside a 16-bit bounding block (`< 2^16`), opens a pathway for memory caching!

Instead of brute-forcing $3$ dimensions directly, we break it into smaller sub-dimensions:
1. **Dimension $1$ and $2$**: We can precalculate and map the frequency of every resulting combination of `nums[i] & nums[j]`. Due to the bounds, the results also strictly fall inside the `[0, 65535]` range. 
2. **Dimension $3$**: With the frequencies pre-mapped in $\mathcal{O}(N^2)$ time, we iterate through our 3rd index $k$. For each $k$, we fetch `nums[k]` and scan all values $v$ where $v \in [0, 65535]$. If `(nums[k] & v) == 0`, we rapidly bulk-add the recorded pair-frequency of $v$ towards our triple count.

This turns an $N \times N \times N$ problem into $N^2 + N \times 2^{16}$, avoiding timeouts completely.

### Micro-Optimization:
Instead of looping exactly 65536 checks for *every* $k$, we can pre-filter the array and strictly loop against only the subset of non-zero tracked values. This drops the $N \times 2^{16}$ ceiling drastically on sparse datasets.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2 + N \times 2^{16})$ worst-case. Bounding the possible pairwise computations restricts the third check effectively avoiding cubic scaling.
- **Space Complexity:** $\mathcal{O}(2^{16})$ for caching the pair count results, easily consuming roughly $256$ KB of continuous stack/heap memory block logic.

---

## 🔍 Edge Cases Considered

- Arrays entirely filled with zeroes `[0, 0, ... 0]`: Valid combinations evaluate correctly as strictly identical permutations scale precisely.
- Non-overlapping disjoints (e.g., mutually exclusive bits). Fast-tracked because non-zero frequencies instantly yield the appropriate multiplicative combination.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
