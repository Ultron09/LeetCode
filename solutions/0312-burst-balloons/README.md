# [312. Burst Balloons](https://leetcode.com/problems/burst-balloons/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Array](../../topics/arrays-and-hashing.md), [Intervals](../../topics/intervals.md)

---

## 📌 Problem Statement

You are given `n` balloons, indexed from `0` to `n - 1`. Each balloon is painted with a number on it represented by an array `nums`. You are asked to burst all the balloons.

If you burst the `i`th balloon, you will get `nums[i - 1] * nums[i] * nums[i + 1]` coins. If `i - 1` or `i + 1` goes out of bounds of the array, then treat it as if there is a balloon with a `1` painted on it.

Return **the maximum coins you can collect by bursting the balloons wisely**.

### Example 1:
```
Input: nums = [3,1,5,8]
Output: 167
Explanation:
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
```

### Example 2:
```
Input: nums = [1,5]
Output: 10
```

### Constraints:
- $n == \text{nums.length}$
- $1 \le n \le 300$
- $0 \le \text{nums}[i] \le 100$

---

## 💡 Intuition & Approach

### 1. The Challenge of "Forward" Thinking
If we think about bursting balloons in chronological order (choosing which balloon to burst *first*), the remaining balloons become adjacent, creating dynamic dependencies that break optimal substructure.

### 2. The Breakthrough: "Reverse" Thinking (Last Balloon to Burst)
Instead of asking *“which balloon bursts first?”*, ask:
> **Which balloon $k \in (i, j)$ is the VERY LAST balloon to burst in the open interval $(i, j)$?**

When balloon $k$ is the last balloon to burst in $(i, j)$:
- All other balloons in $(i, k)$ and $(k, j)$ have already been burst.
- Therefore, the remaining neighbors of balloon $k$ are guaranteed to be the boundary balloons $i$ and $j$.
- The coins gained from bursting balloon $k$ last is exactly:
  $$\text{vals}[i] \times \text{vals}[k] \times \text{vals}[j]$$
- The subproblems for the open intervals $(i, k)$ and $(k, j)$ are completely independent.

### 3. State & Recurrence Relation
Pad the array with boundary values $1$: `vals = [1] + nums + [1]`.
Let `dp[i][j]` be the max coins collected in open interval $(i, j)$:
$$\text{dp}[i][j] = \max_{i < k < j} \left( \text{dp}[i][k] + \text{dp}[k][j] + \text{vals}[i] \times \text{vals}[k] \times \text{vals}[j] \right)$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^3)$ where $N \le 300$ ($\approx \frac{N^3}{6} \approx 4.5 \times 10^6$ basic operations).
- **Space Complexity:** $\mathcal{O}(N^2)$ for the 2D DP matrix.

---

## 🔍 Edge Cases Considered

- **$N = 1$**: Handled directly $\implies 1 \times \text{nums}[0] \times 1$.
- **Balloons with value $0$**: Handled natively without special branching.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
