# [25. Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/)

**Difficulty:** `Hard`  
**Topics:** [Linked List](../../topics/linked-list.md), [Recursion](../../topics/dynamic-programming.md), [Two Pointers](../../topics/two-pointers.md)

---

## 📌 Problem Statement

Given the `head` of a linked list, reverse the nodes of the list `k` at a time, and return the modified list.

`k` is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of `k` then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

### Example 1:
```
Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]
```

### Example 2:
```
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
```

### Constraints:
- The number of nodes in the list is `n`.
- $1 \le k \le n \le 5000$
- $0 \le \text{Node.val} \le 1000$

---

## 💡 Intuition & Approach

### 1. In-Place Reversal with Constant Extra Memory
- Maintain a `dummy` node pointing to `head` and a pointer `groupPrev` initially set to `&dummy`.
- For each group:
  1. Advance $k$ steps from `groupPrev` to find the $k$-th node `kth`.
  2. If fewer than $k$ nodes remain (`kth == nullptr`), terminate the loop without modifying remaining nodes.
  3. Store `groupNext = kth->next`.
  4. Perform standard pointer reversal for nodes between `groupPrev->next` and `groupNext`, setting initial `prev = groupNext`.
  5. Connect `groupPrev->next = kth`, and advance `groupPrev` to the tail of the newly reversed group.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - Each node is traversed at most twice (once for length probing and once for pointer reversal).
  - Runtime $\approx 1$ ms in C++.
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space (modifies pointers entirely in-place).

---

## 🔍 Edge Cases Considered

- **$k = 1$ or single element list**: Handled immediately without unnecessary reversals.
- **List length is an exact multiple of $k$**: Fully reversed with clean termination on the final `nullptr`.
- **List length is not a multiple of $k$**: Trailing $(n \bmod k)$ nodes remain in their original order.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
