# [887. Super Egg Drop](https://leetcode.com/problems/super-egg-drop/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [Dynamic Programming](../../topics/dynamic-programming.md), [Binary Search](../../topics/binary-search.md)

---

## 📌 Problem Statement

You are given `k` identical eggs and you have access to a building with `n` floors labeled from `1` to `n`.

You know that there exists a floor `f` where `0 <= f <= n` such that any egg dropped at a floor higher than `f` will break, and any egg dropped at or below floor `f` will not break.

Each move, you may take an unbroken egg and drop it from any floor `x` (where `1 <= x <= n`). If the egg breaks, you can no longer use it. However, if the egg does not break, you may reuse it in future moves.

Return the minimum number of moves that you need to determine with certainty what the value of `f` is.

### Example 1:
```
Input: k = 1, n = 2
Output: 2
Explanation: 
Drop the egg from floor 1. If it breaks, we know that f = 0.
Otherwise, drop the egg from floor 2. If it breaks, we know that f = 1.
If it does not break, then we know f = 2.
Hence, we need at minimum 2 moves to determine with certainty what the value of f is.
```

### Constraints:
- `1 <= k <= 100`
- `1 <= n <= 10^4`

---

## 💡 Intuition & Approach

This is a classic Dynamic Programming problem with a mathematical twist that drastically optimizes the time complexity from $\mathcal{O}(K \cdot N^2)$ to $\mathcal{O}(K \cdot M)$ where $M$ is the answer.

Instead of defining DP state as `dp[k][n]` = minimum moves for `k` eggs and `n` floors, we flip the dimensions:
Let `dp[m][k]` = the **maximum number of floors** we can test with `m` moves and `k` eggs.

When we drop an egg from a floor, two things can happen:
1. **The egg breaks**: We now have `k - 1` eggs and `m - 1` moves. We can check `dp[m - 1][k - 1]` floors below the drop point.
2. **The egg survives**: We still have `k` eggs and `m - 1` moves. We can check `dp[m - 1][k]` floors above the drop point.

Combining these with the 1 floor we just checked at the current drop point, the total floors we can resolve is:
`dp[m][k] = dp[m - 1][k - 1] + dp[m - 1][k] + 1`

We start at `m = 0` and increment `m` until `dp[m][k] >= n`. The first `m` that satisfies this condition is our minimal number of moves. 

Because `dp[m][k]` only depends on `dp[m-1]`, we can optimize this to a 1D DP array updating backwards.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(K \cdot M)$ — Where $K$ is the number of eggs and $M$ is the minimum moves needed (the answer). In the worst case, $M \approx K \log N$, making this algorithm extremely fast and much more optimal than standard $\mathcal{O}(K \cdot N \log N)$ binary search DP approaches.
- **Space Complexity:** $\mathcal{O}(K)$ — A single 1D DP array of size `K + 1` to track the state across `m` iterations.

---

## 🔍 Edge Cases Considered

- `k = 1`: With only 1 egg, we are forced to check every floor linearly from bottom to top. Our relation perfectly gives `dp[m][1] = dp[m-1][0] + dp[m-1][1] + 1 = 0 + (m - 1) + 1 = m`, so $m = n$ moves.
- `m = 1`: One move with `k` eggs allows us to check exactly 1 floor.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
