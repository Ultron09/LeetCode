# [123. Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an array `prices` where `prices[i]` is the price of a given stock on the $i^{\text{th}}$ day.

Find the **maximum profit** you can achieve. You may complete **at most two transactions**.

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

### Example 1:
```
Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3 - 0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4 - 1 = 3.
Total profit = 3 + 3 = 6.
```

### Example 2:
```
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5 - 1 = 4.
```

### Example 3:
```
Input: prices = [7,6,4,3,1]
Output: 0
```

### Constraints:
- $1 \le \text{prices.length} \le 10^5$
- $0 \le \text{prices}[i] \le 10^5$

---

## 💡 Intuition & Approach

### 1. Four-State Finite State Machine (FSM)
At any point in time during the sequence of prices, an investor is in one of four distinct states:
1. `buy1`: Maximizing remaining cash after buying the 1st stock:
   $$\text{buy1} = \max(\text{buy1}, -\text{price})$$
2. `sell1`: Maximizing profit after selling the 1st stock:
   $$\text{sell1} = \max(\text{sell1}, \text{buy1} + \text{price})$$
3. `buy2`: Maximizing cash after buying the 2nd stock using profit gained from `sell1`:
   $$\text{buy2} = \max(\text{buy2}, \text{sell1} - \text{price})$$
4. `sell2`: Maximizing total profit after selling the 2nd stock:
   $$\text{sell2} = \max(\text{sell2}, \text{buy2} + \text{price})$$

### 2. Space Optimization
Because each state only depends on the previous state's evaluation on the current day, all four states can be updated concurrently in $\mathcal{O}(1)$ space in a single forward pass.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N = \text{prices.length}$ (single linear pass, $< 10$ ms in C++).
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space for 4 state registers.

---

## 🔍 Edge Cases Considered

- **Monotonically decreasing prices** (`[7, 6, 4, 3, 1]`): Handled $\implies \text{returns 0}$.
- **Monotonically increasing prices** (`[1, 2, 3, 4, 5]`): Handled $\implies \text{returns 4}$.
- **Single day price array** (`[1]`): Handled $\implies \text{returns 0}$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
