# [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

**Difficulty:** `Hard`  
**Topics:** [Trees & BST](../../topics/trees.md), [Depth-First Search](../../topics/trees.md), [Breadth-First Search](../../topics/trees.md), [Design](../../topics/arrays-and-hashing.md), [String](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

### Example 1:
```
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]
```

### Example 2:
```
Input: root = []
Output: []
```

### Constraints:
- The number of nodes in the tree is in the range $[0, 10^4]$.
- $-1000 \le \text{Node.val} \le 1000$

---

## 💡 Intuition & Approach

### 1. Preorder DFS Traversal with Null Sentinel
A standard preorder traversal is insufficient to uniquely reconstruct a binary tree unless null pointers (`nullptr`) are explicitly marked with a sentinel character (e.g. `'#'` or `'null'`).

### 2. Serialization:
- Traverse the tree in **pre-order** (`Root -> Left -> Right`):
  - If current node is `nullptr`: append `"# "` to the output buffer.
  - Else: append `node->val` followed by space, then recursively serialize `node->left` and `node->right`.

### 3. Deserialization:
- Feed the serialized string into an `std::istringstream`.
- Read token-by-token:
  - If token is `"#"`: return `nullptr`.
  - Otherwise: parse integer value $V$, instantiate `node = new TreeNode(V)`, recursively assign `node->left = deserializeDfs(in)`, `node->right = deserializeDfs(in)`, and return `node`.

---

## ⚡ Complexity Analysis

- **Time Complexity:**
  - `serialize(root)`: $\mathcal{O}(N)$ where $N \le 10^4$ is the number of nodes (visits each node and null leaf once).
  - `deserialize(data)`: $\mathcal{O}(N)$ (reconstructs each tree node in linear time).
- **Space Complexity:** $\mathcal{O}(N)$ for serialized string representation and recursion call stack depth $\mathcal{O}(H)$.

---

## 🔍 Edge Cases Considered

- **Empty Tree (`root == nullptr`)**: Serializes to `"# "` and reconstructs to `nullptr`.
- **Single Node**: Encodes root and two null markers.
- **Skewed / Degenerate Trees**: Recursion depth up to $N = 10^4$ without heap degradation.
- **Negative Node Values**: Preserved through `std::stoi` and `std::ostringstream`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
