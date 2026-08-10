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

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Greedy Fallacy**: Ensure greedy choice property actually holds (e.g. standard 0/1 knapsack cannot be solved greedily, it requires DP).
2. **Sorting Criteria**: Choosing whether to sort by start time, end time, or value ratio is crucial.
3. **Empty Input / Single Element**: Always verify behavior for $N = 0$ or $N = 1$.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 3348 | [Smallest Divisible Digit Product II](../solutions/3348-smallest-divisible-digit-product-ii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/3348-smallest-divisible-digit-product-ii/solution.cpp) |

