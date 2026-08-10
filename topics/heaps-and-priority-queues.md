# ⛰️ Heaps & Priority Queues

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Heaps and Priority Queues.

---

## 📖 1. Core Theory & Fundamentals

A Binary Heap is a complete binary tree satisfying the heap property:
- **Max-Heap**: Parent value $\ge$ children values. Root is the maximum.
- **Min-Heap**: Parent value $\le$ children values. Root is the minimum.

### Complexities
- Insertion (`push`): $\mathcal{O}(\log N)$ via heapify up (sift up).
- Extraction (`pop`): $\mathcal{O}(\log N)$ via heapify down (sift down).
- Peek Top (`top`): $\mathcal{O}(1)$.
- Building Heap from Array (`std::make_heap`): $\mathcal{O}(N)$.

### C++ Standard Library
- `std::priority_queue<T>`: Defaults to **Max-Heap**.
- `std::priority_queue<T, vector<T>, greater<T>>`: **Min-Heap**.
- Custom comparator with structs or lambda expressions.

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Top-K Frequent Elements / Kth Largest
Maintain a min-heap of size $K$ to find the $K$ largest elements in $\mathcal{O}(N \log K)$ time.
```cpp
#include <queue>

// Kth Largest Element in an Array
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int num : nums) {
        minHeap.push(num);
        if (static_cast<int>(minHeap.size()) > k) {
            minHeap.pop(); // Remove smallest element
        }
    }
    return minHeap.top();
}
```

### Pattern B: Two Heaps (Find Median from Data Stream)
```cpp
class MedianFinder {
private:
    priority_queue<int> maxHeap; // Lower half
    priority_queue<int, vector<int>, greater<int>> minHeap; // Upper half

public:
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();

        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};
```

### Pattern C: Merge K Sorted Lists
```cpp
struct Compare {
    bool operator()(const ListNode* a, const ListNode* b) {
        return a->val > b->val; // Min-heap
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
    for (ListNode* head : lists) {
        if (head) pq.push(head);
    }

    ListNode dummy(0);
    ListNode* curr = &dummy;

    while (!pq.empty()) {
        ListNode* smallest = pq.top();
        pq.pop();
        curr->next = smallest;
        curr = curr->next;
        if (smallest->next) pq.push(smallest->next);
    }
    return dummy.next;
}
```

### Pattern D: K-Way Top Element Extraction on Monotonic Intervals via RMQ Heap
When extracting top-K elements across multidimensional structures with monotonic properties (e.g. subarray range differences):
1. Precompute $\mathcal{O}(1)$ Range Queries (Sparse Table for min/max).
2. Exploit monotonicity: for fixed $l$, $V(l, r)$ is non-decreasing with $r \implies$ optimal right bound starts at $r = n - 1$.
3. Seed Max-Heap with $(V(l, n - 1), l, n - 1)$ for all $l \in [0, n - 1]$.
4. Greedily pop top element, accumulate, and push $(V(l, r - 1), l, r - 1)$ in $\mathcal{O}(\log N)$.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Min-Heap Comparator Inversion**: In `std::priority_queue`, `std::greater<T>` produces a **min-heap** (contrary to `std::sort` where `greater` produces descending order).
2. **Empty Heap Access**: Calling `.top()` or `.pop()` on an empty `priority_queue` causes undefined behavior / crash.
3. **Floating Point Division in Median**: Always cast sums to `double` before dividing by `2.0`.
4. **Total Sum Overflow**: Summing $K$ values each up to $10^9$ requires `long long` for accumulators.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 23 | [Merge k Sorted Lists](../solutions/0023-merge-k-sorted-lists/README.md) | `Hard` | $\mathcal{O}(N \log K)$ | $\mathcal{O}(K)$ | [C++](../solutions/0023-merge-k-sorted-lists/solution.cpp) |
| 3691 | [Maximum Total Subarray Value II](../solutions/3691-maximum-total-subarray-value-ii/README.md) | `Hard` | $\mathcal{O}((N + K) \log N)$ | $\mathcal{O}(N \log N)$ | [C++](../solutions/3691-maximum-total-subarray-value-ii/solution.cpp) |


