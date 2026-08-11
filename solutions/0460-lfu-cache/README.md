# [460. LFU Cache](https://leetcode.com/problems/lfu-cache/)

**Difficulty:** `Hard`  
**Topics:** [Linked List](../../topics/linked-list.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Design and implement a data structure for a **Least Frequently Used (LFU)** cache.

Implement the `LFUCache` class:

- `LFUCache(int capacity)` Initializes the object with the `capacity` of the data structure.
- `int get(int key)` Gets the value of the `key` if the `key` exists in the cache. Otherwise, returns `-1`.
- `void put(int key, int value)` Update the value of the `key` if present, or inserts the `key` if not already present. When the cache reaches its `capacity`, it should invalidate and remove the **least frequently used** key before inserting a new item. For this problem, when there is a **tie** (i.e., two or more keys with the same frequency), the **least recently used** key would be invalidated.

To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to $1$ (due to the `put` operation). The use counter for a key in the cache is incremented whenever a `get` or `put` operation is called on it.

The functions `get` and `put` must each run in $\mathcal{O}(1)$ average time complexity.

### Example 1:
```
Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]

Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

Explanation
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // return 1; cnt(1)=2, cache=[1,2]
lfu.put(3, 3);   // cnt(2)=1 is smallest, invalidate 2. cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3; cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // Both 1 and 3 have cnt=2, 1 is LRU, invalidate 1. cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3; cnt(3)=3, cnt(4)=1
lfu.get(4);      // return 4; cnt(4)=2, cnt(3)=3
```

### Constraints:
- $1 \le \text{capacity} \le 10^4$
- $0 \le \text{key} \le 10^5$
- $0 \le \text{value} \le 10^9$
- At most $2 \times 10^5$ calls will be made to `get` and `put`.

---

## 💡 Intuition & Approach

### 1. Dual Invariants: Frequency Ordering & LRU Tie-Breaking
A standard LRU cache uses a single doubly-linked list. An LFU cache requires two levels of ordering:
1. **Primary Ordering**: Keys with smaller use counts must be evicted first.
2. **Secondary Ordering (Tie-Breaking)**: Keys with the same use count must be ordered by recency of access (LRU).

To achieve $\mathcal{O}(1)$ time for both criteria:
- Group keys of the same frequency into independent doubly-linked lists (`std::list<int>`).
- In each frequency list, insert newly touched/added keys at the **front** (MRU) and evict from the **back** (LRU).
- Maintain an integer `minFreq` storing the minimum frequency among all currently active keys.

```
freq = 1: [front: key4] <-> [back: key4]
freq = 2: [front: key3] <-> [back: key3]
minFreq = 1
```

### 2. State & Maps Architecture
- `keyToValFreq`: `unordered_map<int, pair<int, int>>` $(key \to \{value, freq\})$.
- `freqToList`: `unordered_map<int, list<int>>` $(freq \to \text{doubly-linked list of keys})$.
- `keyToIter`: `unordered_map<int, list<int>::iterator>` $(key \to \text{iterator in } freqToList[freq])$.

### 3. Step-by-Step Operations

#### `touch(key)`:
1. Extract `freq = keyToValFreq[key].second`.
2. Erase `keyToIter[key]` from `freqToList[freq]`.
3. If `freqToList[freq]` becomes empty:
   - Erase the list from `freqToList`.
   - If `minFreq == freq`, increment `minFreq++` (since all keys with frequency `freq` have moved to `freq + 1`).
4. Increment frequency: $newFreq = freq + 1$.
5. Push `key` to the front of `freqToList[newFreq]`.
6. Update `keyToIter[key] = freqToList[newFreq].begin()`.

#### `get(key)`:
- If `key` not found, return `-1`.
- Call `touch(key)` and return `keyToValFreq[key].first`.

#### `put(key, value)`:
- If `capacity <= 0`, return immediately.
- If `key` exists: Update value, call `touch(key)`, return.
- If full capacity:
  - Identify LRU key at minimum frequency: `evictKey = freqToList[minFreq].back()`.
  - Pop `evictKey` from `freqToList[minFreq]`, erase from `keyToIter` and `keyToValFreq`.
- Insert new entry with $freq = 1$:
  - Add to `keyToValFreq` and `keyToIter`.
  - Push to front of `freqToList[1]`.
  - Reset `minFreq = 1`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(1)$ average for both `get` and `put`
  - All hash map lookups, doubly-linked list insertions, and node erasures take $\mathcal{O}(1)$ time.
  - Advancing `minFreq` during `touch()` or resetting `minFreq = 1` during `put()` takes $\mathcal{O}(1)$ time.
- **Space Complexity:** $\mathcal{O}(\text{capacity})$
  - Storing at most `capacity` items across `keyToValFreq`, `keyToIter`, and `freqToList`.

---

## 🔍 Edge Cases Considered

- **$\text{capacity} = 0$ / $\text{capacity} = 1$**: Handled gracefully.
- **`minFreq` Maintenance**: Increments only when the last key in `freqToList[minFreq]` moves up to `minFreq + 1`.
- **Existing Key Value Overwrite**: Updates the value and increments frequency without triggering eviction.
- **Tied Minimum Frequencies**: `freqToList[minFreq].back()` strictly extracts the oldest (least recently used) candidate.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
