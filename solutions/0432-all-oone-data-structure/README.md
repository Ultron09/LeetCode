# [432. All O`one Data Structure](https://leetcode.com/problems/all-oone-data-structure/)

**Difficulty:** `Hard`  
**Topics:** [Linked List](../../topics/linked-list.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Design a data structure to store the strings' count with the ability to return the strings with minimum and maximum counts.

Implement the `AllOne` class:

- `AllOne()` Initializes the object of the data structure.
- `inc(String key)` Increments the count of the string `key` by $1$. If `key` does not exist in the data structure, insert it with count $1$.
- `dec(String key)` Decrements the count of the string `key` by $1$. If the count of `key` is $0$ after the decrement, remove it from the data structure. It is guaranteed that `key` exists in the data structure before the decrement.
- `getMaxKey()` Returns one of the keys with the maximal count. If no element exists, return an empty string `""`.
- `getMinKey()` Returns one of the keys with the minimum count. If no element exists, return an empty string `""`.

**Note:** Each function must run in $\mathcal{O}(1)$ average time complexity.

### Example 1:
```
Input
["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
[[], ["hello"], ["hello"], [], [], ["leet"], [], []]

Output
[null, null, null, "hello", "hello", null, "hello", "leet"]

Explanation
AllOne allOne = new AllOne();
allOne.inc("hello");
allOne.inc("hello");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "hello"
allOne.inc("leet");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "leet"
```

### Constraints:
- $1 \le \text{key.length} \le 10$
- `key` consists of lowercase English letters.
- It is guaranteed that for each call to `dec`, `key` is existing in the data structure.
- At most $5 \times 10^4$ calls will be made to `inc`, `dec`, `getMaxKey`, and `getMinKey`.

---

## 💡 Intuition & Approach

### 1. The Challenge of $\mathcal{O}(1)$ Min & Max Tracking
A simple hash map tracking counts cannot find the minimum or maximum key in $\mathcal{O}(1)$ time. A heap or balanced binary search tree supports min/max queries in $\mathcal{O}(1)$ or $\mathcal{O}(\log N)$, but update operations (`inc`/`dec`) take $\mathcal{O}(\log N)$.

To achieve strict $\mathcal{O}(1)$ average time for **all** four operations:
- Group keys that share the same frequency into **Buckets**.
- Maintain the Buckets in a **Doubly-Linked List** sorted by frequency in strictly ascending order.
- Maintain an `unordered_map<string, list<Bucket>::iterator>` mapping each key directly to the bucket node containing it.

### 2. Data Structure Layout
```
[head] <-> [Bucket: count=1, keys={b, c}] <-> [Bucket: count=2, keys={a}] <-> [tail]
              ^ (Min Key: buckets.front())         ^ (Max Key: buckets.back())
```
- Each `Bucket` holds:
  - `int count`: the common frequency count.
  - `unordered_set<string> keys`: the set of keys with this count.
- Because `inc` changes a key's count from $C \to C + 1$, the key simply moves to the immediately adjacent next bucket (creating one if it does not exist).
- Because `dec` changes a key's count from $C \to C - 1$, the key moves to the immediately adjacent previous bucket (or is deleted if $C = 1$).
- When a bucket's `keys` set becomes empty, it is spliced out of the doubly linked list in $\mathcal{O}(1)$ time.

### 3. Operations Breakdown
- `inc(key)`:
  - If `key` is new: Add to bucket with `count = 1` at the front of the list.
  - If `key` exists at bucket `it`: Check if `next(it)` has `count == it->count + 1`. If not, insert a new bucket immediately after `it`. Move `key` from `it` to `next(it)`. Erase `it` if empty.
- `dec(key)`:
  - If `it->count == 1`: Remove `key` from `it->keys` and erase from map.
  - If `it->count > 1`: Check if `prev(it)` has `count == it->count - 1`. If not, insert a new bucket immediately before `it`. Move `key` from `it` to `prev(it)`. Erase `it` if empty.
- `getMaxKey()`: If list is empty return `""`, else return `*(buckets.back().keys.begin())`.
- `getMinKey()`: If list is empty return `""`, else return `*(buckets.front().keys.begin())`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(1)$ average for all methods
  - `inc(key)`: Hash map lookup + hash set insertion/deletion + doubly-linked list node insertion $\implies \mathcal{O}(1)$.
  - `dec(key)`: Hash map lookup + hash set insertion/deletion + doubly-linked list node removal $\implies \mathcal{O}(1)$.
  - `getMaxKey()`: Accessing `buckets.back().keys.begin()` $\implies \mathcal{O}(1)$.
  - `getMinKey()`: Accessing `buckets.front().keys.begin()` $\implies \mathcal{O}(1)$.
- **Space Complexity:** $\mathcal{O}(N)$
  - Storing $N$ unique keys across the hash map and the bucket sets. The doubly linked list contains at most $\min(N, \sqrt{\text{total increments}})$ distinct frequency bucket nodes.

---

## 🔍 Edge Cases Considered

- **Empty Structure**: `getMaxKey()` and `getMinKey()` safely return `""`.
- **Count Reduced to 0**: Key is completely erased from both bucket and hash map.
- **Empty Bucket Pruning**: Splicing out empty bucket nodes ensures that `buckets.front()` and `buckets.back()` always represent valid, non-empty min/max sets.
- **Multiple Keys in Same Bucket**: Correctly returns any valid key from the bucket.
- **Non-Existent Intermediary Bucket Creation**: Dynamically inserts and links new bucket nodes on demand without corrupting list order.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
