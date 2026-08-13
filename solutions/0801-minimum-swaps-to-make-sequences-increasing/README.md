# [801. Minimum Swaps To Make Sequences Increasing](https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), Arrays

---

## 📌 Problem Statement

You are given two integer arrays of the same length `nums1` and `nums2`. In one operation, you are allowed to swap `nums1[i]` with `nums2[i]`.

Return the minimum number of needed operations to make `nums1` and `nums2` strictly increasing. The test cases are generated so that the given input always makes it possible.

An array `arr` is strictly increasing if and only if `arr[0] < arr[1] < arr[2] < ... < arr[arr.length - 1]`.

### Example 1:
```
Input: nums1 = [1,3,5,4], nums2 = [1,2,3,7]
Output: 1
Explanation: 
Swap nums1[3] and nums2[3]. Then the sequences are:
nums1 = [1, 3, 5, 7] and nums2 = [1, 2, 3, 4]
which are both strictly increasing.
```

### Constraints:
- `2 <= nums1.length <= 10^5`
- `nums2.length == nums1.length`
- `0 <= nums1[i], nums2[i] <= 2 * 10^5`

---

## 💡 Intuition & Approach

This problem screams **Dynamic Programming** because the optimal decision at index `i` only depends on the elements at `i-1` and the decision we made at `i-1` (whether we swapped them or not).

Let's maintain two variables for any given index `i`:
1. `keep`: The minimum number of swaps required to make the prefix up to `i` valid, given that we **DO NOT** swap at index `i`.
2. `swap`: The minimum number of swaps required to make the prefix up to `i` valid, given that we **DO** swap at index `i`.

### Base Case (index `0`):
- `keep = 0` (we don't swap, cost is 0)
- `swap = 1` (we swap, cost is 1)

### DP Transitions (from `i-1` to `i`):
For any index `i > 0`, we initialize `curr_keep = INF` and `curr_swap = INF`. There are two conditions that allow transitions:

1. **Normal increasing condition:** `nums1[i] > nums1[i - 1]` AND `nums2[i] > nums2[i - 1]`
   If this is true, we can keep the same state between `i-1` and `i`.
   - If we didn't swap at `i-1`, we don't swap at `i`: `curr_keep = min(curr_keep, prev_keep)`
   - If we swapped at `i-1`, we must swap at `i`: `curr_swap = min(curr_swap, prev_swap + 1)`

2. **Cross increasing condition:** `nums1[i] > nums2[i - 1]` AND `nums2[i] > nums1[i - 1]`
   If this is true, we can switch states between `i-1` and `i`.
   - If we swapped at `i-1`, we don't swap at `i`: `curr_keep = min(curr_keep, prev_swap)`
   - If we didn't swap at `i-1`, we swap at `i`: `curr_swap = min(curr_swap, prev_keep + 1)`

Note that these two conditions are not mutually exclusive. Both can be true at the same time, in which case we simply take the minimum across all possible transitions. 
Since the states at `i` only depend on the states at `i-1`, we can optimize the space from $\mathcal{O}(N)$ to $\mathcal{O}(1)$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — We iterate through the arrays once, making constant time calculations at each step.
- **Space Complexity:** $\mathcal{O}(1)$ — Only a few state variables (`prev_keep`, `prev_swap`, `curr_keep`, `curr_swap`) are maintained instead of full DP arrays.

---

## 🔍 Edge Cases Considered

- **Multiple valid paths:** The `min()` function in transitions ensures that even if both conditions (normal and cross) are satisfied, we always carry forward the path with the fewest swaps.
- **Strictly Increasing Rules:** Equality breaks strict increasing; the problem guarantees an answer is always possible, meaning we will never hit a state where both `curr_keep` and `curr_swap` remain `INF`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
