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

### Pattern H: Matrix Exponentiation DP (Linear Transitions with Huge $N$)
When transitions are linear and $N$ is up to $10^9$ with state size $S \le 150$:
1. Formulate transition matrix $T$ such that $V_{k+1} = T \times V_k$.
2. Compute $T^{N - \text{base}}$ via binary matrix exponentiation in $\mathcal{O}(S^3 \log N)$ time.
3. Multiply the powered matrix by the initial base state vector $V_{\text{base}}$ to obtain final answer in logarithmic time.

### Pattern I: Digit DP with Count & Contribution Sum Propagation
When summing localized structural scores (e.g. peaks, valleys, digit counts) across a large numerical range $[num_1, num_2]$:
1. Decompose range into $\text{solve}(num_2) - \text{solve}(num_1 - 1)$.
2. Use memoized DFS over state `(pos, prev, curr)` with `isLimit` and `isLeading` flags.
3. Propagate pairs `(subCount, subSum)`: when a local condition is met (e.g. $curr$ is a peak), directly add `subCount` to the accumulated sum since all downstream numbers receive $+1$ score.

### Pattern J: DAG Longest Path via DFS + Memoization (Bounded Jumps / Decreasing Walks)
When finding the longest valid traversal in an array where transitions are strictly bounded (distance $d$) and monotonic (height strictly decreases):
1. **DAG Property**: Because transitions move strictly to smaller values ($arr[j] < arr[i]$), cycles are impossible.
2. **Top-Down Memoized DFS**: Compute $\text{dp}[i] = 1 + \max_{j} \text{dp}[j]$ by scanning both left and right directions up to $d$ steps.
3. **Obstacle Pruning**: Immediately terminate directional scans as soon as an intermediate element blocks the path ($arr[j] \ge arr[i]$).

### Pattern K: Multi-Column Boundary DP with Prefix/Suffix Optimization
When grid operations define vertical column profile heights and adjacent columns interact:
1. Formulate 2D state $dp[h_{curr}][h_{prev}]$ capturing the heights of consecutive columns.
2. Precompute prefix and suffix maximums over the previous column's height $k$ to avoid $\mathcal{O}(n)$ inner enumeration.
3. Transition in $\mathcal{O}(1)$ time per state, reducing the global complexity from $\mathcal{O}(n^4)$ to $\mathcal{O}(n^3)$.

### Pattern L: 1D Continuous Matching DP with Capacity Allocations
When assigning 1D objects (e.g. robots) to servicing hubs (e.g. factories) with capacities:
1. **Non-Crossing Monotonicity**: Sort both objects and hubs by 1D coordinates so that relative order is strictly preserved.
2. **State & Transition**: Let $dp[i]$ be the minimum cost to service the first $i$ objects. For each hub $(pos, limit)$, branch over assigning $k \in [1, \min(limit, n - i)]$ contiguous objects:
   $$next\_dp[i + k] = \min(next\_dp[i + k], \, dp[i] + \sum_{j=i}^{i+k-1} |obj[j] - pos|)$$
3. **Space Optimization**: Maintain a 1D rolling array reducing space from $\mathcal{O}(N \cdot M)$ to $\mathcal{O}(N)$.

### Pattern M: Multi-Agent State Compression DP (Free / Implicit Pointer Tracking)
When coordinating two active agents/fingers typing a sequential string:
1. **Implicit Location**: At step $i$, one agent is guaranteed to be at `word[i - 1]`.
2. **Reduced State Space**: Only track the position of the *other* agent `other` $\in [0, \Sigma) \cup \{\text{UNPLACED}\}$, reducing the DP from $\mathcal{O}(N \cdot \Sigma^2)$ to $\mathcal{O}(N \cdot \Sigma)$ time and $\mathcal{O}(\Sigma)$ space.
### Pattern N: 1D Directional Coverage DP with Overlapping Segment Bounding
When selecting 1D directional actions (e.g. shooting left/right with obstacles):
1. **Spatial Ordering**: Sort all active agents and static targets along the 1D axis.
2. **State Definition**: Let `dp[0]` and `dp[1]` track the maximum covered targets up to agent $i$ with agent $i$ acting LEFT vs RIGHT.
3. **Overlapping Gap Bounding**: If agent $i-1$ shoots RIGHT and agent $i$ shoots LEFT into the shared interval $(r_{i-1}, r_i)$, their union coverage cannot exceed the total targets present in that interval:
### Pattern O: Suffix LCP Matrix Reconstruction & Bottom-Up DP Validation
When reconstructing strings from Longest Common Prefix (LCP) relation matrices:
1. **Character Propagation**: If $LCP[i][j] > 0$, characters at $i$ and $j$ must be equal ($word[i] == word[j]$). Greedily assign the lowest available letter from `'a'` to `'z'`.
2. **Component Bounds**: If the number of disjoint equivalence classes exceeds 26, the configuration is impossible.
3. **Bottom-Up DP Verification**: Validate the reconstructed candidate using the standard suffix recurrence:
   $$dp[i][j] = (word[i] == word[j]) \, ? \, (1 + dp[i+1][j+1]) : 0$$
   Confirm $dp[i][j] == LCP[i][j]$ for all $0 \le i, j < N$ in $\mathcal{O}(N^2)$ time.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **State Initialization / Infinity Bounds**: When finding minimums, initialize with a sentinel value (e.g. `amount + 1` or `1e9`) instead of `INT_MAX` to avoid integer overflow during additions like `1 + dp[i - coin]`.
