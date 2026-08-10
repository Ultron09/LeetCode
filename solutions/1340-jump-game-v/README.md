# [1340. Jump Game V](https://leetcode.com/problems/jump-game-v/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an array of integers `arr` and an integer `d`. In one step you can jump from index `i` to index `j` if:
1. `0 <= j < arr.length` and $|i - j| \le d$.
2. `arr[i] > arr[j]` (you can only jump downwards to strictly smaller heights).
3. `arr[i] > arr[k]` for all indices `k` strictly between `i` and `j` (you cannot jump over any equal or taller pillars).

You can choose any index as the starting position. Return the **maximum number of indices** you can visit.

### Example 1:
```
Input: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
Output: 4
Explanation: You can start at index 10 (value 12). Jump path: 10 (12) -> 8 (10) -> 6 (9) -> 7 (7).
```

### Example 2:
```
Input: arr = [3,3,3,3,3], d = 3
Output: 1
Explanation: You can start at any index, but you cannot jump anywhere because all elements are equal.
```

### Example 3:
```
Input: arr = [7,6,5,4,3,2,1], d = 1
Output: 7
Explanation: Start at index 0 and visit all indices sequentially.
```

### Constraints:
- $1 \le \text{arr.length} \le 1000$
- $1 \le \text{arr}[i] \le 10^5$
- $1 \le d \le \text{arr.length}$

---

## 💡 Intuition & Approach

### 1. Directed Acyclic Graph (DAG) Structure
Since every valid jump strictly decreases the pillar height (`arr[j] < arr[i]`), there can never be any cyclic dependencies. The state transitions naturally form a **Directed Acyclic Graph (DAG)**.

### 2. Memoized DFS (Top-Down Dynamic Programming)
Let `dp[i]` denote the maximum number of visited indices starting at index `i`.
$$\text{dp}[i] = 1 + \max_{j \in \text{valid jumps from } i} (\text{dp}[j])$$

For each index `i`:
- **Scan Right**: Traverse $j = i + 1 \dots \min(i + d, n - 1)$. As soon as $\text{arr}[j] \ge \text{arr}[i]$, the view is blocked, so break immediately. Otherwise, transition to $\text{dfs}(j)$.
- **Scan Left**: Traverse $j = i - 1 \dots \max(i - d, 0)$. As soon as $\text{arr}[j] \ge \text{arr}[i]$, break immediately. Otherwise, transition to $\text{dfs}(j)$.
- Memoize `memo[i] = dp[i]`.

The overall answer is $\max_{0 \le i < n} \text{dp}[i]$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot D)$
  - There are $N$ distinct states.
  - Each state explores at most $2D$ adjacent neighbors before hitting bounds or a taller pillar.
  - Total operations $\le 1000 \times 2000 = 2 \times 10^6$ ($< 10$ ms in C++).
- **Space Complexity:** $\mathcal{O}(N)$
  - Memoization array `memo` of size $N$ and recursion depth at most $N$.

---

## 🔍 Edge Cases Considered

- **All Elements Equal**: No jumps possible; returns 1.
- **Strictly Decreasing / Increasing Array**: Linear path visits all $N$ elements.
- **$D \ge N$**: Clamped cleanly by array boundaries $[0, N - 1]$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
