# [3661. Maximum Walls Destroyed by Robots](https://leetcode.com/problems/maximum-walls-destroyed-by-robots/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Binary Search](../../topics/binary-search.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

There is an endless straight line populated with robots and walls. You are given:
- `robots`: An array where `robots[i]` is the coordinate of the $i$-th robot.
- `distance`: An array where `distance[i]` is the maximum shooting distance of the $i$-th robot.
- `walls`: An array where `walls[j]` is the position of the $j$-th wall.

### Rules:
1. Each robot can fire **one bullet**, either strictly **to the left** or strictly **to the right**.
2. A bullet travels up to `distance[i]` and destroys every wall in its trajectory.
3. **Robots act as impassable barriers**: If a bullet strikes another robot, it immediately stops and cannot travel further.
4. A wall located at the exact position of a robot can only be destroyed by that robot (firing in either direction).

Return the **maximum number of unique walls** that can be destroyed.

### Example 1:
```
Input: robots = [4], distance = [3], walls = [1, 10]
Output: 1
Explanation: Robot at 4 fires left with distance 3 (range [1, 4]), destroying the wall at 1.
```

### Example 2:
```
Input: robots = [10, 2], distance = [5, 1], walls = [5, 2, 7]
Output: 3
Explanation:
- Robot at 10 fires left with distance 5 (range [5, 10]), destroying walls at 5 and 7.
- Robot at 2 fires left with distance 1 (range [1, 2]), destroying wall at 2.
Total unique walls destroyed = 3.
```

### Example 3:
```
Input: robots = [1, 2], distance = [100, 1], walls = [10]
Output: 0
Explanation: Robot at 1 cannot shoot right past robot at 2. Wall at 10 remains safe.
```

### Constraints:
- $n == \text{robots.length} == \text{distance.length} \le 10^5$
- $m == \text{walls.length} \le 10^5$
- $1 \le \text{robots}[i], \text{walls}[j] \le 10^9$
- $1 \le \text{distance}[i] \le 10^9$

---

## 💡 Intuition & Approach

### 1. Spatial Ordering & Blocking Ranges
Sort both `robots` (along with their `distance`) and `walls`.
For the $i$-th sorted robot at coordinate $r_i$:
- **Firing Left**: The bullet can reach at most $r_i - d_i$, but is blocked by robot $i-1$ at coordinate $r_{i-1}$.
  $$\text{Left Range} = [\max(r_i - d_i, r_{i-1} + 1), \, r_i]$$
- **Firing Right**: The bullet can reach at most $r_i + d_i$, but is blocked by robot $i+1$ at coordinate $r_{i+1}$.
  $$\text{Right Range} = [r_i, \, \min(r_i + d_i, r_{i+1} - 1)]$$

Wall counts in any interval $[L, R]$ can be queried in $\mathcal{O}(\log M)$ using `std::lower_bound` and `std::upper_bound` on the sorted `walls` array.

### 2. Dynamic Programming State Transitions
Let:
- `dp[0]` = Maximum unique walls destroyed considering first $i$ robots, with robot $i$ firing **LEFT**.
- `dp[1]` = Maximum unique walls destroyed considering first $i$ robots, with robot $i$ firing **RIGHT**.

For robot $i \ge 1$:
1. **Robot $i$ fires LEFT (`next_dp0`)**:
   - If robot $i-1$ fired LEFT: Their target intervals are disjoint $\implies dp[0] + \text{left}[i]$.
   - If robot $i-1$ fired RIGHT: Both robot $i-1$ (right) and robot $i$ (left) shoot into the shared gap $(r_{i-1}, r_i)$. Their combined coverage is capped at `num_between` (the total walls in $[r_{i-1}, r_i]$):
     $$dp[1] - \text{right}[i-1] + \min(\text{right}[i-1] + \text{left}[i], \, \text{num\_between})$$
2. **Robot $i$ fires RIGHT (`next_dp1`)**:
   - Regardless of whether robot $i-1$ fired left or right, robot $i$'s rightward trajectory does not overlap with any previous robot's coverage:
     $$\max(dp[0], dp[1]) + \text{right}[i]$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N + M \log M + N \log M)$
  - Sorting robots: $\mathcal{O}(N \log N)$.
  - Sorting walls: $\mathcal{O}(M \log M)$.
  - Binary search queries: $3$ queries per robot $\implies \mathcal{O}(N \log M)$.
  - Total time $< 25$ ms in C++.
- **Space Complexity:** $\mathcal{O}(N)$ for robot coordinate pairing and $\mathcal{O}(1)$ DP rolling state space.

---

## 🔍 Edge Cases Considered

- $N = 1$: Single robot, left/right ranges unconstrained by neighbor robots.
- Overlapping coverage between two facing robots: Capped by the exact number of walls in the intermediate interval.
- Large coordinates ($10^9$): Coordinates handled natively with standard 32/64-bit comparisons without overflow.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
