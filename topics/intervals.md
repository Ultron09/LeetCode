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

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Inclusive vs Exclusive Endpoints**: Pay attention to whether $[1, 2]$ and $[2, 3]$ count as overlapping (e.g. `start <= prevEnd` vs `start < prevEnd`).
2. **Unsorted Inputs**: Never assume intervals are pre-sorted unless guaranteed by constraints.
3. **Empty Input**: Always check `intervals.empty()`.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
<!-- Problems will be added here -->
