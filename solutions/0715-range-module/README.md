# [715. Range Module](https://leetcode.com/problems/range-module/)

**Difficulty:** `Hard`  
**Topics:** [Intervals](../../topics/intervals.md)

---

## 📌 Problem Statement

Design a data structure that tracks ranges represented as **half-open intervals** `[left, right)` and supports:

- **`addRange(left, right)`** — Track every real number in `[left, right)`.
- **`queryRange(left, right)`** — Return `true` if every real number in `[left, right)` is currently tracked.
- **`removeRange(left, right)`** — Stop tracking every real number in `[left, right)`.

### Example:
```
RangeModule rm = new RangeModule();
rm.addRange(10, 20);       // Tracked: [10, 20)
rm.removeRange(14, 16);    // Tracked: [10, 14) ∪ [16, 20)
rm.queryRange(10, 14);     // true  — [10, 14) fully tracked
rm.queryRange(13, 15);     // false — 14 is not tracked
rm.queryRange(16, 17);     // true  — [16, 17) ⊂ [16, 20)
```

### Constraints:
- `1 <= left < right <= 10^9`
- At most `10^4` calls to `addRange`, `queryRange`, and `removeRange`.

---

## 💡 Intuition & Approach

### 1. Data Structure: Ordered Map of Disjoint Intervals

Maintain a `std::map<int, int>` where each entry `{start → end}` represents a tracked half-open interval `[start, end)`. The map's sorted key ordering guarantees intervals are always in ascending order.

**Invariant:** All stored intervals are **disjoint** and **non-adjacent** (touching intervals get merged).

### 2. addRange(left, right)

1. Use `upper_bound(left)` to find the first interval with `start > left`.
2. Step back to check if the previous interval overlaps (its `end >= left`).
3. **Merge loop:** While the current interval's `start <= right`, it overlaps with `[left, right)`:
   - Expand `[left, right)` to encompass it: `left = min(left, it->start)`, `right = max(right, it->end)`.
   - Erase the old interval.
4. Insert the merged `[left, right)`.

```
Before: [10,14)  [16,20)  [25,30)
addRange(12, 18)
→ Merges [10,14) and [16,20) into [10,20)
After:  [10,20)  [25,30)
```

### 3. queryRange(left, right)

1. Use `upper_bound(left)` and step back one position.
2. If the found interval has `end >= right`, then `[left, right)` is fully contained → `true`.
3. Otherwise → `false`.

This is $\mathcal{O}(\log N)$ — just one binary search, no iteration.

### 4. removeRange(left, right)

1. Find overlapping intervals (same approach as `addRange`).
2. For each overlapping interval `[s, e)`:
   - Erase it.
   - If `s < left`, re-insert `[s, left)` (the portion before the removed range).
   - If `e > right`, re-insert `[right, e)` (the portion after the removed range).

```
Before: [10,20)
removeRange(14, 16)
→ Splits into [10,14) and [16,20)
After:  [10,14)  [16,20)
```

---

## ⚡ Complexity Analysis

| Operation | Time | Space |
|---|---|---|
| **addRange** | $\mathcal{O}(N)$ worst case | — |
| **queryRange** | $\mathcal{O}(\log N)$ | — |
| **removeRange** | $\mathcal{O}(N)$ worst case | — |
| **Overall** | $\mathcal{O}(N)$ per mutation | $\mathcal{O}(N)$ |

- $N$ = number of disjoint intervals currently stored.
- **Amortized analysis:** Each interval is inserted and erased at most once, so across $Q$ operations the total work is $\mathcal{O}(Q \log Q)$ amortized.
- `queryRange` is always $\mathcal{O}(\log N)$ — no iteration needed.

---

## 🔍 Edge Cases Considered

- **Overlapping add:** `addRange(10,20)` then `addRange(15,25)` → merges to `[10,25)`.
- **Adjacent intervals:** `addRange(10,15)` then `addRange(15,20)` → merges to `[10,20)` (touching at 15 counts as overlap since `15 <= right`).
- **Remove splits interval:** `addRange(1,100)` then `removeRange(40,60)` → `[1,40) ∪ [60,100)`.
- **Remove at boundaries:** `removeRange(1,100)` on `[1,100)` → empty.
- **Query on empty module:** Returns `false`.
- **Query partially tracked:** `[13,15)` spanning a gap → `false`.
- **Re-add after remove:** Correctly re-tracks the range.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
