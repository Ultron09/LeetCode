# [2463. Minimum Total Distance Traveled](https://leetcode.com/problems/minimum-total-distance-traveled/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Greedy](../../topics/greedy.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

There are some robots and factories positioned along the X-axis:
- `robot[i]`: Unique starting position of the $i$-th robot.
- `factory[j] = [position_j, limit_j]`: The position and maximum repair capacity of the $j$-th factory.

Robots move at the same speed along the X-axis until they reach an available factory. To minimize the total travel distance, you can choose each robot's initial direction.

Return the **minimum total distance** traveled by all robots to be repaired.

### Example 1:
```
Input: robot = [0,4,6], factory = [[2,2],[6,2]]
Output: 4
Explanation:
- Robot at 0 goes to factory 1 at 2 (dist = 2).
- Robot at 4 goes to factory 1 at 2 (dist = 2).
- Robot at 6 goes to factory 2 at 6 (dist = 0).
Total distance = 2 + 2 + 0 = 4.
```

### Example 2:
```
Input: robot = [1,-1], factory = [[-2,1],[2,1]]
Output: 2
Explanation:
- Robot at 1 goes to factory 2 at 2 (dist = 1).
- Robot at -1 goes to factory 1 at -2 (dist = 1).
Total distance = 1 + 1 = 2.
```

### Constraints:
- $1 \le \text{robot.length}, \text{factory.length} \le 100$
- $-10^9 \le \text{robot}[i], \, \text{position}_j \le 10^9$
- $0 \le \text{limit}_j \le \text{robot.length}$
- It is guaranteed that all robots can be repaired.

---

## 💡 Intuition & Approach

### 1. Optimal Non-Crossing Property
In a 1D space, if robot $A$ starts to the left of robot $B$, then the optimal assignment will never send $A$ to a factory strictly to the right of $B$'s assigned factory (paths would cross or overlap suboptimally). Thus, sorting both `robot` and `factory` by position preserves monotonicity and allows contiguous partition assignments.

### 2. Dynamic Programming Formulation
Let `dp[i]` be the minimum total distance required to repair the first `i` sorted robots using a subset of processed factories.

For each factory $(pos, limit)$:
- We can choose to assign $k \in [0, limit]$ contiguous robots $(i, i+1, \dots, i+k-1)$ to this factory.
- Transition:
  $$\text{next\_dp}[i + k] = \min(\text{next\_dp}[i + k], \, dp[i] + \sum_{j=i}^{i+k-1} |robot[j] - pos|)$$
- The state is updated iteratively across all factories using rolling 1D arrays.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \cdot N \cdot \min(N, \text{limit}))$ where $N \le 100$ (robots) and $M \le 100$ (factories)
  - Sorting: $\mathcal{O}(N \log N + M \log M)$.
  - DP transitions: $M \times N \times \min(N, \text{limit}) \le 100 \times 100 \times 100 = 10^6$ operations ($< 5$ ms in C++).
- **Space Complexity:** $\mathcal{O}(N)$ using 1D rolling DP table.

---

## 🔍 Edge Cases Considered

- **$limit_j = 0$**: Factory has zero capacity and is skipped cleanly ($k = 0$).
- **Large Coordinates**: Positions reach $\pm 10^9$; distance sums accumulate up to $100 \times 2 \times 10^9 = 2 \times 10^{11}$, handled safely with `long long`.
- **$N = 1$**: Single robot trivially matches nearest available factory.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
