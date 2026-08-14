# [956. Tallest Billboard](https://leetcode.com/problems/tallest-billboard/)

**Difficulty:** `Hard`  
**Topics:** [Array](../../topics/arrays-and-hashing.md), [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

You are installing a billboard and want it to have the largest height. The billboard will have two steel supports, one on each side. Each steel support must be an equal height.

You are given a collection of rods that can be welded together. For example, if you have rods of lengths `1`, `2`, and `3`, you can weld them together to make a support of length `6`.

Return the largest possible height of your billboard installation. If you cannot support the billboard, return `0`.

### Example 1:
```
Input: rods = [1,2,3,6]
Output: 6
Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
```

### Example 2:
```
Input: rods = [1,2,3,4,5,6]
Output: 10
Explanation: We have two disjoint subsets {2,3,5} and {4,6}, which have the same sum = 10.
```

### Example 3:
```
Input: rods = [1,2]
Output: 0
Explanation: The billboard cannot be supported, so we return 0.
```

### Constraints:
- `1 <= rods.length <= 20`
- `1 <= rods[i] <= 1000`
- `sum(rods[i]) <= 5000`

---

## 💡 Intuition & Approach

This problem can be viewed as selecting two disjoint subsets from `rods` that have an equal sum, such that the sum is maximized. 

A naive approach of generating all possible subsets would take $\mathcal{O}(3^N)$, which is $3^{20} \approx 3.48 \times 10^9$ and will Time Limit Exceeded (TLE). We need a Dynamic Programming approach.

1. **State Definition**:
   Instead of keeping track of the exact sums of both subsets, we only care about their **difference**.
   Let `dp[d]` be the **maximum height of the taller support** such that the height difference between the two supports is exactly `d`.

2. **Initialization**:
   - `dp[0] = 0` (difference 0, height 0)
   - `dp[d] = -1` for all `d > 0` (unreachable states)

3. **Transitions**:
   For each `rod` in `rods`, and for each existing reachable difference `d`:
   - **Option 1**: Weld the `rod` onto the **taller** support.
     The new difference becomes `d + rod`.
     The new taller support height is `dp[d] + rod`.
     `new_dp[d + rod] = max(new_dp[d + rod], dp[d] + rod)`
   - **Option 2**: Weld the `rod` onto the **shorter** support.
     The new difference becomes `|d - rod|`.
     What happens to the taller support's height?
     - If `d >= rod`, the shorter support is still shorter (or equal). The taller support's height remains `dp[d]`.
     - If `d < rod`, the shorter support overtakes the taller one and becomes the new taller support. Its height becomes the old shorter height (`dp[d] - d`) plus `rod`, which is `dp[d] - d + rod`.
     In both cases, the new height of the taller support can be compactly written as `dp[d] + max(0, rod - d)`.
     `new_dp[|d - rod|] = max(new_dp[|d - rod|], dp[d] + max(0, rod - d))`
   - **Option 3**: Don't use the `rod`.
     `new_dp[d] = max(new_dp[d], dp[d])` (this naturally happens by copying the `dp` array before iterating).

4. **Result**:
   After processing all rods, the answer is `dp[0]`, which represents the maximum height where the two supports have a difference of `0`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \times S)$ where $N$ is `rods.length` and $S$ is `sum(rods)`. The maximum sum is 5000, and $N \le 20$. So $20 \times 5000 = 100,000$ operations, which easily passes within the time limit.
- **Space Complexity:** $\mathcal{O}(S)$ since the DP array requires space proportional to the maximum sum $S$.

---

## 🔍 Edge Cases Considered

- Cannot form two non-empty equal subsets (e.g. `[1, 2]`). The base state `dp[0] = 0` is naturally returned.
- A single heavy rod that disrupts everything else. The states easily manage this by evaluating combinations locally bounded up to $S$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
