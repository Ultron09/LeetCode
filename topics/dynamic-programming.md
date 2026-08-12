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
### Pattern P: Regular Expression Matching & Wildcard Transition DP
When matching text $s$ against pattern $p$ with wildcards (`.` and `*`):
1. **State Definition**: $dp[i][j]$ indicates whether $s[0..i-1]$ matches $p[0..j-1]$.
2. **Empty String Base Initialization**: If $p[j-1] == '*' $, $dp[0][j] = dp[0][j-2]$ (matching 0 instances).
3. **Transitions**:
   - Single character match (`p[j-1] == s[i-1]` or `p[j-1] == '.'`): $dp[i][j] = dp[i-1][j-1]$.
   - Star wildcard (`p[j-1] == '*'`):
     - Zero match of $p[j-2]$: $dp[i][j] = dp[i][j-2]$.
     - One or more match: If $p[j-2]$ matches $s[i-1]$, $dp[i][j] = dp[i][j] \lor dp[i-1][j]$.

### Pattern R: Reverse Grid DP for Survival/Health Optimization (Dungeon Game)
When finding the minimum initial resource needed to traverse a grid without ever hitting $\le 0$:
1. Forward DP fails because maximizing health does not guarantee surviving early dips.
2. Define $dp[i][j]$ as the minimum health required *before* entering cell $(i, j)$.
3. Recurrence working backwards from bottom-right $(M-1, N-1)$ to $(0, 0)$:
   $$dp[i][j] = \max(1, \min(dp[i+1][j], dp[i][j+1]) - \text{grid}[i][j])$$
4. The $\max(1, \cdot)$ operator guarantees non-zero survival at every step. Compress to 1D rolling array of size $N+1$ for $\mathcal{O}(N)$ space.

### Pattern S: Memoized DFS on Grid DAG (Longest Monotonic Path)
When traversing a grid where step transitions enforce strict inequalities ($M[nr][nc] > M[r][c]$):
1. **DAG Property**: Strict monotonicity guarantees acyclicity; an explicit `visited` cycle set is unnecessary.
2. **Top-Down Memoization**: Define $DP[r][c]$ as the longest strictly increasing path starting from cell $(r, c)$.
3. **State Transition**:
   $$DP[r][c] = 1 + \max_{(nr, nc) \in \text{adj}(r, c), M[nr][nc] > M[r][c]} DP[nr][nc]$$
### Pattern T: Multi-Dimensional LIS via Sorting + Dimension Reduction
When finding the longest chain where **all** dimensions are strictly increasing (e.g. Russian doll nesting):
1. **Sort by Primary Dimension Ascending**: Guarantees monotonicity in the first coordinate.
2. **Break Ties with Reverse Sort on Secondary Dimension**: For equal primary keys, sort the secondary dimension **descending**. This prevents `lower_bound` in the patience-sort LIS from selecting two elements with the same primary key.
3. **Patience-Sort LIS on Reduced Dimension**: Extract the secondary dimension and compute the LIS in $\mathcal{O}(N \log N)$ using `lower_bound` on a `tails` array.
4. **Generalizes to $k$ Dimensions**: For $k > 2$, sort by the first $k-1$ dimensions and apply patience-sort on the last, though additional care is needed for ties in intermediate dimensions.

### Pattern U: State-Bounded Forward Jump DP (Position-Index Dual Mapping & Velocity State)
When simulating forward movement where the next jump step depends on previous velocity $k \in \{k-1, k, k+1\}$:
1. **Mathematical Bound on Velocity**: Prove that after $i$ hops, maximum incoming jump size $k \le i < N$, strictly bounding the 2D state space to $N \times N$.
2. **Dual Spatial-Index Mapping**: Use a pre-allocated hash map or binary search (`std::lower_bound`) to map coordinate positions $\text{stones}[i] + d$ to array indices $j$ in $\mathcal{O}(1)$ or $\mathcal{O}(\log N)$.
3. **Forward Transition with Early Exit**:
   $$\text{dp}[j][d] = \text{true} \quad \forall d \in \{k-1, k, k+1\}, \quad d > 0, \quad \text{stones}[j] = \text{stones}[i] + d$$
   Immediately exit with `true` as soon as $j == N - 1$.
