# [891. Sum of Subsequence Widths](https://leetcode.com/problems/sum-of-subsequence-widths/)

**Difficulty:** `Hard`  
**Topics:** [Array](../../topics/arrays-and-hashing.md), [Math](../../topics/math-and-geometry.md), [Sorting](../../topics/math-and-geometry.md) (Sorting often grouped under standard algorithms)

---

## 📌 Problem Statement

The **width** of a sequence is the difference between the maximum and minimum elements in the sequence.

Given an array of integers `nums`, return the sum of the widths of all the non-empty subsequences of `nums`. Since the answer may be very large, return it modulo `10^9 + 7`.

A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements.

### Example 1:
```
Input: nums = [2,1,3]
Output: 6
Explanation: The subsequences are [1], [2], [3], [2,1], [2,3], [1,3], [2,1,3].
The corresponding widths are 0, 0, 0, 1, 1, 2, 2.
The sum of these widths is 6.
```

### Constraints:
- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^5`

---

## 💡 Intuition & Approach

The naive approach is to generate all $2^N - 1$ subsequences, compute their widths, and sum them up. This takes $\mathcal{O}(2^N)$ time and is impossible given $N \le 10^5$.

We need a mathematically optimal way to compute the sum. 

1. **Order Independence:** The width of a subsequence depends *only* on its maximum and minimum elements. The relative order of elements in the original array does not change the set of subsequences nor their elements. Therefore, we can safely **sort** the array.
2. **Individual Contribution:** Instead of calculating `max - min` per subsequence, we sum the contributions of all max elements and subtract the contributions of all min elements across all subsequences.
3. **Combinatorics:** Let's look at `nums[i]` in the sorted array (0-indexed). 
   - `nums[i]` will be the **maximum** in any subsequence formed by it and a subset of the elements to its left. Since there are $i$ elements to its left, there are $2^i$ such subsequences. Thus, its contribution as a maximum is `nums[i] * 2^i`.
   - `nums[i]` will be the **minimum** in any subsequence formed by it and a subset of the elements to its right. Since there are $n - 1 - i$ elements to its right, there are $2^{n - 1 - i}$ such subsequences. Thus, its contribution as a minimum is `-nums[i] * 2^{n - 1 - i}`.
4. **Total Sum:** The answer is:
   $$\sum_{i=0}^{n-1} \left( nums[i] \cdot 2^i - nums[i] \cdot 2^{n - 1 - i} \right)$$
   This can be efficiently computed in a single pass while tracking powers of 2.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$ — Sorting the array is the bottleneck. The subsequent loop runs in $\mathcal{O}(N)$ time.
- **Space Complexity:** $\mathcal{O}(1)$ or $\mathcal{O}(N)$ — Depending on the language's sorting algorithm implementation.

---

## 🔍 Edge Cases Considered

- `n = 1`: The only subsequence has max = min, so width = 0. Handled correctly.
- Modulo Arithmetic: Subtractions can result in negative numbers under modulo logic in some languages (like C++). We must ensure the final answer is positive by doing `(ans + mod) % mod`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
