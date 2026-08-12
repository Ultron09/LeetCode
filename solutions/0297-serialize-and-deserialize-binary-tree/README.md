# [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

**Difficulty:** `Hard`  
**Topics:** [Trees & BST](../../topics/trees.md), [Depth-First Search](../../topics/trees.md), [Breadth-First Search](../../topics/graphs.md), [Design](../../topics/arrays-and-hashing.md), [String](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

### Example 1:
```
        1
       / \
      2   3
         / \
        4   5

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

### 1. Preorder DFS Traversal with Null Sentinels (Optimal & Cleanest)
In a standard binary tree traversal (preorder, inorder, or postorder), knowing just one traversal is insufficient to reconstruct the unique tree structure without additional constraints (e.g., BST property or having both preorder and inorder).

However, **recording explicit null pointers (`#`)** removes all ambiguity:
- Every node has exactly two children recorded.
- Preorder sequence: `Root -> Left Subtree -> Right Subtree`.
- The first element of any subtree in preorder is unambiguously the root of that subtree.

### 2. Implementation Mechanics
1. **Serialization (`serialize`)**:
   - Traverse the tree recursively in preorder.
   - If `root == nullptr`, append `"# "` to the string stream.
   - Otherwise, append `to_string(root->val) + " "` and recurse on `root->left` then `root->right`.
2. **Deserialization (`deserialize`)**:
   - Wrap the serialized string in `istringstream in(data)`.
   - Read the next token:
     - If the token is `"#"` or stream is exhausted, return `nullptr`.
     - Otherwise, construct `TreeNode* root = new TreeNode(stoi(token))`.
     - Recursively assign `root->left = deserializeHelper(in)` and `root->right = deserializeHelper(in)`.
     - Return `root`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - **Serialize**: Visits each of the $N$ nodes (and $N+1$ null leaves) exactly once in $\mathcal{O}(1)$ work per node $\implies \mathcal{O}(N)$.
  - **Deserialize**: Parses $2N + 1$ tokens, constructing each node in $\mathcal{O}(1)$ time $\implies \mathcal{O}(N)$.
- **Space Complexity:** $\mathcal{O}(N)$
  - **Recursion Stack**: $\mathcal{O}(H)$ where $H$ is the tree height ($\mathcal{O}(\log N)$ balanced, $\mathcal{O}(N)$ skewed).
  - **Serialized String**: Contains $2N + 1$ tokens $\implies \mathcal{O}(N)$.

---

## 🔍 Edge Cases Considered

- **Empty Tree (`root = nullptr`)**: Serializes to `"# "`, deserializes directly to `nullptr`.
- **Single Node Tree**: Serializes to `"val # # "`, correctly reconstructed as leaf node.
- **Skewed Trees (Line Trees)**: Correctly tracks left/right orientation through explicit `#` tokens without recursion depth stack overflow.
- **Negative Values**: `stoi` automatically parses negative numbers (e.g., `"-1000"`).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