4. **Flat Contiguous Storage**: Allocate a 1D `vector<uint8_t> dp(N * N, 0)` for zero container allocation overhead and optimal CPU cache locality.

### Pattern V: Arithmetic Subsequence DP (Difference-Map State Indexing)
When counting subsequences with constant step differences:
1. **State Definition**: Let `dp[i][d]` be the number of arithmetic subsequences of length $\ge 2$ ending at index $i$ with common difference $d$.
2. **Transition**: For each pair $(j, i)$ with $j < i$ and difference $d = \text{nums}[i] - \text{nums}[j]$:
   - Extended subsequences of length $\ge 3$: `totalCount += dp[j][d]`.
   - Update ending count at $i$: `dp[i][d] += dp[j][d] + 1` (where $+1$ accounts for the 2-element base pair $(\text{nums}[j], \text{nums}[i])$).
3. **Difference Overflow Protection**: Always compute $d$ using `static_cast<long long>` to avoid 32-bit signed integer overflow.
4. **Complexity**: $\mathcal{O}(N^2)$ time and $\mathcal{O}(N^2)$ space.

### Pattern W: Pigeonhole Cycle Detection & Fast-Forwarding (String Repetition Matching)
When matching a target string $s_2$ as a subsequence inside an $n_1$-times repeated source block $s_1$:
1. **Periodic State Representation**: The matching index `s2Idx` $\in [0, |s_2|-1]$ at the boundary of each $s_1$ block fully captures the continuation state.
2. **Pigeonhole Cycle Bound**: Because `s2Idx` has only $|s_2|$ distinct values, a repeat state must occur within $|s_2| + 1$ iterations of $s_1$.
3. **Cycle Jump**:
   - Compute cycle periods $\Delta s_1 = \text{currS1} - \text{prevS1}$ and $\Delta s_2 = \text{currS2} - \text{prevS2}$.
   - Fast-forward $s_1$ and $s_2$ counts by $\lfloor (n_1 - \text{currS1}) / \Delta s_1 \rfloor$.
   - Execute the remaining tail iterations ($< |s_2|$) linearly.
4. **Complexity**: $\mathcal{O}(|s_1| \cdot |s_2|)$ time and $\mathcal{O}(|s_2|)$ space.

### Pattern X: Length-Ordered Incremental Vocabulary Word Break DP
When identifying composite/concatenated strings formed by at least two shorter elements in a dictionary:
1. **Length-Ascending Sort**: Sort dictionary words by length so all candidate sub-words are evaluated and cached before evaluating longer words.
2. **Word Break DP Check**: For word $W$ of length $L$, define `dp[i]` = whether prefix $W[0 \dots i-1]$ can be formed by cached words:
   $$\text{dp}[i] = \text{true} \quad \text{if } \exists j < i : \text{dp}[j] \land W[j \dots i-1] \in \text{wordSet}$$
3. **Incremental Insertion**: If `dp[L] == true`, mark $W$ as concatenated. Always insert $W$ into `wordSet` afterward.
4. **Complexity**: $\mathcal{O}(N \log N + N \cdot L^3)$ time, $\mathcal{O}(\sum |W_i|)$ space.

### Pattern Y: Circular Ring Metric Multi-Stage Transition DP (Freedom Trail)
When finding the minimum steps to sequence through an alphabet on a circular dial:
1. **Circular Distance Metric**: For positions $i, j$ on a dial of length $R$, $\text{dist}(i, j) = \min(|i - j|, R - |i - j|)$.
2. **State Representation**: `dp[pos]` = minimum accumulated rotations + button presses to spell the prefix of `key` ending at dial index `pos`.
3. **Stage Transitions**: For each character in `key`, transition from all previous valid positions to each index `nxt` containing the target character:
   $$\text{next\_dp}[\text{nxt}] = \min_{\text{prev}} (\text{dp}[\text{prev}] + \text{dist}(\text{prev}, \text{nxt}) + 1)$$
4. **Complexity**: $\mathcal{O}(K \cdot R^2)$ time and $\mathcal{O}(R)$ space.

