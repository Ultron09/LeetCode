# [732. My Calendar III](https://leetcode.com/problems/my-calendar-iii/)

**Difficulty:** `Hard`  
**Topics:** [Intervals](../../topics/intervals.md)

---

## 📌 Problem Statement

A **k-booking** happens when `k` events have some non-empty intersection (i.e., there is some time common to all `k` events).

Implement the `MyCalendarThree` class:

- `MyCalendarThree()` — Initializes the object.
- `int book(int startTime, int endTime)` — Returns the largest `k` such that there exists a k-booking in the calendar after adding the event `[startTime, endTime)`.

### Example 1:
```
Input:  ["MyCalendarThree", "book", "book", "book", "book", "book", "book"]
        [[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
Output: [null, 1, 1, 2, 3, 3, 3]
```

### Constraints:
- $0 \le \text{startTime} < \text{endTime} \le 10^9$
- At most 400 calls will be made to `book`.

---

## 💡 Intuition & Approach

### 1. Brute Force Idea — Pairwise Intersection Check

For each new booking, check all subsets of events for common intersection. This is exponential and infeasible.

### 2. Optimal Strategy — Sweep Line with Difference Map

The classic **sweep line** technique for maximum overlap:

1. For each booking `[start, end)`, record two events:
   - `+1` at `start` (an interval opens)
   - `-1` at `end` (an interval closes)

2. Store these deltas in an **ordered map** (`std::map<int, int>`).

3. After each `book()`, sweep through all event points in sorted order, maintaining a running sum. The **maximum running sum** at any point equals the maximum k-booking.

```
Timeline for the example:
  
  5: +1, +1       → active = 2, then 3
 10: +1, +1, -1   → active changes at boundary
 15: -1            → active decreases
 ...

After all 6 bookings:
  5: +2   → sweep: 2
 10: +2-1 → sweep: 2+1 = 3
 15: -1   → sweep: 3-1 = 2
 20: -1   → sweep: 2-1 = 1  (but more events pending)
 ...
 Maximum = 3 ✓
```

### 3. Why This Works

The half-open interval `[start, end)` means a booking is active at time `t` if `start ≤ t < end`. The difference map accumulates: at any sorted position, the prefix sum equals exactly the number of currently active bookings. The maximum prefix sum is the answer.

### 4. Why `std::map` and Not Array?

Time values range up to $10^9$, so a direct array is impossible. The ordered map stores only the ~800 distinct endpoints (at most 400 calls × 2 endpoints each), keeping the sweep compact.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ per `book()` call
  - Each call adds 2 entries and sweeps through all $\le 2N$ endpoints.
  - Total across $N$ calls: $\mathcal{O}(N^2)$.
  - With $N \le 400$, this is $\le 320{,}000$ operations — very fast.
- **Space Complexity:** $\mathcal{O}(N)$ — the difference map stores at most $2N$ entries.

---

## 🔍 Edge Cases Considered

- **Single booking** → always returns 1.
- **Fully overlapping identical intervals** (`[0,10)` × 4) → returns 4.
- **Non-overlapping intervals** (`[0,5)`, `[5,10)`, `[10,15)`) → always returns 1 (half-open means endpoints don't overlap).
- **Maximum coordinate values** ($10^9$) → handled by map (no array allocation).
- **Nested intervals** (`[0,100)`, `[10,90)`, `[20,80)`) → correctly counts the peak overlap.

---

## 🔗 Related Problems

- [729. My Calendar I](https://leetcode.com/problems/my-calendar-i/) — Double-booking prevention (simpler variant)
- [731. My Calendar II](https://leetcode.com/problems/my-calendar-ii/) — Triple-booking prevention
- [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/) — Same sweep line technique for minimum rooms

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
