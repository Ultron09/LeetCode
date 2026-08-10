# [154. Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Suppose an array of length `n` sorted in ascending order is rotated between `1` and `n` times.

Given the sorted rotated array `nums` that may contain **duplicates**, return the **minimum element** of this array.

You must decrease the overall operation steps as much as possible.

### Example 1:
```
Input: nums = [1,3,5]
Output: 1
```

### Example 2:
```
Input: nums = [2,2,2,0,1]
Output: 0
```

### Constraints:
- $n == \text{nums.length}$
- $1 \le n \le 5000$
- $-5000 \le \text{nums}[i] \le 5000$
- `nums` is sorted and rotated between $1$ and $n$ times.

---

## 💡 Intuition & Approach

### 1. Binary Search with Pivot Comparison
We maintain a search interval `[left, right]`. We compare the middle element `nums[mid]` against the right boundary `nums[right]`:
- **Case 1: `nums[mid] > nums[right]`**:
  - The pivot (point of descent) and minimum must lie strictly in the right half `[mid + 1, right]`.
  - Set `left = mid + 1`.
- **Case 2: `nums[mid] < nums[right]`**:
  - The right half `[mid, right]` is sorted in ascending order.
  - The minimum could be `mid` itself or lie to its left.
  - Set `right = mid`.
- **Case 3: `nums[mid] == nums[right]` (Handling Duplicates)**:
  - We cannot determine which half contains the inflection point (e.g. `[1, 0, 1, 1, 1]` vs `[1, 1, 1, 0, 1]`).
  - However, because `nums[mid] == nums[right]`, removing `nums[right]` by decrementing `right--` will not discard the minimum value as long as `left < right`.
  - Set `right--`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** 
  - **Average Case:** $\mathcal{O}(\log N)$ — Binary search halves the search space when elements are distinct.
  - **Worst Case:** $\mathcal{O}(N)$ — Occurs when almost all elements are identical (e.g. `[2, 2, 2, 2, 2]`), forcing linear shrinking `right--`.
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space.

---

## 💬 Follow-up Discussion

> **Q:** Would duplicate elements affect the runtime complexity? How and why?  
> **A:** **Yes.** In the distinct elements case (LeetCode 153), every iteration halves the search space yielding a guaranteed $\mathcal{O}(\log N)$ worst-case. With duplicates, whenever `nums[mid] == nums[right]`, the algorithm cannot determine whether the inflection point lies in the left or right subarray without further inspection. Decrementing the boundary by 1 (`right--`) handles this safely, but degrades the worst-case time complexity to $\mathcal{O}(N)$.

---

## 🔍 Edge Cases Considered

- **Pivot at start or end**: Handled seamlessly by interval contraction.
- **All elements identical**: Degrades to linear scan $\mathcal{O}(N)$ correctly finding the element.
- **Alternating duplicates**: (e.g. `[3, 1, 3]`, `[10, 1, 10, 10, 10]`).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
