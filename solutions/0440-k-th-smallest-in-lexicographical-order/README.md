# [440. K-th Smallest in Lexicographical Order](https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/)

**Difficulty:** `Hard`  
**Topics:** [Trees & BST](../../topics/trees.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

Given two integers `n` and `k`, return the $k^{\text{th}}$ lexicographically smallest integer in the range $[1, n]$.

### Example 1:
```
Input: n = 13, k = 2
Output: 10
Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
```

### Example 2:
```
Input: n = 1, k = 1
Output: 1
```

### Constraints:
- $1 \le k \le n \le 10^9$

---

## 💡 Intuition & Approach

### 1. The 10-ary Prefix Tree (Denary Tree) Concept
All numbers from $1$ to $n$ can be organized conceptually as a 10-ary prefix tree (Trie):
- The root has 9 children: $1, 2, 3, 4, 5, 6, 7, 8, 9$.
- Each node $x$ has 10 children: $10x, 10x+1, \dots, 10x+9$.
- A **pre-order traversal** (Root $\to$ Children from left to right) of this tree visits numbers in **exact lexicographical order**.

```
                [Root]
         /    /   |   \    \
        1    2    3 ... 8    9
       / \
     10  11 ... 19
    /
  100 ...
```

### 2. Subtree Size Counting (`countSteps`)
To determine whether the $k^{\text{th}}$ number is within the subtree rooted at `curr`:
- Count all nodes in the subtree of `curr` bounded by $n$:
  - Level 0: $[curr, curr + 1)$
  - Level 1: $[curr \times 10, (curr + 1) \times 10)$
  - Level 2: $[curr \times 100, (curr + 1) \times 100)$
  - Level $L$: $[first, last)$ where nodes at this depth are $\min(n + 1, last) - first$.
- Repeat while $first \le n$.

### 3. Tree Traversal & Pruning
Start at `curr = 1` with remaining steps $k \gets k - 1$:
- Compute `steps = countSteps(curr, n)`.
- **Case 1 (`steps <= k`)**: The target is **not** in the subtree rooted at `curr`.
  - Skip the entire subtree: `k -= steps`.
  - Move horizontally to the right sibling: `curr += 1`.
- **Case 2 (`steps > k`)**: The target **is** inside the subtree of `curr`.
  - Descend into the leftmost child: `curr *= 10`.
  - Decrement step count: `k -= 1` (accounting for visiting `curr * 10`).

Terminate when $k = 0$ and return `curr`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}((\log_{10} n)^2)$
  - The maximum depth of the tree is $\log_{10} n \le 10$.
  - At each step, calculating `countSteps` takes $\mathcal{O}(\log_{10} n)$ iterations.
  - Across the entire search, we move down at most $\log_{10} n$ times and move right at most 9 times per level.
  - Total operations $\le 10 \times 9 \times 10 \approx 900 \ll 10^8$ (executes in $< 0.1\text{ ms}$).
- **Space Complexity:** $\mathcal{O}(1)$
  - Only scalar 64-bit integer variables are maintained.

---

## 🔍 Edge Cases Considered

- **$n = 1, k = 1$**: Handled in $\mathcal{O}(1)$ step.
- **$k = n$**: Correctly identifies the largest lexicographical string (e.g. `9`, `99`, `999999999`).
- **Intermediate Level Clamping**: Partial levels (where only a subset of interval $[first, last)$ is $\le n$) are precisely clamped using $\min(n + 1, last)$.
- **Integer Overflow**: $first \times 10$ and $last \times 10$ can exceed $2^{31}-1$; 64-bit integer arithmetic (`long long`) prevents overflow.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
