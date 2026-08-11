# [502. IPO](https://leetcode.com/problems/ipo/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Heaps / Priority Queue](../../topics/heaps-and-priority-queues.md)

---

## 📌 Problem Statement

Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited resources, it can only finish at most `k` distinct projects before the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most `k` distinct projects.

You are given `n` projects where the $i$-th project has a pure profit `profits[i]` and a minimum capital of `capital[i]` is needed to start it.

Initially, you have `w` capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.

Pick a list of at most `k` distinct projects from given projects to maximize your final capital, and return the **final maximized capital**.

The answer is guaranteed to fit in a 32-bit signed integer.

### Example 1:
```
Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
Output: 4
Explanation: 
- Since your initial capital is 0, you can only start the project indexed 0.
- After finishing it you will obtain profit 1 and your capital becomes 1.
- With capital 1, you can start project 1 or project 2.
- Finishing project 2 yields pure profit 3 -> capital becomes 1 + 3 = 4.
```

### Example 2:
```
Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
Output: 6
```

### Constraints:
- $1 \le k \le 10^5$
- $0 \le w \le 10^9$
- $n == \text{profits.length} == \text{capital.length}$
- $1 \le n \le 10^5$
- $0 \le \text{profits}[i] \le 10^4$
- $0 \le \text{capital}[i] \le 10^9$

---

## 💡 Intuition & Approach

### 1. Greedy Choice & Matroid Property
- Finishing a project never decreases our capital because all `profits[i] >= 0`.
- As capital $w$ grows, the set of affordable projects $(\text{capital}[i] \le w)$ is **monotonically expanding**.
- At any step, among all currently affordable projects, selecting the project with the **maximum profit** is optimal: it yields the largest immediate increase in capital, thereby maximizing the pool of newly unlocked projects for all subsequent choices.

### 2. Dual Data Structure Implementation
1. **Sorting by Capital**: Pair up `(capital[i], profits[i])` and sort ascendingly by required capital.
2. **Max-Heap for Affordable Profits**:
   - Maintain a max-heap `availableProfits`.
   - While the next project in the sorted list has $\text{capital} \le w$, push its profit into the heap and advance the pointer.
   - Pop the top profit from `availableProfits`, add it to $w$, and repeat for up to $k$ rounds.
   - If the heap becomes empty at any turn, no further projects can be afforded, and we terminate early.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N + k \log N)$
  - Sorting $N$ projects takes $\mathcal{O}(N \log N)$.
  - Each project profit is pushed and popped from the max-heap at most once across all $k$ rounds, taking $\mathcal{O}(N \log N)$.
  - Overall time for $N, k \le 10^5$ is $\approx 3 \times 10^6$ operations (executes in $< 35\text{ ms}$).
- **Space Complexity:** $\mathcal{O}(N)$
  - Storing paired projects and heap elements.

---

## 🔍 Edge Cases Considered

- **$k \ge N$**: Finishes all affordable projects and terminates when the heap empties.
- **Initial Capital $w = 0$**: Correctly unlocks zero-capital projects first.
- **Zero Profit Projects**: Handled naturally without breaking heap invariants.
- **No Affordable Projects**: Returns initial capital $w$ immediately.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