2. **0/1 Knapsack Order**: In 1D space-optimized 0/1 knapsack, traverse capacities backwards (`for (int w = W; w >= weight; --w)`) to avoid reusing the same item.
3. **Off-by-One in DP Table Sizes**: Allocate size `N + 1` when `dp[0]` represents the empty string/prefix.
4. **Unreachable Cells in Multi-Criteria DP**: Guard against propagating from unreachable cells (e.g. `score == -1`); skip them when computing neighbor transitions.
5. **Matrix Multiplication Cache Ordering**: Always use $(i, k, j)$ loop order with `if (A[i][k] == 0) continue;` to maximize L1/L2 cache hits.
6. **Digit DP Leading Zero Mapping**: Map uninitialized digits ($-1$) to index $0$ in fixed memoization tables, or leave them uncached until the first non-zero digit is placed.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 1301 | [Number of Paths with Max Score](../solutions/1301-number-of-paths-with-max-score/README.md) | `Hard` | $\mathcal{O}(N^2)$ | $\mathcal{O}(N^2)$ | [C++](../solutions/1301-number-of-paths-with-max-score/solution.cpp) |
| 1320 | [Minimum Distance to Type a Word Using Two Fingers](../solutions/1320-minimum-distance-to-type-a-word-using-two-fingers/README.md) | `Hard` | $\mathcal{O}(N \cdot \Sigma)$ | $\mathcal{O}(\Sigma)$ | [C++](../solutions/1320-minimum-distance-to-type-a-word-using-two-fingers/solution.cpp) |
| 1340 | [Jump Game V](../solutions/1340-jump-game-v/README.md) | `Hard` | $\mathcal{O}(N \cdot D)$ | $\mathcal{O}(N)$ | [C++](../solutions/1340-jump-game-v/solution.cpp) |
| 1406 | [Stone Game III](../solutions/1406-stone-game-iii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/1406-stone-game-iii/solution.cpp) |
| 2463 | [Minimum Total Distance Traveled](../solutions/2463-minimum-total-distance-traveled/README.md) | `Hard` | $\mathcal{O}(M \cdot N \cdot \min(N, \text{limit}))$ | $\mathcal{O}(N)$ | [C++](../solutions/2463-minimum-total-distance-traveled/solution.cpp) |
| 2573 | [Find the String with LCP](../solutions/2573-find-the-string-with-lcp/README.md) | `Hard` | $\mathcal{O}(N^2)$ | $\mathcal{O}(N^2)$ | [C++](../solutions/2573-find-the-string-with-lcp/solution.cpp) |
| 3225 | [Maximum Score From Grid Operations](../solutions/3225-maximum-score-from-grid-operations/README.md) | `Hard` | $\mathcal{O}(N^3)$ | $\mathcal{O}(N^2)$ | [C++](../solutions/3225-maximum-score-from-grid-operations/solution.cpp) |
| 3336 | [Find the Number of Subsequences With Equal GCD](../solutions/3336-find-the-number-of-subsequences-with-equal-gcd/README.md) | `Hard` | $\mathcal{O}(N \cdot M^2)$ | $\mathcal{O}(M^2)$ | [C++](../solutions/3336-find-the-number-of-subsequences-with-equal-gcd/solution.cpp) |
| 3661 | [Maximum Walls Destroyed by Robots](../solutions/3661-maximum-walls-destroyed-by-robots/README.md) | `Hard` | $\mathcal{O}((N + M) \log M + N \log N)$ | $\mathcal{O}(N)$ | [C++](../solutions/3661-maximum-walls-destroyed-by-robots/solution.cpp) |
| 3699 | [Number of ZigZag Arrays I](../solutions/3699-number-of-zigzag-arrays-i/README.md) | `Hard` | $\mathcal{O}(N \cdot M)$ | $\mathcal{O}(M)$ | [C++](../solutions/3699-number-of-zigzag-arrays-i/solution.cpp) |
| 3700 | [Number of ZigZag Arrays II](../solutions/3700-number-of-zigzag-arrays-ii/README.md) | `Hard` | $\mathcal{O}((2M)^3 \log N)$ | $\mathcal{O}((2M)^2)$ | [C++](../solutions/3700-number-of-zigzag-arrays-ii/solution.cpp) |
| 3753 | [Total Waviness of Numbers in Range II](../solutions/3753-total-waviness-of-numbers-in-range-ii/README.md) | `Hard` | $\mathcal{O}(D^3 \log_{10}(num_2))$ | $\mathcal{O}(D^2 \log_{10}(num_2))$ | [C++](../solutions/3753-total-waviness-of-numbers-in-range-ii/solution.cpp) |






