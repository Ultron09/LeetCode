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

### Pattern F: Grid Cut Partitioning with Connectivity-Preserving Discounting
When finding 1D cuts (horizontal/vertical) across a 2D matrix to balance partition sums with optional single-cell discounting:
1. **Transposition for Orientation Reuse**: Evaluate vertical cuts by transposing the grid and running the horizontal cut subroutine.
2. **Dynamic Frequency Sweeping**: Maintain `topCount` and `bottomCount` frequency maps, shifting one row/column per step in $\mathcal{O}(M \cdot N)$ total time.
3. **Geometric Connectivity Rules for Rectangle Single-Cell Removal**:
   - $1 \times C$ or $R \times 1$: Only the two boundary endpoints maintain connectivity.
   - $R \ge 2 \text{ and } C \ge 2$: Any single cell removal preserves full 4-directional connectivity.

### Pattern G: In-Place Cycle Sort & Self-Hashing
To find the smallest missing positive integer in $[1, N + 1]$ with $\mathcal{O}(1)$ auxiliary space:
1. **Pigeonhole Target Range**: The missing positive must fall within $[1, N + 1]$.
2. **Cycle Sort Invariant**: For each index $i$, repeatedly swap `nums[i]` with `nums[nums[i] - 1]` while `1 <= nums[i] <= N` and `nums[nums[i] - 1] != nums[i]`.
3. **Linear Scan**: The first index $i$ where `nums[i] != i + 1` identifies the missing positive $i + 1$. If all match, return $N + 1$.

### Pattern H: Bidirectional Palindromic Prefix/Suffix Splitting with Hash Table
When finding all pairs $(i, j)$ such that $\text{words}[i] + \text{words}[j]$ forms a palindrome:
1. **Hash Map Indexing**: Store all strings in an `unordered_map<string, int>`.
2. **Decomposition per Word**:
   For each word $w$ of length $L$, test all $L + 1$ split points $k \in [0, L]$ where $w = w[0\dots k-1] + w[k\dots L-1]$:
   - **Suffix Palindrome (Append $(i, j)$)**: If $w[k\dots L-1]$ is a palindrome, check if $\text{reversed}(w[0\dots k-1])$ exists in the map at $j \ne i$.
   - **Prefix Palindrome (Prepend $(j, i)$)**: If $k > 0$ and $w[0\dots k-1]$ is a palindrome, check if $\text{reversed}(w[k\dots L-1])$ exists in the map at $j \ne i$.
3. **Complexity**: Achieves optimal $\mathcal{O}(\sum L_i^2)$ time with $\mathcal{O}(N \cdot L)$ space.
### Pattern I: O(1) Randomized Multiset with Dense Array + Index Set Map
When building a multiset supporting $\mathcal{O}(1)$ insert, remove, and uniform random sampling:
1. **Dense Array**: Store all elements in a `vector<int> nums` for $\mathcal{O}(1)$ random access via `nums[rand() % size]`.
2. **Index Set Map**: Maintain `unordered_map<int, unordered_set<int>> valToIdx` mapping each value to its set of indices in `nums`.
3. **Swap-and-Pop Removal**: To remove `val` at `removeIdx`, swap with `nums.back()`, update both index sets, then `pop_back()`.
4. **Self-Swap Guard**: When `removeIdx == lastIdx`, do **not** re-insert the index after erasing, or the set will contain a stale entry.

