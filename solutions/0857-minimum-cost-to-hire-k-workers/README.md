# [857. Minimum Cost to Hire K Workers](https://leetcode.com/problems/minimum-cost-to-hire-k-workers/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Heaps & Priority Queues](../../topics/heaps-and-priority-queues.md), [Sorting](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

There are `n` workers. You are given two integer arrays `quality` and `wage` where `quality[i]` is the quality of the `i`th worker and `wage[i]` is the minimum wage expectation for the `i`th worker.

We want to hire exactly `k` workers to form a paid group. To hire a group of `k` workers, we must pay them according to the following rules:

1. Every worker in the paid group must be paid at least their minimum wage expectation.
2. In the group, each worker's pay must be directly proportional to their quality. This means if a worker’s quality is double that of another worker in the group, then they must be paid twice as much as the other worker.

Given the integer `k`, return the least amount of money needed to form a paid group satisfying the above conditions. Answers within `10^-5` of the actual answer will be accepted.

### Example 1:
```
Input: quality = [10,20,5], wage = [70,50,30], k = 2
Output: 105.00000
Explanation: We pay 70 to 0th worker and 35 to 2nd worker.
```

### Example 2:
```
Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], k = 3
Output: 30.66667
Explanation: We pay 4 to 0th worker, 13.33333 to 2nd and 3rd workers separately.
```

### Constraints:
- `n == quality.length == wage.length`
- `1 <= k <= n <= 10^4`
- `1 <= quality[i], wage[i] <= 10^4`

---

## 💡 Intuition & Approach

1. **Understanding the Ratio**: For any group of `k` workers to satisfy the proportionality rule, all workers in the group must be paid based on the same ratio `R = wage / quality`. To ensure every worker receives *at least* their minimum expected wage, `R` must be the maximum `wage / quality` ratio among all chosen workers.
2. **Sorting Strategy**: If we sort the workers in ascending order of their `wage / quality` ratio, then for any worker `i` we consider as the "ratio setter" (the worker with the maximum ratio), all workers before `i` in the sorted list have a smaller or equal ratio and can be safely paid using `R`.
3. **Minimizing Cost**: Since the cost of hiring a group is `R * (sum of their qualities)`, we want to pick `k-1` workers from the available pool (before `i`) that have the **smallest possible qualities**.
4. **Max-Heap for Qualities**: We maintain a max-heap of qualities as we iterate through the sorted workers. We keep the size of the heap at `k`. If it exceeds `k`, we remove the worker with the largest quality. This effectively maintains the smallest `k` qualities encountered so far. When the heap has exactly `k` elements, we calculate the cost and update the minimum cost found.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$ — Sorting the array of workers dominates the time complexity $\mathcal{O}(N \log N)$. Processing each worker using a max-heap takes $\mathcal{O}(\log K)$, making the iteration phase $\mathcal{O}(N \log K)$. Overall time is $\mathcal{O}(N \log N)$.
- **Space Complexity:** $\mathcal{O}(N + K)$ — We create a pair array of size $N$ to store worker ratios and qualities, and we maintain a max-heap of size up to $K$.

---

## 🔍 Edge Cases Considered

- Arrays where all workers have the exact same `wage / quality` ratio.
- High variance in qualities forcing the priority queue to quickly discard large outliers.
- Edge values in constraints with $K = 1$ and $K = N$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
