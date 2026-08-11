# 💰 Greedy Algorithms

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Greedy Algorithms.

---

## 📖 1. Core Theory & Fundamentals

A Greedy Algorithm builds up a solution piece by piece, always choosing the next piece that offers the most immediate/local benefit without reconsidering past choices.
- **Greedy Choice Property**: A globally optimal solution can be reached by making locally optimal decisions.
- **Optimal Substructure**: An optimal solution to the problem contains optimal solutions to its subproblems.

### Proving Correctness
1. **Exchange Argument**: Show that any optimal solution can be gradually transformed into the greedy solution without worsening its quality.
2. **Greedy Stays Ahead**: Show that at every intermediate step, the greedy solution's progress is at least as good as any alternative.

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Jump Game / Reachability
```cpp
// Jump Game: Can you reach the last index?
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    int n = nums.size();

    for (int i = 0; i < n; ++i) {
        if (i > maxReach) return false; // Cannot reach this index
        maxReach = max(maxReach, i + nums[i]);
        if (maxReach >= n - 1) return true;
    }
    return true;
}
```

### Pattern B: Gas Station / Circular Circuit
```cpp
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int totalTank = 0;
    int currentTank = 0;
    int startingStation = 0;

    for (size_t i = 0; i < gas.size(); ++i) {
        int diff = gas[i] - cost[i];
        totalTank += diff;
        currentTank += diff;

        if (currentTank < 0) {
            // Cannot start from any station up to i
            startingStation = i + 1;
            currentTank = 0;
        }
    }
    return totalTank >= 0 ? startingStation : -1;
}
```

### Pattern C: Activity Selection / Minimum Intervals
```cpp
// Non-overlapping intervals: Max non-overlapping intervals = Min removals
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    // Sort by end time
    sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
        return a[1] < b[1];
    });

    int count = 0;
    int prevEnd = intervals[0][1];

    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] < prevEnd) {
            count++; // Overlap -> remove current
        } else {
            prevEnd = intervals[i][1];
        }
    }
    return count;
}
```

### Pattern D: Prefix Matching with Greedy Suffix Reconstruction
Used when finding the smallest valid sequence/number $\ge \text{num}$ subject to global multiplicative/additive constraints (e.g. LeetCode 3348).
1. Match the longest valid prefix of `num` from right to left.
2. Increment the pivot digit $D > \text{num}[i]$.
3. Greedily construct the lexicographically smallest valid suffix of remaining length $L$ by selecting the smallest feasible digit $d \in [1, 9]$ at each step.

### Pattern E: Two-Pass Constraint Relaxation & Triangular Peak Optimization
When positions must satisfy Lipschitz/slope constraints (e.g. $|h_i - h_{i+1}| \le 1$) alongside discrete upper bounds:
1. Sort restrictions by index and add boundary conditions $(1, 0)$ and $(n, n - 1)$.
2. **Left-to-Right Pass**: Propagate growth limits forward: $h_i = \min(h_i, h_{i-1} + (x_i - x_{i-1}))$.
3. **Right-to-Left Pass**: Propagate growth limits backward: $h_i = \min(h_i, h_{i+1} + (x_{i+1} - x_i))$.
4. **Triangular Peak**: Between adjacent tight bounds $(x_1, h_1)$ and $(x_2, h_2)$, the peak height is $\lfloor \frac{(x_2 - x_1) + h_1 + h_2}{2} \rfloor$.

### Pattern F: Exchange Argument for Energy/Buffer Preservation
When tasks require a minimum initial threshold $minimum_i$ and consume $actual_i$:
1. Use an exchange argument on adjacent tasks $A$ and $B$: doing $A$ before $B$ is better if and only if $(minimum_A - actual_A) \ge (minimum_B - actual_B)$.
2. Sort tasks in descending order of $(minimum_i - actual_i)$.
### Pattern G: Constrained String Generation with Priority Placement & Rightmost Breaking
When constructing a lexicographically minimal string satisfying equality and inequality substring constraints:
1. **Mandatory Placements**: Fix all mandatory equality constraints ('T'). Contradictions immediately imply infeasibility.
2. **Minimal Default Fill**: Populate all unconstrained positions with the minimal character (`'a'`).
3. **Rightmost Breaking**: For any violated inequality constraint ('F') where a substring matches the forbidden pattern, break the match by modifying the rightmost unconstrained position in that window to the next available character (`'b'`), minimizing lexicographical penalty.
4. **Validation**: Run a final verification pass to ensure no later modifications violated earlier constraints.

### Pattern H: Greedy Line Packing & Balanced Space Apportionment
When formatting text into justified fixed-width lines:
1. **Greedy Fitting**: Pack as many words as fit within `maxWidth` such that word lengths plus mandatory single-space separators $\le \text{maxWidth}$.
2. **Left-Justification Exception**: If the line contains a single word or is the last line of text, space words with 1 space and right-pad remaining spaces.
### Pattern I: Two-Pass Bidirectional Neighbor Satisfaction
When an element's value must strictly exceed both its left and right neighbors subject to rating inequalities:
1. **Left-to-Right Pass**: Initialize all elements to baseline minimum (e.g. 1) and increment $A[i] = A[i - 1] + 1$ whenever $R[i] > R[i - 1]$.
2. **Right-to-Left Pass**: Update $A[i] = \max(A[i], A[i + 1] + 1)$ whenever $R[i] > R[i + 1]$.
3. The $\max$ operator maintains the previously satisfied left-neighbor condition while strictly enforcing the right-neighbor condition in $\mathcal{O}(N)$ time.

