# [321. Create Maximum Number](https://leetcode.com/problems/create-maximum-number/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), [Greedy](../../topics/greedy.md), [Two Pointers](../../topics/two-pointers.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given two integer arrays `nums1` and `nums2` of lengths `m` and `n` respectively. `nums1` and `nums2` represent the digits of two numbers. You are also given an integer `k`.

Create the maximum number of length `k <= m + n` from digits of the two numbers. The relative order of the digits from the same array must be preserved.

Return an array of the `k` digits representing the answer.

### Example 1:
```
Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
Output: [9,8,6,5,3]
```

### Example 2:
```
Input: nums1 = [6,7], nums2 = [6,0,4], k = 5
Output: [6,7,6,0,4]
```

### Example 3:
```
Input: nums1 = [3,9], nums2 = [8,9], k = 3
Output: [9,8,9]
```

### Constraints:
- $m == \text{nums1.length}$
- $n == \text{nums2.length}$
- $1 \le m, n \le 500$
- $0 \le \text{nums1}[i], \text{nums2}[i] \le 9$
- $1 \le k \le m + n$
- `nums1` and `nums2` do not have leading zeros.

---

## 💡 Intuition & Approach

The problem naturally decomposes into **three modular subproblems**:

### Subproblem 1: Single-Array Maximum Subsequence (`maxSubsequence`)
To find the lexicographically largest subsequence of length $L$ from an array of length $N$:
- Maintain a monotonic decreasing stack.
- We are allowed to drop at most $N - L$ digits.
- While `drop > 0` and current digit is strictly greater than `stack.top()`, pop and decrement `drop`.
- Truncate stack to size $L$.

### Subproblem 2: Lexicographically Largest Merge (`merge`)
To merge two candidate sequences `seq1` and `seq2` into a single sequence of length $k$:
- At each step, greedily choose the digit from whichever sequence has the **lexicographically larger remaining suffix**.
- If digits match, look ahead until the first difference to break ties.

### Subproblem 3: Enumerating Partition Sizes
Enumerate all valid partition lengths $i$ digits from `nums1` and $k - i$ digits from `nums2`:
$$\max(0, k - n) \le i \le \min(k, m)$$
For each $i$:
1. `s1 = maxSubsequence(nums1, i)`
2. `s2 = maxSubsequence(nums2, k - i)`
3. `candidate = merge(s1, s2, k)`
4. Track the maximum candidate across all valid $i$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(k \cdot (m + n + k^2))$ where $m, n \le 500, k \le 1000$. With $k$ partitions, each merge takes $\mathcal{O}(k^2)$ worst case comparison, running in $< 15\text{ ms}$ in C++.
- **Space Complexity:** $\mathcal{O}(k)$ for monotonic stack and merged candidate buffers.

---

## 🔍 Edge Cases Considered

- **$i = 0$ or $i = k$**: All digits taken exclusively from one array.
- **Identical Prefix in Sequences during Merge**: Tie-breaking looks ahead to future digits correctly.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
