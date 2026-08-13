# [805. Split Array With Same Average](https://leetcode.com/problems/split-array-with-same-average/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), Math, Meet in the Middle, Bit Manipulation

---

## 📌 Problem Statement

You are given an integer array `nums`.

You should move each element of `nums` into one of the two arrays `A` and `B` such that `A` and `B` are non-empty, and `average(A) == average(B)`.

Return `true` if it is possible to achieve that and `false` otherwise.

Note that for an array `arr`, `average(arr)` is the sum of all the elements of `arr` over the length of `arr`.

### Example 1:
```
Input: nums = [1,2,3,4,5,6,7,8]
Output: true
Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have an average of 4.5.
```

### Example 2:
```
Input: nums = [3,1]
Output: false
```

### Constraints:
- `1 <= nums.length <= 30`
- `0 <= nums[i] <= 10^4`

---

## 💡 Intuition & Approach

Finding two subsets with the same average can be mathematically transformed to avoid floating point comparisons and complex state tracking.
If `average(A) == average(B)`, then both subsets must have an average equal to the overall average of the array `nums`.

Let `S` be the sum of the array and `N` be its length. The average is `S / N`.
We want to find a proper subset `A` such that `sum(A) / size(A) == S / N`.
This means `N * sum(A) - S * size(A) == 0`.

We can shift the values of the array to center the target average at `0`.
For every element `x` in `nums`, transform it to: `a[i] = x * N - S`.
Now, our goal reduces to a classic problem: **Find any proper, non-empty subset of `a` that sums to exactly 0.**

### Meet-in-the-Middle Algorithm
Since $N \le 30$, iterating over all $2^{30}$ subsets is too slow (approx $10^9$ operations).
We can use a Meet-in-the-Middle approach:
1. Divide `a` into two halves: `left` (size $N/2$) and `right` (size $N - N/2$).
2. Compute all subset sums for the `left` half. If any non-empty subset sums to 0, return `true`. Otherwise, save the unique sums in a sorted array `left_sums`.
3. Compute all subset sums for the `right` half. We test all subsets **except the full `right` subset**.
   - If any subset sums to 0, return `true`.
   - Otherwise, if its `sum` has a complement `-sum` in `left_sums` (using binary search), return `true`.

**Why skip the full `right` subset?**
We need a *proper* subset (meaning we can't select all elements). If a valid solution required the full `right` half and a subset of `left`, its complement (the remaining elements in `left`) would also sum to 0. Since the complement resides entirely in `left`, it would have been found during step 2! This elegantly avoids accidentally selecting the entire array while maintaining completeness.

### Pruning
Before even generating the transformed array `a`, we can check if it's theoretically possible. 
For a valid subset of size $k$ ($1 \le k \le N/2$), its sum must be an integer: $(S \cdot k) \pmod N == 0$. If no such $k$ exists, return `false` instantly.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(2^{N/2} \log(2^{N/2}))$. For $N = 30$, $N/2 = 15$. $2^{15} = 32,768$. Generating and sorting the left sums takes negligible time, making the algorithm extremely fast.
- **Space Complexity:** $\mathcal{O}(2^{N/2})$ to store `left_sums`.

---

## 🔍 Edge Cases Considered

- **$N = 2$:** Handled gracefully. For e.g. `[3, 1]`, no proper subset will have average 2, algorithm returns false.
- **All elements identical:** Transformation makes all elements `0`, algorithm finds `0` instantly.
- **No Fractional Drops:** Scaling each element by $N$ completely eliminates rounding issues that typically plague average calculations.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
