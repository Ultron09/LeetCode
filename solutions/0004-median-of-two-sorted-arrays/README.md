# [4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Divide and Conquer](../../topics/binary-search.md), [Array](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively, return the **median** of the two sorted arrays.

The overall run time complexity should be $\mathcal{O}(\log(m + n))$.

### Example 1:
```
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
```

### Example 2:
```
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
```

### Constraints:
- `nums1.length == m`
- `nums2.length == n`
- $0 \le m \le 1000$
- $0 \le n \le 1000$
- $1 \le m + n \le 2000$
- $-10^6 \le \text{nums1}[i], \text{nums2}[i] \le 10^6$

---

## 💡 Intuition & Approach

### 1. The Median Partition Concept
The median divides a combined set of $m + n$ elements into two equal halves (left half and right half) such that every element in the left half is $\le$ every element in the right half:
- **Left Half Size**: $\lfloor \frac{m + n + 1}{2} \rfloor$
- If we take $i$ elements from `nums1`, we must take $j = \lfloor \frac{m + n + 1}{2} \rfloor - i$ elements from `nums2`.

### 2. Binary Search on Array Partition
- Ensure $m \le n$ (swap `nums1` and `nums2` if necessary) so that $i \in [0, m]$ and $j \ge 0$ is always valid.
- For a partition at $(i, j)$:
  - $\text{maxLeft1} = (i == 0) \, ? \, -\infty : \text{nums1}[i-1]$
  - $\text{minRight1} = (i == m) \, ? \, +\infty : \text{nums1}[i]$
  - $\text{maxLeft2} = (j == 0) \, ? \, -\infty : \text{nums2}[j-1]$
  - $\text{minRight2} = (j == n) \, ? \, +\infty : \text{nums2}[j]$

### 3. Partition Invariant & Adjustments
- **Valid Partition**: $\text{maxLeft1} \le \text{minRight2}$ and $\text{maxLeft2} \le \text{minRight1}$.
  - If total elements $m + n$ is odd: $\text{median} = \max(\text{maxLeft1}, \text{maxLeft2})$.
  - If total elements $m + n$ is even: $\text{median} = \frac{\max(\text{maxLeft1}, \text{maxLeft2}) + \min(\text{minRight1}, \text{minRight2})}{2.0}$.
- **Too Far Right**: $\text{maxLeft1} > \text{minRight2} \implies \text{high} = i - 1$.
- **Too Far Left**: $\text{maxLeft2} > \text{minRight1} \implies \text{low} = i + 1$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\log(\min(M, N)))$
  - Binary search is performed over the range $[0, \min(M, N)]$.
  - At most $\log_2(1000) \approx 10$ iterations.
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space.

---

## 🔍 Edge Cases Considered

- **One array is empty**: Handled via $\pm\infty$ sentinels without conditional branching.
- **Disjoint ranges** (`nums1` strictly before or after `nums2`): Correctly converges to $i = 0$ or $i = m$.
- **Even vs. Odd combined length**: Distinct integer/float median return formulas.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
