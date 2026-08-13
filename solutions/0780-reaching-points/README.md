# [780. Reaching Points](https://leetcode.com/problems/reaching-points/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

Given four integers `sx`, `sy`, `tx`, and `ty`, return `true` if it is possible to convert the point `(sx, sy)` to the point `(tx, ty)` through some operations, or `false` otherwise.

The allowed operation on some point `(x, y)` is to convert it to either `(x, x + y)` or `(x + y, y)`.

### Example 1:
```
Input: sx = 1, sy = 1, tx = 3, ty = 5
Output: true
Explanation:
One series of moves that transforms the starting point to the target is:
(1, 1) -> (1, 2)
(1, 2) -> (3, 2)
(3, 2) -> (3, 5)
```

### Example 2:
```
Input: sx = 1, sy = 1, tx = 2, ty = 2
Output: false
```

### Constraints:
- `1 <= sx, sy, tx, ty <= 10^9`

---

## 💡 Intuition & Approach

Working forwards from `(sx, sy)` creates a massive binary tree of possibilities because at every step we can choose to branch into `(x, x+y)` or `(x+y, y)`. Since coordinates can go up to $10^9$, searching this tree forward would lead to a Time Limit Exceeded (TLE) or Memory Limit Exceeded (MLE) error.

Instead, we **work backwards**. 
If we look at any target state `(tx, ty)`, because $x$ and $y$ are strictly positive (constrained to $\ge 1$), there is only **one** deterministic way to step backwards:
- If `tx > ty`, the previous point MUST have been `(tx - ty, ty)`.
- If `ty > tx`, the previous point MUST have been `(tx, ty - tx)`.
- If `tx == ty`, we can't step back because coordinates must be positive (the previous point would involve a `0`).

### Optimization with Modulo
Simply subtracting the smaller value from the larger one can still result in TLE if one coordinate is much larger than the other (e.g., `(1, 1) -> (10^9, 1)` would take $10^9$ subtraction steps). 
Instead of repeated subtraction, we can use the modulo operator `%` to fast-forward the subtractions, mirroring the Euclidean algorithm.

**Algorithm:**
1. While `tx >= sx` and `ty >= sy`:
   - If we have reached `(sx, sy)`, return `true`.
   - If `tx > ty`:
     - If `ty > sy`, we can fast-forward: `tx %= ty`.
     - If `ty == sy`, we just need to check if `tx` can reach `sx` by subtracting `ty`. Since `ty` won't change anymore, we return `(tx - sx) % ty == 0`.
   - If `ty > tx`:
     - If `tx > sx`, we can fast-forward: `ty %= tx`.
     - If `tx == sx`, we just check if `(ty - sy) % tx == 0`.
   - If `tx == ty`:
     - Unless they match `(sx, sy)` exactly (handled at the start of the loop), this is a dead end. Break out of the loop.
2. Return `false` if the loop terminates without finding a match.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\log(\max(tx, ty)))$ — Because the operation structurally mirrors the Euclidean algorithm for greatest common divisor (GCD), the values decrease logarithmically.
- **Space Complexity:** $\mathcal{O}(1)$ — Only constant extra space is used for loop variables.

---

## 🔍 Edge Cases Considered

- **Fast-forward via Modulo**: Handled effectively. A test case like `(1, 1) -> (1000000000, 1)` executes in $\mathcal{O}(1)$ time using the `(tx - sx) % ty == 0` bypass.
- **Target Smaller Than Start**: If `tx < sx` or `ty < sy`, the `while` loop condition naturally fails and the algorithm correctly returns `false`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
