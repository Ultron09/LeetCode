# ⏱️ Intervals

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Interval Scheduling and Merging.

---

## 📖 1. Core Theory & Fundamentals

Interval problems deal with ranges $[start, end]$.
- **Core Technique**: Sorting by $start$ time or $end$ time to establish linear ordering, followed by a single sweep line pass $\mathcal{O}(N \log N)$.
- **Overlap Condition**: Two intervals $[A, B]$ and $[C, D]$ overlap if $\max(A, C) \le \min(B, D)$.

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Merge Overlapping Intervals
```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    // Sort by start time
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> merged;
    merged.push_back(intervals[0]);

    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] <= merged.back()[1]) {
            // Overlapping: expand end time
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    return merged;
}
```

### Pattern B: Insert Interval
```cpp
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> result;
    size_t i = 0, n = intervals.size();

    // 1. Add all intervals ending before newInterval starts
    while (i < n && intervals[i][1] < newInterval[0]) {
        result.push_back(intervals[i++]);
    }

    // 2. Merge all overlapping intervals with newInterval
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    result.push_back(newInterval);

    // 3. Add all remaining intervals starting after newInterval ends
    while (i < n) {
        result.push_back(intervals[i++]);
    }

    return result;
}
```

### Pattern C: Meeting Rooms II (Chronological Ordering / Min-Heap)
```cpp
#include <queue>

int minMeetingRooms(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    sort(intervals.begin(), intervals.end());

    // Min-heap to store meeting end times
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(intervals[0][1]);

    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] >= minHeap.top()) {
            minHeap.pop(); // Room freed
        }
        minHeap.push(intervals[i][1]);
    }
    return minHeap.size();
}
```

### Pattern D: Dynamic Gap Maintenance with Segment Tree & Balanced BST
When intervals/gaps are dynamically split by inserting obstacles and queried for maximum gap sizes in a prefix $[0, x]$:
1. Maintain obstacle positions in an ordered set (`std::set<int>`).
2. Maintain the preceding gap $p - \text{prev}(p)$ for each obstacle $p$ in a Point-Update Range-Maximum Segment Tree.
3. On obstacle insertion at $x$: update gap at $x$ ($x - prev$) and gap at next obstacle ($next - x$).
4. On query $[0, x]$: find largest obstacle $p \le x$; maximum gap is $\max(\text{SegmentTree.query}(0, p), x - p)$.

### Pattern E: Dynamic Disjoint Interval Maintenance via Ordered Map
When dynamically inserting values into a stream and maintaining disjoint continuous intervals $[L, R]$:
1. **Ordered Map Invariant**: Store intervals in `std::map<int, int>` mapping `start -> end`.
2. **Neighbor Lookups via `upper_bound`**: For a new value $x$, find `it = upper_bound(x)` and `prevIt = prev(it)`.
3. **Four Merge Invariants**:
   - **Contained**: If `prevIt->second >= x`, $x$ is already covered.
   - **Bridge Left & Right**: If `prevIt->second + 1 == x` and `it->first == x + 1`, update `prevIt->second = it->second` and erase `it`.
   - **Extend Left**: If `prevIt->second + 1 == x`, set `prevIt->second = x`.
   - **Extend Right**: If `it->first == x + 1`, replace `it` with $[x, it->second]$.
   - **New Interval**: Insert $[x, x]$.
4. **Complexity**: $\mathcal{O}(\log K)$ insertion and $\mathcal{O}(K)$ retrieval, where $K$ is the number of disjoint intervals ($K \ll N$).

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Inclusive vs Exclusive Endpoints**: Pay attention to whether $[1, 2]$ and $[2, 3]$ count as overlapping (e.g. `start <= prevEnd` vs `start < prevEnd`).
2. **Unsorted Inputs**: Never assume intervals are pre-sorted unless guaranteed by constraints.
3. **Empty Input**: Always check `intervals.empty()`.
4. **Partial Prefix Interval**: In dynamic gap queries up to $x$, don't forget the partial gap between the last obstacle $p \le x$ and $x$ ($x - p$).
5. **Iterator Invalidation on Erase**: In `std::map`, save the iterator's required values before calling `erase()`.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 352 | [Data Stream as Disjoint Intervals](../solutions/0352-data-stream-as-disjoint-intervals/README.md) | `Hard` | $\mathcal{O}(\log K) \text{ add}, \mathcal{O}(K) \text{ get}$ | $\mathcal{O}(K)$ | [C++](../solutions/0352-data-stream-as-disjoint-intervals/solution.cpp) |
| 3161 | [Block Placement Queries](../solutions/3161-block-placement-queries/README.md) | `Hard` | $\mathcal{O}(Q \log M)$ | $\mathcal{O}(M)$ | [C++](../solutions/3161-block-placement-queries/solution.cpp) |

