# [1665. Minimum Initial Energy to Finish Tasks](https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an array `tasks` where `tasks[i] = [actual_i, minimum_i]`:
- `actual_i`: The actual energy consumed to finish the $i$-th task.
- `minimum_i`: The minimum threshold of energy required to *start* the $i$-th task.

You can finish the tasks in **any order**. Return the **minimum initial amount of energy** required to complete all tasks.

### Example 1:
```
Input: tasks = [[1,2],[2,4],[4,8]]
Output: 8
Explanation:
- Task 3 (actual 4, min 8): Energy starts at 8, ends at 4.
- Task 2 (actual 2, min 4): Energy starts at 4, ends at 2.
- Task 1 (actual 1, min 2): Energy starts at 2, ends at 1.
```

### Example 2:
```
Input: tasks = [[1,3],[2,4],[10,11],[10,12],[8,9]]
Output: 32
```

### Example 3:
```
Input: tasks = [[1,7],[2,8],[3,9],[4,10],[5,11],[6,12]]
Output: 27
```

### Constraints:
- $1 \le \text{tasks.length} \le 10^5$
- $1 \le \text{actual}_i \le \text{minimum}_i \le 10^4$

---

## 💡 Intuition & Approach

### 1. Exchange Argument Proof
Consider two adjacent tasks $A$ and $B$:
- **Order $A \to B$**:
  - Energy needed before starting: $\max(minimum_A, \, actual_A + minimum_B)$.
- **Order $B \to A$**:
  - Energy needed before starting: $\max(minimum_B, \, actual_B + minimum_A)$.

Comparing the two:
$$\max(minimum_A, \, actual_A + minimum_B) \le \max(minimum_B, \, actual_B + minimum_A)$$
Subtracting $actual_A + actual_B$ from both sides:
$$minimum_A - actual_A \ge minimum_B - actual_B$$

Thus, we must process tasks in **descending order of $(minimum_i - actual_i)$** (i.e. prioritize tasks that require the largest initial buffer difference).

### 2. Single-Pass Simulation
1. Sort `tasks` such that `(b[1] - b[0]) < (a[1] - a[0])`.
2. Maintain `totalEnergyNeeded` and `currentEnergy` (both initially 0).
3. For each task `[actual, minimum]`:
   - If `currentEnergy < minimum`, add `(minimum - currentEnergy)` to `totalEnergyNeeded` and lift `currentEnergy = minimum`.
   - Subtract `actual` from `currentEnergy`.
4. Return `totalEnergyNeeded`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$ where $N = \text{tasks.length} \le 10^5$
  - Sorting takes $\mathcal{O}(N \log N)$ time.
  - Linear scan takes $\mathcal{O}(N)$ time.
  - Total runtime $< 45$ ms in C++.
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space ($\mathcal{O}(\log N)$ recursion stack for `std::sort`).

---

## 🔍 Edge Cases Considered

- **All tasks have $actual_i == minimum_i$**: The difference is 0; tasks can be run in any order, needing $\sum actual_i$.
- **Large energy differences**: Handled cleanly without overflow within standard 32-bit signed integers.
- **Single task**: Directly returns $minimum_0$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
