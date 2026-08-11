# [381. Insert Delete GetRandom O(1) - Duplicates allowed](https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Implement the `RandomizedCollection` class (a multiset) supporting:

- `bool insert(int val)` — Inserts `val` even if already present. Returns `true` if the item was not present, `false` otherwise.
- `bool remove(int val)` — Removes one occurrence of `val` if present. Returns `true` if the item was present, `false` otherwise.
- `int getRandom()` — Returns a random element with probability proportional to its count.

Each function must work in **average $\mathcal{O}(1)$** time complexity.

### Example 1:
```
Input
["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", "getRandom"]
[[], [1], [1], [2], [], [1], []]
Output
[null, true, false, true, 2, true, 1]

Explanation
insert(1)   → true  (new). Collection: [1]
insert(1)   → false (dup). Collection: [1,1]
insert(2)   → true  (new). Collection: [1,1,2]
getRandom() → 2 (prob 1/3) or 1 (prob 2/3)
remove(1)   → true.        Collection: [1,2]
getRandom() → 1 or 2 (equal probability)
```

### Constraints:
- $-2^{31} \le \text{val} \le 2^{31} - 1$
- At most $2 \times 10^5$ total calls to `insert`, `remove`, and `getRandom`.
- `getRandom` is only called when at least one element exists.

---

## 💡 Intuition & Approach

### 1. Dense Array + Hash Map of Index Sets
The core challenge is achieving $\mathcal{O}(1)$ removal with duplicates while maintaining uniform random sampling:

| Component | Purpose |
|---|---|
| `vector<int> nums` | Dense contiguous storage for $\mathcal{O}(1)$ random access via `nums[rand() % size]` |
| `unordered_map<int, unordered_set<int>> valToIdx` | Maps each value to its set of indices in `nums`, enabling $\mathcal{O}(1)$ lookup and removal |

### 2. Swap-and-Pop Removal with Index Bookkeeping
To remove `val` at index `removeIdx`:
1. Get any index of `val`: `removeIdx = *valToIdx[val].begin()`.
2. Let `lastVal = nums.back()` at `lastIdx = nums.size() - 1`.
3. Overwrite: `nums[removeIdx] = lastVal`.
4. Update index sets:
   - Remove `removeIdx` from `valToIdx[val]`.
   - Remove `lastIdx` from `valToIdx[lastVal]`.
   - If `removeIdx != lastIdx`, add `removeIdx` to `valToIdx[lastVal]`.
5. Pop back from `nums`.

### 3. Critical Edge Case: Removing the Last Element
When `removeIdx == lastIdx` (the element to remove IS the last element), we must **not** re-insert `removeIdx` into `valToIdx[lastVal]` after erasing it, since that index is about to be popped. The guard `if (removeIdx != lastIdx)` handles this.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(1)$ average for all three operations.
  - `insert`: Amortized $\mathcal{O}(1)$ vector push + $\mathcal{O}(1)$ hash set insert.
  - `remove`: $\mathcal{O}(1)$ hash lookups + swap + pop.
  - `getRandom`: $\mathcal{O}(1)$ array index.
- **Space Complexity:** $\mathcal{O}(N)$
  - `nums` stores all $N$ elements; `valToIdx` stores all $N$ indices across all sets.

---

## 🔍 Edge Cases Considered

- **Self-Swap on Remove**: When the element to remove is already the last element, the guard prevents index corruption.
- **All Duplicates**: Multiple copies of the same value each occupy distinct indices in the set.
- **Remove Until Empty**: Index sets become empty and subsequent `remove` calls return `false`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
