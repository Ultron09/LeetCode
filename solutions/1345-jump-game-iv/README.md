# [1345. Jump Game IV](https://leetcode.com/problems/jump-game-iv/)

**Difficulty:** `Hard`  
**Topics:** [Graphs & BFS/DFS](../../topics/graphs.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an array of integers `arr`, you are initially positioned at the first index of the array (`index 0`).

In one step, you can jump from index `i` to:
1. `i + 1` (where $i + 1 < \text{arr.length}$)
2. `i - 1` (where $i - 1 \ge 0$)
3. `j` (where $\text{arr}[i] == \text{arr}[j]$ and $i \ne j$)

Return the **minimum number of steps** to reach the last index of the array (`index arr.length - 1`).

### Example 1:
```
Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: Jump path: 0 (100) -> 4 (100) -> 3 (404) -> 9 (404).
```

### Example 2:
```
Input: arr = [7]
Output: 0
Explanation: Start index is already the destination.
```

### Example 3:
```
Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: Jump directly from index 0 to index 7 since arr[0] == arr[7] == 7.
```

### Constraints:
- $1 \le \text{arr.length} \le 5 \times 10^4$
- $-10^8 \le \text{arr}[i] \le 10^8$

---

## 💡 Intuition & Approach

### 1. Unweighted Graph Shortest Path (BFS)
The problem asks for the minimum number of transitions to reach the target, where every jump costs 1 step. This is an unweighted shortest-path problem naturally solved using **Breadth-First Search (BFS)**.

### 2. Preventing $\mathcal{O}(N^2)$ Edge Explosion
If an array contains many elements with the same value (e.g. $5 \times 10^4$ identical numbers), all pairs of matching elements induce complete cliques ($\approx \frac{N^2}{2}$ edges).
- **Optimization**: Once all indices sharing a value $V$ have been added to the BFS queue from one node, we **clear/erase** the entry for $V$ from our index map (`valToIndices.erase(it)`).
- This guarantees that each value group's list of indices is traversed **at most once**, ensuring strict linear time complexity $\mathcal{O}(N)$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - Each index is pushed into the queue at most once.
  - The adjacency list for identical elements is cleared immediately upon first visit.
  - Total operations $\le 3N \approx 1.5 \times 10^5$ ($< 25$ ms in C++).
- **Space Complexity:** $\mathcal{O}(N)$
  - Hash map storing index lists for all elements: $\mathcal{O}(N)$.
  - BFS `visited` vector and `queue`: $\mathcal{O}(N)$.

---

## 🔍 Edge Cases Considered

- **$N = 1$**: Handled in $\mathcal{O}(1)$ returning 0 steps.
- **All Elements Equal**: Jumps directly $0 \to N - 1$ in 1 step.
- **Negative / Large Integers**: Handled seamlessly by `unordered_map<int, vector<int>>`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
