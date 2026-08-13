# [765. Couples Holding Hands](https://leetcode.com/problems/couples-holding-hands/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), Union Find, Greedy

---

## 📌 Problem Statement

There are `n` couples sitting in `2n` seats arranged in a row and want to hold hands.

The people and seats are represented by an integer array `row` where `row[i]` is the ID of the person sitting in the `ith` seat. The couples are numbered in order, the first couple being `(0, 1)`, the second couple being `(2, 3)`, and so on with the last couple being `(2n - 2, 2n - 1)`.

Return the minimum number of swaps so that every couple is sitting side by side. A swap consists of choosing any two people, then they stand up and switch seats.

### Example 1:
```
Input: row = [0,2,1,3]
Output: 1
Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
```

### Example 2:
```
Input: row = [3,2,0,1]
Output: 0
Explanation: All couples are already seated side by side.
```

### Constraints:
- `2n == row.length`
- `2 <= n <= 30`
- `0 <= row[i] < 2n`
- All the elements of `row` are unique.

---

## 💡 Intuition & Approach

This is a classic cycle decomposition problem that can be modeled using Graph Theory or Union Find.

1. **Graph Modeling**: Imagine there are $N$ couches, each holding 2 people. Ideally, each couch should hold exactly one couple. If we look at the two people sitting on a couch, we can identify which couples they belong to. A person with ID `x` belongs to couple `x / 2`.
2. **Edges**: If a couch has a person from Couple A and a person from Couple B, we can imagine an edge between node A and node B.
3. **Cycles**: By connecting all these edges, the graph decomposes into a set of disjoint connected components (cycles). If a component has size $L$ (meaning $L$ couples are mixed up across $L$ couches), it will take exactly $L - 1$ swaps to resolve that entire cycle.
4. **Formula**: The total number of swaps is the sum of $(L - 1)$ for all components. Mathematically, this equals $N - C$, where $N$ is the total number of couples and $C$ is the total number of connected components.
5. **Union Find**: We can iterate through the array taking pairs of adjacent seats, find their respective couple IDs, and `unite()` them in a Disjoint Set structure. Finally, `swaps = N - uf.count`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — We iterate through the array of $2N$ elements once. Each iteration does a `Union` operation which, with path compression, takes $\mathcal{O}(1)$ amortized time.
- **Space Complexity:** $\mathcal{O}(N)$ — For the `parent` array in the Union Find data structure holding $N$ elements.

---

## 🔍 Edge Cases Considered

- **Already Seated Couples**: If all couples are seated correctly, every couple forms a cycle of length 1. $N$ connected components result in $N - N = 0$ swaps.
- **Large Cycles**: If every couch is entangled in a single massive cycle of length $N$, the algorithm correctly computes $N - 1$ swaps.
- **Couple ID Logic**: Using integer division `x / 2` robustly groups `(0,1)` to `0`, `(2,3)` to `1`, etc., without needing complex hash maps or bitwise operations (`x ^ 1`).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