### Pattern J: Greedy Interval Expansion & Continuous Reachability Range
When extending the contiguous range of formable subset sums $[1, \text{miss} - 1]$ to cover $[1, n]$:
1. **Invariant**: Maintain that all integers in $[1, \text{miss} - 1]$ can be formed.
2. **Expansion with Existing Elements**: If the next sorted element satisfies $\text{nums}[i] \le \text{miss}$, include it to expand reach to $[1, \text{miss} + \text{nums}[i] - 1]$ without gaps ($\text{miss} \gets \text{miss} + \text{nums}[i], i \gets i + 1$).
3. **Greedy Patching on Discontinuity**: If $\text{nums}[i] > \text{miss}$ (or input exhausted), patch $\text{miss}$ itself to double coverage to $[1, 2 \cdot \text{miss} - 1]$ ($\text{miss} \gets 2 \cdot \text{miss}, \text{patches} \gets \text{patches} + 1$).
4. **Complexity**: Since reach doubles on each patch, at most $\mathcal{O}(\log n)$ patches occur $\implies \mathcal{O}(M + \log n)$ time, $\mathcal{O}(1)$ space.

### Pattern K: Multi-Constraint Edit Distance with Priority Deletion Allocation (Strong Password Checker)
When editing a sequence subject to simultaneous length bounds $[L_{\min}, L_{\max}]$, character set coverage, and maximum run limits ($\le 2$):
1. **Regime 1 ($N < L_{\min}$)**: Inserts dominate; each insert simultaneously increases length, supplies missing character categories, and breaks runs $\implies \max(L_{\min} - N, \text{missingTypes})$.
2. **Regime 2 ($L_{\min} \le N \le L_{\max}$)**: Replacements dominate; each replacement simultaneously breaks a run and supplies missing categories $\implies \max(\sum \lfloor L_i / 3 \rfloor, \text{missingTypes})$.
3. **Regime 3 ($N > L_{\max}$)**: $D = N - L_{\max}$ deletions are mandatory. Greedily prioritize deletions that save the most replacements per unit cost:
   - $L_i \pmod 3 == 0$: 1 deletion saves 1 replacement.
   - $L_i \pmod 3 == 1$: 2 deletions save 1 replacement.
   - $L_i \ge 3$: 3 deletions save 1 replacement.
   - Final cost: $D + \max(\text{remainingReplacements}, \text{missingTypes})$.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Greedy Fallacy**: Ensure greedy choice property actually holds (e.g. standard 0/1 knapsack cannot be solved greedily, it requires DP).
2. **Sorting Criteria**: Choosing whether to sort by start time, end time, or value ratio is crucial. Always verify with an exchange argument.
3. **Empty Input / Single Element**: Always verify behavior for $N = 0$ or $N = 1$.
4. **Unrelaxed Restrictions**: Calculating peaks on loose/unrelaxed restrictions overestimates peak height. Always perform two-pass relaxation first.
5. **64-bit Overflow on Reach Range**: Continuous interval expansion ($\text{miss} \times 2$) can exceed $2^{31}-1$; always store `miss` as `long long`.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 68 | [Text Justification](../solutions/0068-text-justification/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(\text{maxWidth})$ | [C++](../solutions/0068-text-justification/solution.cpp) |
| 135 | [Candy](../solutions/0135-candy/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0135-candy/solution.cpp) |
| 330 | [Patching Array](../solutions/0330-patching-array/README.md) | `Hard` | $\mathcal{O}(M + \log N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0330-patching-array/solution.cpp) |
| 420 | [Strong Password Checker](../solutions/0420-strong-password-checker/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0420-strong-password-checker/solution.cpp) |
| 1665 | [Minimum Initial Energy to Finish Tasks](../solutions/1665-minimum-initial-energy-to-finish-tasks/README.md) | `Hard` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(1)$ | [C++](../solutions/1665-minimum-initial-energy-to-finish-tasks/solution.cpp) |
| 1840 | [Maximum Building Height](../solutions/1840-maximum-building-height/README.md) | `Hard` | $\mathcal{O}(R \log R)$ | $\mathcal{O}(R)$ | [C++](../solutions/1840-maximum-building-height/solution.cpp) |
| 3348 | [Smallest Divisible Digit Product II](../solutions/3348-smallest-divisible-digit-product-ii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/3348-smallest-divisible-digit-product-ii/solution.cpp) |
| 3474 | [Lexicographically Smallest Generated String](../solutions/3474-lexicographically-smallest-generated-string/README.md) | `Hard` | $\mathcal{O}(N \cdot M)$ | $\mathcal{O}(N + M)$ | [C++](../solutions/3474-lexicographically-smallest-generated-string/solution.cpp) |






