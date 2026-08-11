# [2996. Smallest Missing Integer Greater Than Sequential Prefix Sum](https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/)

**Difficulty:** `Easy`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given a 0-indexed array of integers `nums`.

A prefix `nums[0..i]` is **sequential** if, for all $1 \le j \le i$, $\text{nums}[j] = \text{nums}[j - 1] + 1$. In particular, the prefix consisting only of `nums[0]` is sequential.

Return the smallest integer $x$ missing from `nums` such that $x \ge \text{sum of the longest sequential prefix}$.

### Example 1:
```
Input: nums = [1,2,3,2,5]
Output: 6
Explanation: The longest sequential prefix of nums is [1,2,3] with a sum of 6. 
6 is not in the array, therefore 6 is the smallest missing integer greater than or equal to the sum of the longest sequential prefix.
```

### Example 2:
```
Input: nums = [3,4,5,1,12,14,13]
Output: 15
Explanation: The longest sequential prefix of nums is [3,4,5] with a sum of 12. 
12, 13, and 14 belong to the array while 15 does not. Therefore 15 is the smallest missing integer greater than or equal to the sum of the longest sequential prefix.
```

### Constraints:
- $1 \le \text{nums.length} \le 50$
- $1 \le \text{nums}[i] \le 50$

---

## 💡 Intuition & Approach

### 1. Identify the Longest Sequential Prefix
- Start at index $0$ with `prefixSum = nums[0]`.
- Iterate through $i = 1, 2, \dots, N - 1$.
- As long as $\text{nums}[i] == \text{nums}[i-1] + 1$, add $\text{nums}[i]$ to `prefixSum`.
- As soon as the sequential condition breaks ($\text{nums}[i] \ne \text{nums}[i-1] + 1$), terminate the scan immediately.

### 2. Fast Existence Query with Hash Set
- Insert all elements of `nums` into an `unordered_set<int>`.
- Initialize candidate value $x = \text{prefixSum}$.
- While $x$ exists in the hash set (`numSet.count(x)`), increment $x \gets x + 1$.
- Return the first integer $x$ that is **not** present in the array.

Because the array contains at most $N$ unique elements, the while-loop can execute at most $N$ iterations before discovering a missing integer.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - Scanning the sequential prefix takes $\mathcal{O}(N)$ time.
  - Constructing the hash set takes $\mathcal{O}(N)$ time.
  - Probing for the missing integer takes at most $N$ increments with $\mathcal{O}(1)$ average hash set lookups.
  - Total time: $\mathcal{O}(N)$.
- **Space Complexity:** $\mathcal{O}(N)$
  - Hash set storing at most $N$ distinct values from `nums`.

---

## 🔍 Edge Cases Considered

- **Single-Element Array ($N = 1$)**: Sequential prefix is `[nums[0]]`, sum is `nums[0]`. The loop increments candidate to `nums[0] + 1`, which is not in `nums` $\to$ correctly returns `nums[0] + 1`.
- **Sequential Sequence Broken at Index 1**: e.g. `nums = [5, 1, 2, 3]`. Prefix is `[5]`, sum is 5 $\to$ returns 6.
- **Prefix Sum Already Absent from Array**: Immediately returns `prefixSum` on the first check.
- **Continuous Block of Present Values**: Increments smoothly across consecutive present values until hitting the first gap.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
