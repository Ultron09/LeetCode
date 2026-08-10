# [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)

**Difficulty:** `Hard`  
**Topics:** [Trees & BST](../../topics/trees.md), [Dynamic Programming](../../topics/dynamic-programming.md), [Depth-First Search](../../topics/trees.md)

---

## 📌 Problem Statement

A **path** in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence **at most once**. Note that the path does not need to pass through the root.

The **path sum** of a path is the sum of the node's values in the path.

Given the `root` of a binary tree, return the **maximum path sum** of any non-empty path.

### Example 1:
```
    1
   / \
  2   3

Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
```

### Example 2:
```
   -10
   /  \
  9   20
     /  \
    15   7

Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
```

### Constraints:
- The number of nodes in the tree is in the range $[1, 3 \times 10^4]$.
- $-1000 \le \text{Node.val} \le 1000$

---

## 💡 Intuition & Approach

### 1. Post-Order Tree DP (Branch Gain vs. Apex Path)
At each node $u$, we distinguish between two concepts:
1. **Branch Gain (Contribution to Parent)**: The maximum path sum starting at $u$ and extending downwards into either its left or right subtree:
   $$\text{branchGain}(u) = u.\text{val} + \max(0, \max(\text{leftGain}, \text{rightGain}))$$
   Negative gains are clamped to $0$ (meaning we can choose not to include that subtree).
2. **Apex Path Sum (Turning Point at $u$)**: The path that bridges through $u$, connecting its left subtree, $u$, and its right subtree:
   $$\text{pathSum}(u) = u.\text{val} + \max(0, \text{leftGain}) + \max(0, \text{rightGain})$$

### 2. Global Maxima Tracking
Maintain a global variable `globalMax` initialized to $\text{INT\_MIN}$. At every node, update $\text{globalMax} = \max(\text{globalMax}, \text{pathSum}(u))$, and return $\text{branchGain}(u)$ to the caller.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N \le 3 \times 10^4$ (each node visited exactly once).
- **Space Complexity:** $\mathcal{O}(H)$ for the recursive DFS call stack ($H \le N$, average $\mathcal{O}(\log N)$ for balanced trees).

---

## 🔍 Edge Cases Considered

- **All Negative Node Values** (e.g. `[-3]` or `[-10, -20, -30]`): Correctly chooses the single maximum negative node (e.g. $-3$).
- **Single Node Tree**: Returns `root->val`.
- **Skewed / Linear Trees**: Recursion depth handled cleanly without excess allocations.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
