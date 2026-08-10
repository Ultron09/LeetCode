# [135. Candy](https://leetcode.com/problems/candy/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

There are `n` children standing in a line. Each child is assigned a rating value given in the integer array `ratings`.

You are giving candies to these children subjected to the following requirements:
1. Each child must have at least one candy.
2. Children with a higher rating get more candies than their neighbors.

Return the **minimum number of candies** you need to have to distribute the candies to the children.

### Example 1:
```
Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
```

### Example 2:
```
Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
```

### Constraints:
- $n == \text{ratings.length}$
- $1 \le n \le 2 \times 10^4$
- $0 \le \text{ratings}[i] \le 2 \times 10^4$

---

## 💡 Intuition & Approach

### 1. Two-Pass Greedy Strategy
The condition that a child with a higher rating than their neighbor must receive more candies can be decoupled into two independent directional subproblems:
1. **Left-to-Right Pass**: Ensures child $i$ has more candies than child $i - 1$ if $\text{ratings}[i] > \text{ratings}[i - 1]$:
   $$\text{candies}[i] = \text{candies}[i - 1] + 1$$
2. **Right-to-Left Pass**: Ensures child $i$ has more candies than child $i + 1$ if $\text{ratings}[i] > \text{ratings}[i + 1]$:
   $$\text{candies}[i] = \max(\text{candies}[i], \text{candies}[i + 1] + 1)$$
   The $\max$ function guarantees that the left-to-right condition is never violated when fixing the right-to-left condition.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N = \text{ratings.length} \le 2 \times 10^4$ (two linear passes).
- **Space Complexity:** $\mathcal{O}(N)$ auxiliary space for the candy counts array.

---

## 🔍 Edge Cases Considered

- **Flat / Equal Ratings** (e.g. `[1, 2, 2]`): Equal adjacent neighbors do not need more candies than each other; handled properly $\implies \text{returns 4}$.
- **Monotonically Decreasing Array** (e.g. `[5, 4, 3, 2, 1]`): Right-to-left pass assigns `[5, 4, 3, 2, 1]` $\implies \text{returns 15}$.
- **Single Child** (`[1]`): Handled $\implies \text{returns 1}$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
