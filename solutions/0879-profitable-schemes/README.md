# [879. Profitable Schemes](https://leetcode.com/problems/profitable-schemes/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

There is a group of `n` members, and a list of various crimes they could commit. The `i`-th crime generates a `profit[i]` and requires `group[i]` members to participate in it. If a member participates in one crime, that member can't participate in another crime.

Let's call a profitable scheme any subset of these crimes that generates at least `minProfit` profit, and the total number of members participating in that subset of crimes is at most `n`.

Return the number of schemes that can be chosen. Since the answer may be very large, return it modulo `10^9 + 7`.

### Example 1:
```
Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
Output: 2
Explanation: To make a profit of at least 3, the group could either commit crimes 0 and 1, or just crime 1.
In total, there are 2 schemes.
```

### Example 2:
```
Input: n = 10, minProfit = 5, group = [2,3,5], profit = [6,7,8]
Output: 7
Explanation: To make a profit of at least 5, the group could commit any crimes, as long as they commit one.
There are 7 possible schemes: (0), (1), (2), (0,1), (0,2), (1,2), and (0,1,2).
```

### Constraints:
- `1 <= n <= 100`
- `0 <= minProfit <= 100`
- `1 <= group.length <= 100`
- `1 <= group[i] <= 100`
- `profit.length == group.length`
- `0 <= profit[i] <= 100`

---

## 💡 Intuition & Approach

1. **Multidimensional Knapsack Problem**: This is a variation of the 0/1 Knapsack problem. Each crime represents an item. We have two constraints/dimensions to keep track of for our knapsack state:
   - The exact number of members used (bounded by `n`).
   - The total profit generated (needs to reach `minProfit`).

2. **DP State**: 
   Let `dp[j][k]` be the number of subsets of crimes (schemes) that use exactly `j` members and produce a profit of *at least* `k`.
   Since we only care about hitting `minProfit`, any profit generated that exceeds `minProfit` is treated exactly the same as hitting exactly `minProfit`. This means the profit dimension `k` is safely capped at `minProfit`.

3. **State Transition**:
   For each crime requiring `g` members and generating `p` profit:
   We iterate through all possible previous members `j` and previous profits `k` backwards:
   `dp[j][k] = dp[j][k] + dp[j - g][max(0, k - p)]`
   
   - We iterate backwards (`j` from `n` to `g`, and `k` from `minProfit` to `0`) so that we can compute the transitions in-place using a 2D array, rather than keeping an extra outer dimension for the $i$-th crime.
   - `max(0, k - p)`: This ensures that if the current crime's profit `p` is greater than or equal to the required profit `k`, we look back to `dp[j - g][0]` (which tracks any scheme that started with 0 profit requirement).

4. **Base Case & Final Answer**:
   - `dp[0][0] = 1`: There is exactly 1 way to use 0 members and generate at least 0 profit (by picking the empty subset).
   - After processing all crimes, the total number of valid schemes is the sum of `dp[j][minProfit]` for all $j \in [0, n]$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(L \cdot N \cdot P)$ — Where $L$ is the number of crimes (length of `group`), $N$ is the max number of members `n`, and $P$ is `minProfit`. The constraints are very small ($\le 100$), giving at most $100 \times 100 \times 100 = 1,000,000$ loop iterations, which is extremely fast.
- **Space Complexity:** $\mathcal{O}(N \cdot P)$ — We use a 2D DP array of size $(n+1) \times (minProfit+1)$.

---

## 🔍 Edge Cases Considered

- `minProfit = 0`: In this case, any subset of crimes that fits within `n` members is profitable, including the empty subset. Handled perfectly by the base case and loop condition.
- A single crime providing huge profit far exceeding `minProfit`: Safely constrained by the `max(0, k - p)` logic.
- Total members needed strictly exceeds `n`: Ignored since the inner loop for `j` stops exactly at `g`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
