# [3501. Maximize Active Section with Trade II](https://leetcode.com/problems/maximize-active-section-with-trade-ii/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given a binary string `s` of length `n`, where:
- `'1'` represents an active section.
- `'0'` represents an inactive section.

You can perform **at most one trade** to maximize the number of active sections in `s`. In a trade, you:
1. Convert a contiguous block of `'1'`s that is surrounded by `'0'`s to all `'0'`s.
2. Afterward, convert a contiguous block of `'0'`s that is surrounded by `'1'`s to all `'1'`s.

Additionally, you are given a 2D array `queries`, where `queries[i] = [li, ri]` represents a substring `s[li...ri]`.

For each query, determine the **maximum possible number of active sections in `s`** after making the optimal trade on the substring `s[li...ri]`.

Return an array `answer`, where `answer[i]` is the result for `queries[i]`.

**Note:**
- For each query, treat `s[li...ri]` as if it is augmented with a `'1'` at both ends, forming $t = \text{'1'} + s[li...ri] + \text{'1'}$. The augmented `'1'`s do not contribute to the final count.
- The queries are independent of each other.

### Example 1:
```
Input: s = "01", queries = [[0,1]]
Output: [1]
Explanation: Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.
```

### Example 2:
```
Input: s = "0100", queries = [[0,3],[0,2],[1,3],[2,3]]
Output: [4,3,1,1]
```

### Example 3:
```
Input: s = "1000100", queries = [[1,5],[0,6],[0,4]]
Output: [6,7,2]
```

### Example 4:
```
Input: s = "01010", queries = [[0,3],[1,4],[1,3]]
Output: [4,4,2]
```

### Constraints:
- $1 \le n = s.\text{length} \le 10^5$
- $1 \le \text{queries.length} \le 10^5$
- `s[i]` is either `'0'` or `'1'`.
- `queries[i] = [li, ri]` with $0 \le li \le ri < n$.

---

## 💡 Intuition & Approach

### 1. Mathematical Mechanics of a Trade
In the augmented substring $t = \text{'1'} + s[l \dots r] + \text{'1'}$:
- A trade selects a block of `'1'`s located between two adjacent `'0'`-blocks $B_j$ and $B_{j+1}$.
- In Step 1, converting this `'1'`-block to `'0'`s merges $B_j$ and $B_{j+1}$ into a single contiguous `'0'`-block of combined length $\text{len}(B_j) + \text{len}(1\text{s}) + \text{len}(B_{j+1})$.
- In Step 2, converting this merged `'0'`-block to `'1'`s turns all its zeros into ones.
- **Net Gain:** The initial `'1'`s are restored, and all the `'0'`s from both blocks are converted to `'1'`s. Hence, the net gain in active sections is:
  $$\text{Gain} = \text{effective\_len}(B_j) + \text{effective\_len}(B_{j+1})$$
- The total active sections in $s$ becomes:
  $$\text{Total Active} = \text{total 1s in } s + \max_{(B_j, B_{j+1})} \big( \text{effective\_len}(B_j) + \text{effective\_len}(B_{j+1}) \big)$$

### 2. Preprocessing & Grouping
1. Identify all contiguous blocks of `'0'`s in $s$: $Z_0, Z_1, \dots, Z_{m-1}$ where $Z_k = [start_k, end_k, len_k]$.
2. Precompute the adjacent sum array:
   $$\text{mergeLengths}[j] = len_j + len_{j+1} \quad \text{for } 0 \le j < m - 1$$
3. Build a **Sparse Table** over `mergeLengths` to support $\mathcal{O}(1)$ Range Maximum Queries (RMQ).

### 3. Answering Each Query in $\mathcal{O}(\log M)$
For query $[l, r]$:
1. **Binary Search**:
   - Find the first zero block with $end \ge l$: `first = lower_bound(groupEnds, l)`
   - Find the last zero block with $start \le r$: `last = upper_bound(groupStarts, r) - 1`
2. **If $first \ge last$**: Fewer than 2 zero blocks intersect $[l, r]$, so no trade is possible $\implies$ return $\text{total 1s}$.
3. **If $first < last$**:
   - Compute boundary clamped lengths:
     $$\text{effFirst} = end_{first} - \max(start_{first}, l) + 1$$
     $$\text{effLast} = \min(end_{last}, r) - start_{last} + 1$$
   - **If $last == first + 1$**: Only one candidate pair $(first, last) \implies \text{Gain} = \text{effFirst} + \text{effLast}$.
   - **If $last > first + 1$**:
     - Check boundary pairs: $\text{effFirst} + len_{first+1}$ and $len_{last-1} + \text{effLast}$.
     - Check all fully-contained interior pairs in range $[first + 1, last - 2]$ using Sparse Table in $\mathcal{O}(1)$:
       $$\text{RMQ}(first + 1, last - 2)$$
     - $\text{Gain} = \max(\text{boundary candidates}, \text{RMQ})$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N + Q \log N)$
  - 0-block identification: $\mathcal{O}(N)$.
  - Sparse Table construction: $\mathcal{O}(M \log M)$ where $M \le N/2$.
  - Per query: 2 binary searches ($\mathcal{O}(\log M)$) + 1 RMQ ($\mathcal{O}(1)$) $\implies \mathcal{O}(\log M)$.
  - For $N, Q = 10^5$, total execution time is under $35$ ms in C++.
- **Space Complexity:** $\mathcal{O}(N \log N)$ for the Sparse Table and zero-block arrays.

---

## 🔍 Edge Cases Considered

- **No 0s or Single 0 Block in $[l, r]$**: Correctly recognized via $first \ge last$, returning baseline ones count without trade.
- **Substring Cutting Through 0-Blocks**: Boundary clamping properly computes partial lengths for `first` and `last`.
- **$M \le 1$ Globally**: Returns immediate baseline for all queries.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