### Pattern Z: Interval DP with Trailing Context Dimension (Remove Boxes)
When elimination games allow non-adjacent identical elements to concatenate across erased subsegments:
1. **Context Augmented State**: $\text{dp}[l][r][k]$ = max points from $\text{boxes}[l \dots r]$ with $k$ identical predecessor elements attached to $\text{boxes}[l]$.
2. **Contiguous Compression**: Advance $l$ and increase $k$ while $\text{boxes}[l+1] == \text{boxes}[l]$.
3. **Branching Transitions**:
   - *Option 1 (Immediate Removal)*: $(k + 1)^2 + \text{dp}(l + 1, r, 0)$.
   - *Option 2 (Subsegment Clearing for Merge)*: For $m \in [l + 1, r]$ where $\text{boxes}[m] == \text{boxes}[l]$ and $\text{boxes}[m - 1] \ne \text{boxes}[l]$:
     $$\text{dp}(l + 1, m - 1, 0) + \text{dp}(m, r, k + 1)$$
4. **Complexity**: $\mathcal{O}(N^4)$ worst-case, $\mathcal{O}(N^3)$ average with memoization, $\mathcal{O}(N^3)$ space.

### Pattern AA: Finite State Space Linear Recurrence DP (Student Attendance Record)
When sequencing constrained alphabets where legality depends only on small discrete counters (e.g. total absences $a \in \{0, 1\}$, consecutive lates $l \in \{0, 1, 2\}$):
1. **FSM State Space**: Encode valid suffixes/prefixes with a fixed tuple state $(a, l)$, yielding $|S| = 2 \times 3 = 6$ total states.
2. **Transition Rules**:
   - `'P'`: $(a, l) \to (a, 0)$
   - `'A'`: $(0, l) \to (1, 0)$
   - `'L'`: $(a, l) \to (a, l + 1)$ for $l < 2$
3. **Complexity**: $\mathcal{O}(N)$ time and $\mathcal{O}(1)$ space using rolling array, with optional $\mathcal{O}(|S|^3 \log N)$ matrix exponentiation for large $N$.

### Pattern AB: Sliding Window / Prefix-Sum Accelerated DP Transitions (K Inverse Pairs Array)
When DP transitions involve contiguous range sums of the previous state row $\text{dp}[i][j] = \sum_{p=0}^{\min(j, i-1)} \text{dp}[i-1][j - p]$:
1. **Algebraic Difference**:
   $$\text{dp}[i][j] = \text{dp}[i][j-1] + \text{dp}[i-1][j] - \text{dp}[i-1][j-i] \quad (j \ge i)$$
2. **Complexity Reduction**: Reduces naive $\mathcal{O}(N \cdot K \cdot \min(N, K))$ combinatorial summations to $\mathcal{O}(N \cdot K)$ overall time.
3. **Space Optimization**: 1D rolling array reduces space from $\mathcal{O}(N \cdot K)$ to $\mathcal{O}(K)$.

### Pattern AC: Multi-Branch Wildcard Second-Order Linear DP (Decode Ways II)
When decoding sequential encodings containing wildcard tokens (`*` expanding into $[1 \dots 9]$):
1. **Recurrence Decomposition**:
   $$\text{dp}[i] = (w_1(s[i-1]) \cdot \text{dp}[i-1] + w_2(s[i-2], s[i-1]) \cdot \text{dp}[i-2]) \pmod{10^9 + 7}$$
2. **Exhaustive Multipliers**:
   - Single-digit $w_1$: `*` $\to 9$, `[1..9]` $\to 1$, `0` $\to 0$.
   - Two-digit $w_2$: `**` $\to 15$, `*d` $\to (d \le '6' ? 2 : 1)$, `1*` $\to 9$, `2*` $\to 6$, valid digits $\to 1$, else $0$.
3. **Space Optimization**: $\mathcal{O}(N)$ time with $\mathcal{O}(1)$ space using two rolling variables.

### Pattern AD: Interval DP with Overwrite Optimization (Strange Printer)
When finding the minimum turns/operations to generate a target string where operations can overwrite earlier spans:
1. **Deduplication Preprocessing**: Compress contiguous runs of identical characters (`compact = dedup(s)`).
2. **Base Transition**: $\text{dp}[i][j] = \text{dp}[i][j - 1] + 1$.
3. **Overwrite Matching**: If $s[k] == s[j]$ for $k \in [i, j-1]$, character $s[j]$ can be printed simultaneously with $s[k]$ without adding turns:
   $$\text{dp}[i][j] = \min_{k=i}^{j-1} (\text{dp}[i][k] + (k + 1 \le j - 1 ? \text{dp}[k + 1][j - 1] : 0)) \quad (s[k] == s[j])$$
