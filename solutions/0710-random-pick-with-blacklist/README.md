# [710. Random Pick with Blacklist](https://leetcode.com/problems/random-pick-with-blacklist/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

You are given an integer `n` and an array of unique integers `blacklist`. Design an algorithm to pick a random integer in the range `[0, n - 1]` that is not in `blacklist`. Any integer that is in the mentioned range and not in `blacklist` should be **equally likely** to be returned.

Optimize your algorithm such that it minimizes the number of calls to the built-in random function.

### Example 1:
```
Input: n = 7, blacklist = [2, 3, 5]
Valid set: {0, 1, 4, 6} — each returned with probability 1/4

solution.pick(); // could return 0, 1, 4, or 6
```

### Constraints:
- `1 <= n <= 10^9`
- `0 <= blacklist.length <= min(10^5, n - 1)`
- `0 <= blacklist[i] < n`
- All values of `blacklist` are unique.
- At most `2 * 10^4` calls will be made to `pick`.

---

## 💡 Intuition & Approach

### 1. The Challenge

Naively, we could generate random numbers and reject blacklisted ones — but if the blacklist is large relative to $N$, rejection rates explode. We need **exactly one `rand()` call** per `pick()`.

### 2. Virtual Whitelist Remapping

Let $M = N - B$ where $B = |\text{blacklist}|$. There are exactly $M$ valid numbers.

**Key insight:** Partition `[0, N)` into two zones:

```
[0 ............. M-1]  [M ............. N-1]
   "whitelist zone"       "donor zone"
```

- In the **whitelist zone** `[0, M)`: most indices map to themselves. But some are blacklisted — these need remapping.
- In the **donor zone** `[M, N)`: some indices are valid (not blacklisted) — these become "donors" for remapping.

**Construction algorithm:**
1. Identify blacklisted numbers in the donor zone `[M, N)` — these are "consumed" and unavailable.
2. For each blacklisted number `b < M`, assign it the next available donor from `[M, N)`.
3. Store these remappings in a hash map.

**`pick()` algorithm:**
1. Generate `x = rand() % M`.
2. If `x` is in the remap table, return `remap[x]`.
3. Otherwise, `x` is already valid — return `x`.

### 3. Why This Works

Every valid number in `[0, N)` gets assigned to exactly one index in `[0, M)`:
- Valid numbers already in `[0, M)` map to themselves.
- Valid numbers in `[M, N)` are assigned as remap targets for blacklisted numbers in `[0, M)`.

Since `rand() % M` is uniform over `[0, M)`, each valid number is equally likely. ✓

### 4. Visual Walkthrough (n=7, blacklist=[2,3,5])

```
M = 7 - 3 = 4

Whitelist zone: [0, 1, 2, 3]   ← indices 2,3 are blacklisted
Donor zone:     [4, 5, 6]      ← index 5 is blacklisted

Available donors: 4, 6 (skip 5)

Remap:
  2 → 4  (first available donor)
  3 → 6  (next available donor)

pick() generates rand() % 4:
  0 → 0 (itself)
  1 → 1 (itself)
  2 → 4 (remapped)
  3 → 6 (remapped)

Uniform over {0, 1, 4, 6} ✓
```

---

## ⚡ Complexity Analysis

| Operation | Time | Space |
|---|---|---|
| **Constructor** | $\mathcal{O}(B)$ | $\mathcal{O}(B)$ |
| **pick()** | $\mathcal{O}(1)$ | — |

- $B = |\text{blacklist}|$ (at most $10^5$)
- Exactly **one** call to `rand()` per `pick()` — optimal.

---

## 🔍 Edge Cases Considered

- **Empty blacklist:** No remapping needed; `pick()` returns `rand() % N`.
- **All blacklisted numbers ≥ M:** No remapping needed; they're all in the donor zone.
- **All blacklisted numbers < M:** Every one needs a donor from `[M, N)`.
- **Single valid number:** `M = 1`, always returns the one valid number.
- **Large N (10⁹) with small blacklist:** Only stores $\mathcal{O}(B)$ entries, not $\mathcal{O}(N)$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
