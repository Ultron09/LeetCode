# 🔗 Linked List

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Singly and Doubly Linked Lists.

---

## 📖 1. Core Theory & Fundamentals

A Linked List is a linear collection of data elements whose order is not given by their physical placement in memory. Instead, each element points to the next.

### Key Characteristics
- **Dynamic Size**: Easy insertion/deletion without resizing or shifting.
- **Sequential Access**: $\mathcal{O}(N)$ access time (no $\mathcal{O}(1)$ random indexing).
- **Extra Overhead**: Requires storage for pointers (`next`, `prev`).

### Standard Node Structure
```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
```

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Dummy Head Technique
Eliminates special-case handling for the head node when inserting, deleting, or merging lists.
```cpp
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy(0);
    ListNode* current = &dummy;

    while (list1 && list2) {
        if (list1->val <= list2->val) {
            current->next = list1;
            list1 = list1->next;
        } else {
            current->next = list2;
            list2 = list2->next;
        }
        current = current->next;
    }
    current->next = list1 ? list1 : list2;
    return dummy.next;
}
```

### Pattern B: In-Place Linked List Reversal
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr != nullptr) {
        ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev; // New head
}
```

### Pattern C: Fast & Slow Pointers (Floyd's Tortoise and Hare)
Used for cycle detection, finding the middle element, and finding the cycle entry point.
```cpp
// Detect cycle entry point
ListNode *detectCycle(ListNode *head) {
    if (!head || !head->next) return nullptr;

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // Cycle detected: locate the start node
            ListNode* ptr1 = head;
            ListNode* ptr2 = slow;
            while (ptr1 != ptr2) {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
            return ptr1;
        }
    }
    return nullptr; // No cycle
}
```

### Pattern D: Merge K Sorted Lists (Min-Heap / Divide and Conquer)
```cpp
struct Compare {
    bool operator()(const ListNode* a, const ListNode* b) const {
        return a->val > b->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, Compare> minHeap;
    for (ListNode* head : lists) {
        if (head) minHeap.push(head);
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();
        tail->next = node;
        tail = tail->next;
        if (node->next) minHeap.push(node->next);
    }
    return dummy.next;
}
### Pattern E: In-Place k-Group Reversal
```cpp
ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || k <= 1) return head;
    ListNode dummy(0);
    dummy.next = head;
    ListNode* groupPrev = &dummy;

    auto getKth = [](ListNode* curr, int k) {
        while (curr && k > 0) {
            curr = curr->next;
            k--;
        }
        return curr;
    };

    while (true) {
        ListNode* kth = getKth(groupPrev, k);
        if (!kth) break;
        ListNode* groupNext = kth->next;

        // In-place group reversal
        ListNode* prev = groupNext;
        ListNode* curr = groupPrev->next;
        while (curr != groupNext) {
            ListNode* tmp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = tmp;
        }

        ListNode* newGroupEnd = groupPrev->next;
        groupPrev->next = kth;
        groupPrev = newGroupEnd;
    }
    return dummy.next;
}
```

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Null Pointer Dereference**: Always verify `node != nullptr` and `node->next != nullptr` before accessing `node->next->val`.
2. **Losing Pointer References**: When modifying links, save `curr->next` in a temporary variable before reassigning.
3. **Memory Leaks in C++**: In local test runners or production code, remember to deallocate dynamically allocated nodes or use smart pointers (`std::unique_ptr`).

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 23 | [Merge k Sorted Lists](../solutions/0023-merge-k-sorted-lists/README.md) | `Hard` | $\mathcal{O}(N \log K)$ | $\mathcal{O}(K)$ | [C++](../solutions/0023-merge-k-sorted-lists/solution.cpp) |
| 25 | [Reverse Nodes in k-Group](../solutions/0025-reverse-nodes-in-k-group/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0025-reverse-nodes-in-k-group/solution.cpp) |