### Pattern I: Island-and-Gap Consecutive Streak Partitioning (Human Traffic of Stadium)
When grouping contiguous runs of qualifying entities (e.g., consecutive sequence IDs):
1. **Window Invariant**: In SQL, `id - ROW_NUMBER() OVER (ORDER BY id)` is identical for all consecutive IDs in an unbroken run.
2. **Partition Aggregation**: Window function `COUNT(*) OVER (PARTITION BY island_id)` evaluates the run length in $\mathcal{O}(N)$ without expensive self-joins.
3. **In-Memory Two-Pointer Scanning**: In algorithmic C++, a two-pointer pass $[i, j]$ identifies runs where $A[k+1] = A[k] + 1$ and outputs segments of length $\ge K$.
4. **Complexity**: $\mathcal{O}(N)$ time and $\mathcal{O}(N)$ space.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **`std::unordered_map` Anti-Hash Collisions**: `std::hash` for primitive integer types is an identity mapping in GCC/Clang, making it vulnerable to $\mathcal{O}(N^2)$ worst-case hash-bomb test cases. Use a custom `splitmix64` hash functor for competitive programming:
   ```cpp
   struct CustomHash {
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
| 1 | [Two Sum](../solutions/0001-two-sum/README.md) | `Easy` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0001-two-sum/solution.cpp) |
| 41 | [First Missing Positive](../solutions/0041-first-missing-positive/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0041-first-missing-positive/solution.cpp) |
| 185 | [Department Top Three Salaries](../solutions/0185-department-top-three-salaries/README.md) | `Hard` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N)$ | [SQL / C++](../solutions/0185-department-top-three-salaries/solution.sql) |
| 262 | [Trips and Users](../solutions/0262-trips-and-users/README.md) | `Hard` | $\mathcal{O}(T + U)$ | $\mathcal{O}(U + D)$ | [SQL / C++](../solutions/0262-trips-and-users/solution.sql) |
| 336 | [Palindrome Pairs](../solutions/0336-palindrome-pairs/README.md) | `Hard` | $\mathcal{O}(\sum L_i^2)$ | $\mathcal{O}(N \cdot L)$ | [C++](../solutions/0336-palindrome-pairs/solution.cpp) |
| 381 | [Insert Delete GetRandom O(1) - Duplicates allowed](../solutions/0381-insert-delete-getrandom-o1-duplicates-allowed/README.md) | `Hard` | $\mathcal{O}(1)$ avg | $\mathcal{O}(N)$ | [C++](../solutions/0381-insert-delete-getrandom-o1-duplicates-allowed/solution.cpp) |
| 601 | [Human Traffic of Stadium](../solutions/0601-human-traffic-of-stadium/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [SQL / C++](../solutions/0601-human-traffic-of-stadium/solution.sql) |
| 710 | [Random Pick with Blacklist](../solutions/0710-random-pick-with-blacklist/README.md) | `Hard` | $\mathcal{O}(1)$ pick | $\mathcal{O}(B)$ | [C++](../solutions/0710-random-pick-with-blacklist/solution.cpp) |
| 768 | [Max Chunks To Make Sorted II](../solutions/0768-max-chunks-to-make-sorted-ii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0768-max-chunks-to-make-sorted-ii/solution.cpp) |
| 798 | [Smallest Rotation with Highest Score](../solutions/0798-smallest-rotation-with-highest-score/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0798-smallest-rotation-with-highest-score/solution.cpp) |
| 805 | [Split Array With Same Average](../solutions/0805-split-array-with-same-average/README.md) | `Hard` | $\mathcal{O}(2^{N/2} \log(2^{N/2}))$ | $\mathcal{O}(2^{N/2})$ | [C++](../solutions/0805-split-array-with-same-average/solution.cpp) |
| 843 | [Guess the Word](../solutions/0843-guess-the-word/README.md) | `Hard` | $\mathcal{O}(N^2)$ | $\mathcal{O}(N)$ | [C++](../solutions/0843-guess-the-word/solution.cpp) |
| 891 | [Sum of Subsequence Widths](../solutions/0891-sum-of-subsequence-widths/README.md) | `Hard` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0891-sum-of-subsequence-widths/solution.cpp) |
| 2996 | [Smallest Missing Integer Greater Than Sequential Prefix Sum](../solutions/2996-smallest-missing-integer-greater-than-sequential-prefix-sum/README.md) | `Easy` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/2996-smallest-missing-integer-greater-than-sequential-prefix-sum/solution.cpp) |
| 3548 | [Equal Sum Grid Partition II](../solutions/3548-equal-sum-grid-partition-ii/README.md) | `Hard` | $\mathcal{O}(M \cdot N)$ | $\mathcal{O}(M \cdot N)$ | [C++](../solutions/3548-equal-sum-grid-partition-ii/solution.cpp) |
| 3655 | [XOR After Range Multiplication Queries II](../solutions/3655-xor-after-range-multiplication-queries-ii/README.md) | `Hard` | $\mathcal{O}((N + Q)\sqrt{N})$ | $\mathcal{O}(N + Q)$ | [C++](../solutions/3655-xor-after-range-multiplication-queries-ii/solution.cpp) |
| 3739 | [Count Subarrays With Majority Element II](../solutions/3739-count-subarrays-with-majority-element-ii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/3739-count-subarrays-with-majority-element-ii/solution.cpp) |
