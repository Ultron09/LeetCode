# [952. Largest Component Size by Common Factor](https://leetcode.com/problems/largest-component-size-by-common-factor/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [Union Find](../../topics/graphs.md)

---

## 📌 Problem Statement

You are given an integer array of unique positive integers `nums`. Consider the following graph:

- There are `nums.length` nodes, labeled `nums[0]` to `nums[nums.length - 1]`,
- There is an undirected edge between `nums[i]` and `nums[j]` if `nums[i]` and `nums[j]` share a common factor greater than `1`.

Return the size of the largest connected component in the graph.

### Example 1:
```
Input: nums = [4,6,15,35]
Output: 4
```

### Example 2:
```
Input: nums = [20,50,9,63]
Output: 2
```

### Constraints:
- `1 <= nums.length <= 2 * 10^4`
- `1 <= nums[i] <= 10^5`
- All the values of `nums` are unique.

---

## 💡 Intuition & Approach

Directly checking all pairs for a common factor would take $\mathcal{O}(N^2)$ time, which is too slow given $N = 2 \times 10^4$. Instead, we can think of the problem in terms of bipartite matching between **numbers** and their **prime factors**.

1. **Union-Find by Prime Factor**: 
   If two numbers share a prime factor, they belong to the same component. Therefore, we can use a Disjoint Set Union (DSU) to connect each number to its prime factors.
   For example, if `15` has prime factors `3` and `5`, we `union(15, 3)` and `union(15, 5)`. Later, if `35` has prime factors `5` and `7`, we `union(35, 5)`. Consequently, `15` and `35` become connected via the prime factor `5`.

2. **Efficient Factorization (Sieve of Eratosthenes)**:
   Since the maximum value in `nums` is $10^5$, we can precompute the Smallest Prime Factor (SPF) for all numbers up to $10^5$. This allows us to factorize any number $x$ in $\mathcal{O}(\log x)$ time.

3. **Counting the Components**:
   After processing all numbers in `nums`, we want to find the connected component that contains the most numbers from our original `nums` array. We can do this by iterating through `nums`, finding the root of each number using `uf.find(x)`, and keeping track of the frequencies of each root. The maximum frequency is our answer.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \log \log M + N \log M)$ where $M$ is the maximum value in `nums` ($10^5$) and $N$ is the length of `nums`. Sieve calculation takes $\mathcal{O}(M \log \log M)$. Factoring and unioning takes $\mathcal{O}(\log M)$ for each of the $N$ numbers. Finding the root at the end takes $\mathcal{O}(N \times \alpha(N))$.
- **Space Complexity:** $\mathcal{O}(M)$ to store the `spf` array and the `parent` array for the Union Find data structure up to the maximum possible element.

---

## 🔍 Edge Cases Considered

- Numbers with no common factors with any other numbers correctly fall into isolated components of size 1.
- Numbers that are primes themselves are seamlessly handled as their only prime factor is themselves.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
