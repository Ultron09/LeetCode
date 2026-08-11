# [352. Data Stream as Disjoint Intervals](https://leetcode.com/problems/data-stream-as-disjoint-intervals/)

**Difficulty:** `Hard`  
**Topics:** [Intervals](../../topics/intervals.md), [Binary Search](../../topics/binary-search.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given a data stream input of non-negative integers $a_1, a_2, \dots, a_n$, summarize the numbers seen so far as a list of disjoint intervals.

Implement the `SummaryRanges` class:

- `SummaryRanges()` Initializes the object with an empty stream.
- `void addNum(int value)` Adds the integer `value` to the stream.
- `int[][] getIntervals()` Returns a summary of the integers in the stream currently as a list of disjoint intervals $[start_i, end_i]$. The answer should be sorted by $start_i$.

### Example 1:
```
Input
["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
[[], [1], [], [3], [], [7], [], [2], [], [6], []]
Output
[null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]

Explanation
SummaryRanges summaryRanges = new SummaryRanges();
summaryRanges.addNum(1);      // arr = [1]
summaryRanges.getIntervals(); // return [[1, 1]]
summaryRanges.addNum(3);      // arr = [1, 3]
summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
summaryRanges.addNum(7);      // arr = [1, 3, 7]
summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]
```

### Constraints:
- $0 \le \text{value} \le 10^4$
- At most $3 \times 10^4$ calls will be made to `addNum` and `getIntervals`.
- At most $10^2$ calls will be made to `getIntervals`.

### Follow-up:
*What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?*

---

## 💡 Intuition & Approach

### 1. Ordered Map of Disjoint Intervals
To maintain non-overlapping intervals dynamically:
- Store intervals in a balanced Binary Search Tree (`std::map<int, int>` in C++), mapping `start -> end`.
- When inserting a new integer `value`:
  1. Find the first interval starting strictly after `value` using `upper_bound(value)`: let this iterator be `it`.
  2. The candidate interval to the left is `prevIt = prev(it)` (if `it != intervals.begin()`).

### 2. The 4 Insertion & Merging Scenarios
1. **Already Contained**: If `prevIt != end && prevIt->second >= value`, then `value` is already inside an existing interval. Return immediately ($\mathcal{O}(\log K)$).
2. **Bridge Left and Right**: If `prevIt->second + 1 == value` AND `it != end && it->first == value + 1`:
   - `value` bridges the gap between `[prevIt->start, prevIt->end]` and `[it->start, it->end]`.
   - Update `prevIt->second = it->second` and delete `it`.
3. **Extend Left Interval**: If `prevIt->second + 1 == value`:
   - Extend the left interval: `prevIt->second = value`.
4. **Extend Right Interval**: If `it != end && it->first == value + 1`:
   - Create new interval starting at `value` with end `it->second`, and delete `it`.
5. **New Disjoint Interval**: If no adjacency exists:
   - Insert `[value, value]`.

### 3. Answering the Follow-up
- By storing only the $K$ disjoint intervals in an ordered Red-Black Tree, `addNum` executes in $\mathcal{O}(\log K)$ time.
- When there are frequent merges and $K \ll N$, memory footprint remains minimal ($\mathcal{O}(K)$) and insertion performance is near-instantaneous.

---

## ⚡ Complexity Analysis

- **Time Complexity:**
  - `addNum(val)`: $\mathcal{O}(\log K)$ where $K$ is the current number of disjoint intervals ($K \le \min(N, \text{MAX\_VAL})$).
  - `getIntervals()`: $\mathcal{O}(K)$ to iterate through the map in sorted order.
- **Space Complexity:** $\mathcal{O}(K)$
  - Storage for the $K$ disjoint intervals in the red-black tree.

---

## 🔍 Edge Cases Considered

- **Duplicate Values**: Early return if `prevIt->second >= value`.
- **Boundary Merges at Value 0**: Correctly handles $0$ without negative out-of-bounds pointer issues.
- **Single-Element Extensions vs Double-Bridging**: Distinct branch handling ensures no dangling or duplicate interval keys.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
