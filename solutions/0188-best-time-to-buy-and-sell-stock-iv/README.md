# [188. Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Array](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an integer array `prices` where `prices[i]` is the price of a given stock on the $i$-th day, and an integer `k`.

Find the **maximum profit** you can achieve. You may complete at most `k` transactions (i.e. buy at most `k` times and sell at most `k` times).

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

### Example 1:
```
Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
```

### Example 2:
```
Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. 
Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
```

### Constraints:
- $1 \le k \le 100$
- $1 \le \text{prices.length} \le 1000$
- $0 \le \text{prices}[i] \le 1000$

---

## 💡 Intuition & Approach

### 1. Unlimited Transactions Shortcut ($k \ge N / 2$)
Since each transaction requires at least 2 distinct days (1 to buy, 1 to sell), having $k \ge \lfloor N / 2 \rfloor$ means the transaction limit $k$ will never constrain profitability. We can greedily collect every ascending price segment in $\mathcal{O}(N)$ time:
$$\text{profit} = \sum_{i=1}^{N-1} \max(0, \text{prices}[i] - \text{prices}[i - 1])$$

### 2. General $k$-Transaction Finite State Machine
For $k < N / 2$, maintain state arrays $\text{buy}[t]$ and $\text{sell}[t]$ for $t \in [1, k]$:
- $\text{buy}[t]$: Maximum cash balance after purchasing the $t$-th stock.
- $\text{sell}[t]$: Maximum accumulated profit after completing the $t$-th sale.

For each price $p \in \text{prices}$:
$$\text{buy}[t] = \max(\text{buy}[t], \text{sell}[t - 1] - p)$$
$$\text{sell}[t] = \max(\text{sell}[t], \text{buy}[t] + p)$$
The result is $\text{sell}[k]$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot k)$ where $N \le 1000, k \le 100$ (or $\mathcal{O}(N)$ when $k \ge N/2$).
- **Space Complexity:** $\mathcal{O}(k)$ auxiliary space for state arrays.

---

## 🔍 Edge Cases Considered

- **$k = 0$ or $N \le 1$**: Handled $\implies \text{returns } 0$.
- **Monotonically Decreasing Prices** (e.g. `[5, 4, 3, 2, 1]`): No trades executed $\implies \text{returns } 0$.
- **Large $k$**: Handled by fast $\mathcal{O}(N)$ greedy short-circuit.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
