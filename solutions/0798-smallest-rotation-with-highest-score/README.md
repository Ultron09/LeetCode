# [798. Smallest Rotation with Highest Score](https://leetcode.com/problems/smallest-rotation-with-highest-score/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), Prefix Sum

---

## 📌 Problem Statement

You are given an array `nums`. You can rotate it by a non-negative integer `k` so that the array becomes `[nums[k], nums[k + 1], ... nums[nums.length - 1], nums[0], nums[1], ..., nums[k-1]]`. Afterward, any entries that are less than or equal to their index are worth one point.

For example, if we have `nums = [2,4,1,3,0]`, and we rotate by `k = 2`, it becomes `[1,3,0,2,4]`. This is worth 3 points because `1 > 0` [no points], `3 > 1` [no points], `0 <= 2` [one point], `2 <= 3` [one point], `4 <= 4` [one point].

Return the rotation index `k` that corresponds to the highest score we can achieve if we rotated `nums` by it. If there are multiple answers, return the smallest such index `k`.

### Example 1:
```
Input: nums = [2,3,1,4,0]
Output: 3
Explanation: Scores for each k are listed below: 
k = 0,  nums = [2,3,1,4,0],    score 2
k = 1,  nums = [3,1,4,0,2],    score 3
k = 2,  nums = [1,4,0,2,3],    score 3
k = 3,  nums = [4,0,2,3,1],    score 4
k = 4,  nums = [0,2,3,1,4],    score 3
So we should choose k = 3, which has the highest score.
```

### Constraints:
- `1 <= nums.length <= 10^5`
- `0 <= nums[i] < nums.length`

---

## 💡 Intuition & Approach

We can't afford to literally rotate the array and recalculate the score for each `k` because that would take $\mathcal{O}(N^2)$ time, which is too slow for $N = 10^5$. Instead, we should flip the perspective: **For a specific element `nums[i]`, what are the values of `k` that allow it to score a point?**

If we rotate by `k`, the element originally at index `i` moves to a new index `j = (i - k + N) % N`.
We get a point if `nums[i] <= j`.

The valid range for the new index `j` is `[nums[i], N - 1]`.
We can map this range of `j` back to a range of valid rotations `k`:
- When `j = N - 1` (the maximum index), `k = (i - (N - 1) + N) % N = (i + 1) % N`.
- When `j = nums[i]` (the minimum index), `k = (i - nums[i] + N) % N`.

As `j` decreases from `N - 1` to `nums[i]`, the required `k` continuously increases. Thus, for each element `nums[i]`, it contributes `+1` to the score for `k` in the contiguous range:
`[(i + 1) % N, (i - nums[i] + N) % N]`

Because this range is modular (it wraps around `N`), there are two cases:
1. **Normal Range** (`left <= right`): The element scores for `k \in [left, right]`.
2. **Wrapped Range** (`left > right`): The element scores for `k \in [left, N-1]` AND `k \in [0, right]`.

### Difference Array
Since we have $N$ range addition operations and want to find the maximum overlapping point, we can use a **Difference Array**. 
To add `1` to the range `[L, R]`, we do:
```cpp
diff[L]++;
diff[R + 1]--;
```
After processing all elements in $\mathcal{O}(N)$ time, we sweep through the difference array, computing the prefix sum to get the total score for each `k`. We keep track of the max score and the smallest `k` that achieved it.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — One pass over the array to populate the difference array bounds, and a second pass to compute the prefix sums and find the max score.
- **Space Complexity:** $\mathcal{O}(N)$ — For the difference array of size `N + 1`.

---

## 🔍 Edge Cases Considered

- **Wrap-around Ranges:** If the calculated `k` range wraps over the end of the array (e.g., `[4, 1]`), we correctly split it into `[4, N-1]` and `[0, 1]`.
- **Zero Values:** Handled correctly. If `nums[i] == 0`, it scores a point for all `j` except when `j < 0` (impossible), which covers all valid indices and correctly assigns spans across the full array length.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
