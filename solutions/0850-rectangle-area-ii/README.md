# [850. Rectangle Area II](https://leetcode.com/problems/rectangle-area-ii/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), Line Sweep, Segment Tree

---

## 📌 Problem Statement

You are given a 2D array of axis-aligned rectangles. Each `rectangle[i] = [xi1, yi1, xi2, yi2]` denotes the $i$th rectangle where `(xi1, yi1)` are the coordinates of the bottom-left corner, and `(xi2, yi2)` are the coordinates of the top-right corner.

Calculate the total area covered by all rectangles in the plane. Any area covered by two or more rectangles should only be counted once.

Return the total area. Since the answer may be too large, return it modulo `10^9 + 7`.

### Example 1:
```
Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
Output: 6
Explanation: A total area of 6 is covered by all three rectangles.
```

### Example 2:
```
Input: rectangles = [[0,0,1000000000,1000000000]]
Output: 49
Explanation: The answer is 10^18 modulo (10^9 + 7), which is 49.
```

### Constraints:
- `1 <= rectangles.length <= 200`
- `rectanges[i].length == 4`
- `0 <= xi1, yi1, xi2, yi2 <= 10^9`
- `xi1 <= xi2`
- `yi1 <= yi2`
- All rectangles have non zero area.

---

## 💡 Intuition & Approach

The coordinate constraints ($0 \le X, Y \le 10^9$) are too massive to use a grid counting approach. However, there are at most $200$ rectangles. This is a classic setup for the **Line Sweep** algorithm.

Imagine a vertical line scanning the 2D plane from left to right.
1. Every rectangle spans horizontally from `x1` to `x2`, and vertically from `y1` to `y2`.
2. We break every rectangle into two "events": 
   - An **Enter Event** at `x = x1` that says "start counting the interval `[y1, y2]`".
   - A **Leave Event** at `x = x2` that says "stop counting the interval `[y1, y2]`".
3. We collect all $2N$ events and sort them purely by their $X$-coordinate.
4. As we process these sorted events chronologically, we maintain an array of "Active Y-intervals".
5. Between any two distinct $X$-coordinates (`prev_x` and `curr_x`), the active $Y$-intervals are completely constant. The area added in this vertical strip is simply `(curr_x - prev_x) * total_active_y_length`.
6. To compute `total_active_y_length`, we can simply sort the active intervals and merge overlapping ones, summing up their unified lengths (similar to the standard Merge Intervals problem).
7. After calculating the area for the strip, we update our active $Y$-intervals based on the current event (inserting if it's an Enter event, erasing if it's a Leave event).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2 \log N)$ — There are $2N$ events. At each event, we sort up to $N$ active intervals, which takes $\mathcal{O}(N \log N)$ time. Summed across $2N$ events, the worst-case runtime is bounded by $\mathcal{O}(N^2 \log N)$. For $N = 200$, this yields at most $\approx 300,000$ operations, well under the $10^7$ limit. (A more complex Segment Tree approach can optimize this to $\mathcal{O}(N \log N)$, but is overkill for $N=200$).
- **Space Complexity:** $\mathcal{O}(N)$ — We need memory to store $2N$ events and up to $N$ active intervals.

---

## 🔍 Edge Cases Considered

- **Overlapping events at the same X:** If multiple rectangles begin or end exactly at the same $X$-coordinate, the computed horizontal width (`curr_x - prev_x`) naturally becomes $0$, correctly adding $0$ area and allowing the active states to fully settle before moving to the next non-zero width strip.
- **Large Area Values (Modulo Math):** The area increment `width * active_y` can peak at $10^9 \times 10^9 = 10^{18}$. This fits comfortably inside a standard 64-bit `long long` without overflowing before we apply the `% (10^9 + 7)` modulo operator.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
