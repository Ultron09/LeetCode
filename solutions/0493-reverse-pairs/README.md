# [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Divide and Conquer](../../topics/binary-search.md)

---

## 📌 Problem Statement

Given an integer array `nums`, return the **number of reverse pairs** in the array.

A **reverse pair** is a pair `(i, j)` where:
- $0 \le i < j < \text{nums.length}$
- $\text{nums}[i] > 2 \times \text{nums}[j]$

### Example 1:
```
Input: nums = [1,3,2,3,1]
Output: 2
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
```

### Example 2:
```
Input: nums = [2,4,3,5,1]
Output: 3
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
(2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1
```

### Constraints:
- $1 \le \text{nums.length} \le 5 \times 10^4$
- $-2^{31} \le \text{nums}[i] \le 2^{31} - 1$

---

## 💡 Intuition & Approach

### 1. Divide and Conquer via Merge Sort
Finding cross-inversions between pairs of elements in an array can be formulated recursively:
- Split the array into two halves: `[left..mid]` and `[mid+1..right]`.
- Recursively count reverse pairs strictly contained within the left half and right half, while sorting each half in ascending order.
- Count cross-boundary pairs $(i, j)$ where $i \in [\text{left}, \text{mid}]$ and $j \in [\text{mid}+1, \text{right}]$ such that $\text{nums}[i] > 2 \times \text{nums}[j]$.
- Merge the two sorted halves into a single sorted range.

### 2. Two Pointers Monotonicity for Cross-Half Counting
Because both sub-arrays are already sorted in ascending order:
- As the left pointer $i$ advances from $\text{left}$ to $\text{mid}$, $\text{nums}[i]$ is non-decreasing.
- The right pointer $j$ (which tracks all elements satisfying $\text{nums}[i] > 2 \times \text{nums}[j]$) only moves **forward** from $\text{mid}+1$ to $\text{right}+1$.
- Thus, counting all valid pairs across both partitions takes strictly linear time $\mathcal{O}(\text{right} - \text{left} + 1)$ instead of quadratic time.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$
  - Standard merge sort recurrence: $T(N) = 2T(N/2) + \mathcal{O}(N) \implies \mathcal{O}(N \log N)$.
  - With $N \le 5 \times 10^4$, $N \log_2 N \approx 8 \times 10^5$ operations (runs in $< 15\text{ ms}$).
- **Space Complexity:** $\mathcal{O}(N)$
  - Auxiliary buffer `temp` allocated once and reused across all recursive stack frames.

---

## 🔍 Edge Cases Considered

- **32-bit Integer Overflow**: $\text{nums}[j] \times 2$ can overflow signed 32-bit `int` when $\text{nums}[j] \approx 2^{30}$ or $\text{nums}[j] = -2^{31}$. We promote calculations to `long long` via `2LL * nums[j]`.
- **Negative Values**: Monotonicity property holds consistently across negative and positive domains.
- **Single Element Arrays ($N = 1$)**: Returns $0$ immediately without unnecessary recursive splitting.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
