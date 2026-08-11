# [546. Remove Boxes](https://leetcode.com/problems/remove-boxes/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Array](../../topics/arrays-and-hashing.md), [Memoization](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

You are given several boxes with different colors represented by different positive numbers.

You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (i.e., composed of $k$ boxes, $k \ge 1$), remove them and get $k \times k$ points.

Return the **maximum points** you can get.

### Example 1:
```
Input: boxes = [1,3,2,2,2,3,4,3,1]
Output: 23
Explanation:
[1, 3, 2, 2, 2, 3, 4, 3, 1] 
----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
----> [1, 3, 3, 3, 1] (1*1=1 points) 
----> [1, 1] (3*3=9 points) 
----> [] (2*2=4 points)
Total = 9 + 1 + 9 + 4 = 23 points.
```

### Example 2:
```
Input: boxes = [1,1,1]
Output: 9
```

### Example 3:
```
Input: boxes = [1]
Output: 1
```

### Constraints:
- $1 \le \text{boxes.length} \le 100$
- $1 \le \text{boxes}[i] \le 100$

---

## 💡 Intuition & Approach

### 1. Why Standard 2D Interval DP Fails
In standard 2D interval DP $\text{dp}[l][r]$, subproblems are assumed to be independent of external context. However, in this problem, removing intermediate elements from a subarray allows disconnected elements of the same color on the left and right to **concatenate and merge**, yielding superlinear gains ($k^2$).

### 2. Augmenting the State with Predecessors (`k`)
We introduce a 3rd state dimension:
- $\text{dp}[l][r][k]$: the maximum points obtainable from subarray $\text{boxes}[l \dots r]$, given that there are $k$ boxes immediately to the left of $l$ with the exact same color as $\text{boxes}[l]$.

### 3. State Transitions & Pruning Optimizations
1. **Contiguous Same-Color Compression**:
   Advance $l$ and increment $k$ while $\text{boxes}[l+1] == \text{boxes}[l]$.
2. **Option 1: Remove Immediately**:
   Eliminate $\text{boxes}[l]$ together with all $k$ attached predecessors:
   $$\text{Points} = (k + 1)^2 + \text{dp}(l + 1, r, 0)$$
3. **Option 2: Clear Intermediate Boxes to Merge with $\text{boxes}[m]$**:
   For each index $m \in [l + 1, r]$ where $\text{boxes}[m] == \text{boxes}[l]$:
   - Clear subarray $[l + 1 \dots m - 1]$ with $0$ attached boxes: $\text{dp}(l + 1, m - 1, 0)$.
   - Then $\text{boxes}[l]$ and its $k$ predecessors merge with $\text{boxes}[m]$, contributing $k + 1$ attached boxes to the remaining subproblem $[m \dots r]$: $\text{dp}(m, r, k + 1)$.
   $$\text{Points} = \text{dp}(l + 1, m - 1, 0) + \text{dp}(m, r, k + 1)$$
   - *Pruning*: Skip $m$ if $\text{boxes}[m - 1] == \text{boxes}[l]$ (already covered by initial compression).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^4)$ upper bound, $\mathcal{O}(N^3)$ average
  - Total distinct reachable states $(l, r, k)$ is at most $N^3 / 6 \approx 1.6 \times 10^5$.
  - Transition loops over $m \in [l+1, r]$ ($\le N$ steps).
  - With memoization and run-length skipping, runtime is $< 20\text{ ms}$ for $N = 100$.
- **Space Complexity:** $\mathcal{O}(N^3)$
  - 3D memoization array $\text{memo}[100][100][100] \approx 4\text{ MB}$.

---

## 🔍 Edge Cases Considered

- **All Identical Boxes ($N$ same colors)**: Compresses immediately to $(N)^2 = N^2$.
- **Alternating Sequences (`[1, 2, 1, 2, 1]`)**: Correctly explores merging outer pairs versus clearing inner singletons.
- **Single Element Array ($N = 1$)**: Returns $1$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
