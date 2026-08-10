# [23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)

**Difficulty:** `Hard`  
**Topics:** [Linked List](../../topics/linked-list.md), [Heaps / Priority Queue](../../topics/heaps-and-priority-queues.md), [Divide and Conquer](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an array of `k` linked-lists `lists`, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

### Example 1:
```
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted linked list:
1->1->2->3->4->4->5->6
```

### Example 2:
```
Input: lists = []
Output: []
```

### Example 3:
```
Input: lists = [[]]
Output: []
```

### Constraints:
- `k == lists.length`
- $0 \le k \le 10^4$
- $0 \le \text{lists}[i]\text{.length} \le 500$
- $-10^4 \le \text{lists}[i][j] \le 10^4$
- `lists[i]` is sorted in ascending order.
- Total sum of `lists[i].length` $\le 10^4$.

---

## 💡 Intuition & Approach

### 1. Min-Heap (Priority Queue) Method
- Insert the head node of each non-empty linked list into a Min-Heap of size at most $K$.
- Extract the smallest node `curr = minHeap.top()`, attach it to our merged list tail, and if `curr->next != nullptr`, push `curr->next` into the heap.
- Repeat until the heap is empty.

### 2. Divide and Conquer Method (Alternative)
- Pairwise merge lists using the standard 2-list merge subroutine until only 1 list remains: $\mathcal{O}(N \log K)$ time and $\mathcal{O}(1)$ auxiliary space.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log K)$
  - $N$ is the total number of nodes across all $K$ lists.
  - Each node is pushed and popped from the heap of size at most $K$ exactly once $\implies \mathcal{O}(N \log K)$.
- **Space Complexity:** $\mathcal{O}(K)$ auxiliary space for storing at most $K$ node pointers in the heap.

---

## 🔍 Edge Cases Considered

- **Empty input array `lists = []`**: Returns `nullptr`.
- **Lists containing null pointers `lists = [nullptr, nullptr]`**: Guarded during heap initialization.
- **Single list**: Directly processed and returned.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
