# 📦 Arrays & Hashing

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Arrays, Hash Maps, Hash Sets, and Prefix Sums.

---

## 📖 1. Core Theory & Fundamentals

### Arrays & Contiguous Memory
- **Memory Layout**: Continuous block of memory. Cache-friendly with $\mathcal{O}(1)$ random access by index via pointer arithmetic: `address = base + index * sizeof(element)`.
- **Operations Complexity**:
  - Access: $\mathcal{O}(1)$
  - Search (Unsorted): $\mathcal{O}(N)$
  - Search (Sorted): $\mathcal{O}(\log N)$ via Binary Search
  - Insertion / Deletion at End: Amortized $\mathcal{O}(1)$ (`std::vector::push_back`)
  - Insertion / Deletion in Middle/Front: $\mathcal{O}(N)$ due to shifting elements

### Hash Maps & Hash Sets
- **Hash Table Principle**: Computes an integer hash value from a key using a hash function, mapping it to a bucket index (`hash(key) % capacity`).
- **Collision Resolution**:
  - **Chaining**: Linked list or vector per bucket.
  - **Open Addressing**: Linear probing, quadratic probing, or double hashing.
- **C++ STL Containers**:
  - `std::unordered_map<K, V>` & `std::unordered_set<K>`: Average $\mathcal{O}(1)$ lookup, insertion, deletion. Worst case $\mathcal{O}(N)$ on heavy collisions.
  - `std::map<K, V>` & `std::set<K>`: Self-balancing BST (Red-Black Tree). Guaranteed $\mathcal{O}(\log N)$ operations and maintains elements in sorted order.

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Frequency Counting / Lookup Map
Used for anagram detection, finding duplicates, two sum lookups.
```cpp
// Check if two strings are anagrams (Frequency array for ASCII/lowercase)
bool isAnagram(const string& s, const string& t) {
    if (s.length() != t.length()) return false;
    vector<int> count(26, 0);
    for (char c : s) count[c - 'a']++;
    for (char c : t) {
        if (--count[c - 'a'] < 0) return false;
    }
    return true;
}
```

### Pattern B: Prefix Sum & Hash Map (Subarray Sum Equals K)
Find the number of continuous subarrays whose sum equals $K$.
```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1; // Base case: empty prefix has sum 0
    int currentSum = 0;
    int totalSubarrays = 0;

    for (int num : nums) {
        currentSum += num;
        if (prefixCount.find(currentSum - k) != prefixCount.end()) {
            totalSubarrays += prefixCount[currentSum - k];
        }
        prefixCount[currentSum]++;
    }
    return totalSubarrays;
}
```

### Pattern C: Kadane's Algorithm (Maximum Subarray Sum)
Calculates the maximum sum contiguous subarray in $\mathcal{O}(N)$ time and $\mathcal{O}(1)$ space.
```cpp
int maxSubArray(vector<int>& nums) {
    int maxSoFar = nums[0];
    int currentMax = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        currentMax = max(nums[i], currentMax + nums[i]);
        maxSoFar = max(maxSoFar, currentMax);
    }
    return maxSoFar;
}
```

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Custom Hash for Pairs / Tuples**: `std::unordered_map` does not provide a default hash function for `std::pair<int, int>`. Always define a custom functor using `boost::hash_combine` or bit shifting:
   ```cpp
   struct PairHash {
       size_t operator()(const pair<int, int>& p) const {
           return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
       }
### Pattern D: Transformed Prefix Sum with Incremental Frequency Maintenance
To count subarrays satisfying majority/balance conditions (e.g. target element count $>$ remaining elements):
1. Transform elements: target $\to +1$, other $\to -1$.
2. Condition simplifies to prefix sum inequality: $s[l] < s[r+1]$.
3. Since $s[r+1] = s[r] \pm 1$, the count of previous prefix sums strictly less than $s[r+1]$ changes by only one bucket (`pre[s[r]]` or `pre[s[r+1]]`).
4. Maintain `presum` incrementally in $\mathcal{O}(1)$ time with an array `pre[2*N + 1]` shifted by $N$, achieving an optimal $\mathcal{O}(N)$ runtime overall.

### Pattern E: Square Root Decomposition with Multiplicative Difference Arrays
When range updates apply periodic stride-$k$ operations (e.g. arithmetic progressions $l + c \cdot k \le r$):
1. **Threshold Split**: Partition step size $k$ with threshold $B = \lfloor \sqrt{N} \rfloor$.
2. **Large $k \ge B$**: Apply brute force directly in $\mathcal{O}(N/k) \le \mathcal{O}(\sqrt{N})$ per query.
3. **Small $k < B$**: Group queries by $k$. Maintain a modular difference array `diff[idx]` updated at $l$ with $v$ and at $last + k$ with $v^{-1} \pmod M$. Propagate prefix products across each residue class modulo $k$ in $\mathcal{O}(N)$ time per small $k$.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Unordered Map Rehashing Overheads**: `std::unordered_map` can degrade to $\mathcal{O}(N^2)$ due to hash collisions. Use `custom_hash` or static arrays:
   ```cpp
   struct custom_hash {
       static uint64_t splitmix64(uint64_t x) {
           x += 0x9e3779b97f4a7c15;
           x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
           x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
           return x ^ (x >> 31);
       }
       size_t operator()(uint64_t x) const {
           static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
           return splitmix64(x + FIXED_RANDOM);
       }
   };
   ```
2. **Integer Overflow in Prefix Sums & Combinatorics**: When counting total valid subarrays ($N \le 10^5$), the total count can reach $\approx 5 \times 10^9$. Always use `long long` for accumulators.
3. **Negative Indexing in Shifted Arrays**: When using static frequency tables for values in $[-N, N]$, always offset by $N$ (`table[val + N]`).

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 3655 | [XOR After Range Multiplication Queries II](../solutions/3655-xor-after-range-multiplication-queries-ii/README.md) | `Hard` | $\mathcal{O}((N + Q)\sqrt{N})$ | $\mathcal{O}(N + Q)$ | [C++](../solutions/3655-xor-after-range-multiplication-queries-ii/solution.cpp) |
| 3739 | [Count Subarrays With Majority Element II](../solutions/3739-count-subarrays-with-majority-element-ii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/3739-count-subarrays-with-majority-element-ii/solution.cpp) |


