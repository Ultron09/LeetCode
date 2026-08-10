# 📈 Dynamic Programming

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Dynamic Programming (DP).

---

## 📖 1. Core Theory & Fundamentals

Dynamic Programming solves optimization and counting problems by combining solutions to overlapping subproblems with optimal substructure.

### Two Implementation Philosophies
1. **Top-Down with Memoization**: Natural recursive breakdown + cache lookup table $\mathcal{O}(N)$.
2. **Bottom-Up Iteration (Tabulation)**: Build solution from base cases iteratively; frequently allows space optimization from $\mathcal{O}(N)$ or $\mathcal{O}(N^2)$ to $\mathcal{O}(1)$ or $\mathcal{O}(N)$.

### DP Problem Identification Framework
1. **Define State**: What parameters uniquely identify a subproblem? (e.g. `dp[i]` or `dp[i][j]`).
2. **State Transition Relation**: Express `dp[state]` as a function of smaller subproblems.
3. **Base Cases**: Minimal subproblem boundary states (e.g. `dp[0] = 0`).
4. **Evaluation Order**: Ensure subproblems are computed before they are consumed.
5. **Space Optimization**: Does transition only depend on the previous row or previous element?

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: 1D DP / Fibonacci & House Robber Pattern
```cpp
// House Robber: dp[i] = max(dp[i-1], dp[i-2] + nums[i])
int rob(vector<int>& nums) {
    int prev2 = 0; // dp[i-2]
    int prev1 = 0; // dp[i-1]

    for (int num : nums) {
        int current = max(prev1, prev2 + num);
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}
```

### Pattern B: 0/1 Knapsack & Unbounded Knapsack (Coin Change)
```cpp
// Coin Change: Minimum coins to make up amount (Unbounded knapsack)
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (i - coin >= 0) {
                dp[i] = min(dp[i], 1 + dp[i - coin]);
            }
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}
```

### Pattern C: Longest Common Subsequence (2D DP / String Alignment)
```cpp
int longestCommonSubsequence(const string& text1, const string& text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}
```

### Pattern D: Longest Increasing Subsequence ($\mathcal{O}(N \log N)$ Patience Sort)
```cpp
int lengthOfLIS(vector<int>& nums) {
    vector<int> tails;
    for (int num : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if (it == tails.end()) {
            tails.push_back(num);
        } else {
            *it = num;
        }
    }
    return tails.size();
}
```

### Pattern E: Minimax & Game Theory DP (Relative Score Difference)
Used in two-player zero-sum sequential games (e.g. Stone Game series).
Define $DP[i]$ as the maximum relative score difference $(\text{my\_score} - \text{opponent\_score})$ achievable starting from state $i$:
$$DP[i] = \max_{\text{valid choices } k} \left( \text{gain}(k) - DP[\text{next\_state}(i, k)] \right)$$
```cpp
// Stone Game III: Take 1, 2, or 3 stones
int dp1 = 0, dp2 = 0, dp3 = 0; // dp[i+1], dp[i+2], dp[i+3]
for (int i = n - 1; i >= 0; --i) {
    int sum = 0, best = INT_MIN;
    for (int k = 1; k <= 3 && i + k - 1 < n; ++k) {
        sum += stoneValue[i + k - 1];
        int nextDP = (k == 1 ? dp1 : (k == 2 ? dp2 : dp3));
        best = max(best, sum - nextDP);
    }
    dp3 = dp2; dp2 = dp1; dp1 = best;
}
```

### Pattern F: Disjoint Multi-Subsequence DP (Tracking Associative Properties)
When partitioning elements into multiple disjoint subsequences while tracking associative properties (e.g. $\gcd(s_1) = \gcd(s_2)$ or $\text{XOR}(s_1) = \text{XOR}(s_2)$):
- Maintain a rolling table `dp[p1][p2]` where $p_1, p_2$ represent current property states ($0$ = empty subsequence).
- For each element $x$, evaluate 3 disjoint branches:
  1. Skip $x$: `nextDp[p1][p2] += dp[p1][p2]`
  2. Add to $s_1$: `nextDp[f(p1, x)][p2] += dp[p1][p2]`
  3. Add to $s_2$: `nextDp[p1][f(p2, x)] += dp[p1][p2]`
- Precomputing transition tables (e.g. `gcdTable[M][M]`) reduces state transition costs to $\mathcal{O}(1)$.

### Pattern G: Dual-State Grid DP (Maximum Value + Counting Optimal Paths)
When simultaneously optimizing a value (e.g. max path sum) and counting the number of distinct optimal paths:
- Define `dp[r][c] = {best_value, path_count}`.
- Examine reachable predecessors/neighbors:
  1. Find `max_val = max(neighbor.value)`.
  2. Sum `path_count` of all neighbors whose value equals `max_val` modulo $10^9 + 7$.
  3. Set `dp[r][c] = {max_val + grid[r][c], total_ways}`.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **State Initialization / Infinity Bounds**: When finding minimums, initialize with a sentinel value (e.g. `amount + 1` or `1e9`) instead of `INT_MAX` to avoid integer overflow during additions like `1 + dp[i - coin]`.
2. **0/1 Knapsack Order**: In 1D space-optimized 0/1 knapsack, traverse capacities backwards (`for (int w = W; w >= weight; --w)`) to avoid reusing the same item.
3. **Off-by-One in DP Table Sizes**: Allocate size `N + 1` when `dp[0]` represents the empty string/prefix.
4. **Unreachable Cells in Multi-Criteria DP**: Guard against propagating from unreachable cells (e.g. `score == -1`); skip them when computing neighbor transitions.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 1301 | [Number of Paths with Max Score](../solutions/1301-number-of-paths-with-max-score/README.md) | `Hard` | $\mathcal{O}(N^2)$ | $\mathcal{O}(N^2)$ | [C++](../solutions/1301-number-of-paths-with-max-score/solution.cpp) |
| 1406 | [Stone Game III](../solutions/1406-stone-game-iii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/1406-stone-game-iii/solution.cpp) |
| 3336 | [Find the Number of Subsequences With Equal GCD](../solutions/3336-find-the-number-of-subsequences-with-equal-gcd/README.md) | `Hard` | $\mathcal{O}(N \cdot M^2)$ | $\mathcal{O}(M^2)$ | [C++](../solutions/3336-find-the-number-of-subsequences-with-equal-gcd/solution.cpp) |