4. **Complexity**: $\mathcal{O}(N^3)$ time and $\mathcal{O}(N^2)$ space.

### Pattern AE: Anchor Decomposition with Prefix & Suffix Optimal Subarray DP (Maximum Sum of 3 Non-Overlapping Subarrays)
When finding $k$ non-overlapping fixed-length intervals maximizing total value:
1. **Window Sum Precomputation**: Compute length-$k$ window sums $\text{windowSum}[i]$ in $\mathcal{O}(N)$ time.
2. **Left/Right Optimal Indexes**:
   - `leftMax[i]` = index in $[0, i]$ with maximum sum (use strict `>` to maintain smallest index on ties).
   - `rightMax[i]` = index in $[i, M - 1]$ with maximum sum (use non-strict `>=` to maintain earlier index on ties).
3. **Anchor Middle Window Sweep**: For each valid middle start index $j \in [k, M - 1 - k]$, query $l = \text{leftMax}[j - k]$ and $r = \text{rightMax}[j + k]$.
4. **Complexity**: $\mathcal{O}(N)$ time and $\mathcal{O}(N)$ space.

### Pattern AF: Bitmask DP Subset Cover (Stickers to Spell Word)
When a target string of length $T \le 15$–$20$ must be covered using items from a collection (stickers, tiles, etc.):
1. **State**: $dp[\text{mask}]$ = min items to cover target positions indicated by set bits in `mask`. Total states: $2^T$.
2. **Anchor Pruning**: For each state, find the **lowest uncovered bit position** and only try items that contain that character. This enforces a canonical ordering and prunes exponentially.
3. **Greedy Matching**: For each qualifying item, iterate through target positions left-to-right. For each uncovered position, if the item has a remaining copy of that letter, mark it covered and decrement the item's available count.
4. **Transition**: $dp[\text{newMask}] = \min(dp[\text{newMask}], dp[\text{mask}] + 1)$.
5. **Impossibility**: If $dp[2^T - 1]$ stays $\infty$, return $-1$.
6. **Complexity**: $\mathcal{O}(2^T \cdot N \cdot T)$ time, $\mathcal{O}(2^T)$ space.

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
| 10 | [Regular Expression Matching](../solutions/0010-regular-expression-matching/README.md) | `Hard` | $\mathcal{O}(M \cdot N)$ | $\mathcal{O}(M \cdot N)$ | [C++](../solutions/0010-regular-expression-matching/solution.cpp) |
| 44 | [Wildcard Matching](../solutions/0044-wildcard-matching/README.md) | `Hard` | $\mathcal{O}(M \cdot N)$ worst / $\mathcal{O}(M + N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0044-wildcard-matching/solution.cpp) |
| 87 | [Scramble String](../solutions/0087-scramble-string/README.md) | `Hard` | $\mathcal{O}(N^4)$ | $\mathcal{O}(N^3)$ | [C++](../solutions/0087-scramble-string/solution.cpp) |
| 115 | [Distinct Subsequences](../solutions/0115-distinct-subsequences/README.md) | `Hard` | $\mathcal{O}(M \cdot N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0115-distinct-subsequences/solution.cpp) |
| 123 | [Best Time to Buy and Sell Stock III](../solutions/0123-best-time-to-buy-and-sell-stock-iii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0123-best-time-to-buy-and-sell-stock-iii/solution.cpp) |
| 132 | [Palindrome Partitioning II](../solutions/0132-palindrome-partitioning-ii/README.md) | `Hard` | $\mathcal{O}(N^2)$ | $\mathcal{O}(N)$ | [C++](../solutions/0132-palindrome-partitioning-ii/solution.cpp) |
| 174 | [Dungeon Game](../solutions/0174-dungeon-game/README.md) | `Hard` | $\mathcal{O}(M \cdot N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0174-dungeon-game/solution.cpp) |
| 188 | [Best Time to Buy and Sell Stock IV](../solutions/0188-best-time-to-buy-and-sell-stock-iv/README.md) | `Hard` | $\mathcal{O}(N \cdot k)$ | $\mathcal{O}(k)$ | [C++](../solutions/0188-best-time-to-buy-and-sell-stock-iv/solution.cpp) |
| 312 | [Burst Balloons](../solutions/0312-burst-balloons/README.md) | `Hard` | $\mathcal{O}(N^3)$ | $\mathcal{O}(N^2)$ | [C++](../solutions/0312-burst-balloons/solution.cpp) |
| 329 | [Longest Increasing Path in a Matrix](../solutions/0329-longest-increasing-path-in-a-matrix/README.md) | `Hard` | $\mathcal{O}(M \cdot N)$ | $\mathcal{O}(M \cdot N)$ | [C++](../solutions/0329-longest-increasing-path-in-a-matrix/solution.cpp) |
| 354 | [Russian Doll Envelopes](../solutions/0354-russian-doll-envelopes/README.md) | `Hard` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0354-russian-doll-envelopes/solution.cpp) |
| 403 | [Frog Jump](../solutions/0403-frog-jump/README.md) | `Hard` | $\mathcal{O}(N^2)$ | $\mathcal{O}(N^2)$ | [C++](../solutions/0403-frog-jump/solution.cpp) |
| 446 | [Arithmetic Slices II - Subsequence](../solutions/0446-arithmetic-slices-ii-subsequence/README.md) | `Hard` | $\mathcal{O}(N^2)$ | $\mathcal{O}(N^2)$ | [C++](../solutions/0446-arithmetic-slices-ii-subsequence/solution.cpp) |
| 466 | [Count The Repetitions](../solutions/0466-count-the-repetitions/README.md) | `Hard` | $\mathcal{O}(\|s_1\| \cdot \|s_2\|)$ | $\mathcal{O}(\|s_2\|)$ | [C++](../solutions/0466-count-the-repetitions/solution.cpp) |
| 472 | [Concatenated Words](../solutions/0472-concatenated-words/README.md) | `Hard` | $\mathcal{O}(N \log N + N \cdot L^3)$ | $\mathcal{O}(\sum \|W_i\|)$ | [C++](../solutions/0472-concatenated-words/solution.cpp) |
| 514 | [Freedom Trail](../solutions/0514-freedom-trail/README.md) | `Hard` | $\mathcal{O}(K \cdot R^2)$ | $\mathcal{O}(R)$ | [C++](../solutions/0514-freedom-trail/solution.cpp) |
| 546 | [Remove Boxes](../solutions/0546-remove-boxes/README.md) | `Hard` | $\mathcal{O}(N^4)$ | $\mathcal{O}(N^3)$ | [C++](../solutions/0546-remove-boxes/solution.cpp) |
| 552 | [Student Attendance Record II](../solutions/0552-student-attendance-record-ii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0552-student-attendance-record-ii/solution.cpp) |
| 629 | [K Inverse Pairs Array](../solutions/0629-k-inverse-pairs-array/README.md) | `Hard` | $\mathcal{O}(N \cdot K)$ | $\mathcal{O}(K)$ | [C++](../solutions/0629-k-inverse-pairs-array/solution.cpp) |
| 639 | [Decode Ways II](../solutions/0639-decode-ways-ii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0639-decode-ways-ii/solution.cpp) |
| 664 | [Strange Printer](../solutions/0664-strange-printer/README.md) | `Hard` | $\mathcal{O}(N^3)$ | $\mathcal{O}(N^2)$ | [C++](../solutions/0664-strange-printer/solution.cpp) |
| 689 | [Maximum Sum of 3 Non-Overlapping Subarrays](../solutions/0689-maximum-sum-of-3-non-overlapping-subarrays/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0689-maximum-sum-of-3-non-overlapping-subarrays/solution.cpp) |
| 691 | [Stickers to Spell Word](../solutions/0691-stickers-to-spell-word/README.md) | `Hard` | $\mathcal{O}(2^T \cdot N \cdot T)$ | $\mathcal{O}(2^T)$ | [C++](../solutions/0691-stickers-to-spell-word/solution.cpp) |
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











