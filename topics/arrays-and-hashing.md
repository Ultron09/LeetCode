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
   };
   ```
2. **Integer Overflow in Prefix Sums**: When summing large values (e.g. array of $10^5$ elements each up to $10^9$), use `long long` for prefix totals.
3. **Empty / Single Element Arrays**: Always guard against empty inputs.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
<!-- Problems will be added here -->
