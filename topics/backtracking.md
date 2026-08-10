# 🔄 Backtracking

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Backtracking and Exhaustive State Space Search.

---

## 📖 1. Core Theory & Fundamentals

Backtracking is a systematic method for exploring all potential configurations of a search space.
- It builds candidates incrementally, and abandons a candidate ("backtracks") as soon as it determines that the candidate cannot lead to a valid solution.
- **Classic Complexity**: Typically exponential $\mathcal{O}(2^N)$ or factorial $\mathcal{O}(N!)$.

### General Backtracking Blueprint
```cpp
void backtrack(State& state, Choices& choices, vector<Result>& results) {
    if (isGoal(state)) {
        results.push_back(format(state));
        return;
    }
    for (auto& choice : getAvailableChoices(choices, state)) {
        if (!isValid(choice, state)) continue; // Pruning
        makeChoice(state, choice);
        backtrack(state, choices, results);
        undoChoice(state, choice);             // Backtrack
    }
}
```

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Subsets (Power Set)
```cpp
void generateSubsets(int start, vector<int>& nums, vector<int>& current, vector<vector<int>>& result) {
    result.push_back(current);
    for (size_t i = start; i < nums.size(); ++i) {
        current.push_back(nums[i]);
        generateSubsets(i + 1, nums, current, result);
        current.pop_back(); // Backtrack
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> current;
    generateSubsets(0, nums, current, result);
    return result;
}
```

### Pattern B: Combinations with Duplicates (Subsets II / Combination Sum II)
Sort first and prune adjacent duplicates at the same recursion depth.
```cpp
void backtrack(int start, int target, vector<int>& candidates, vector<int>& curr, vector<vector<int>>& res) {
    if (target == 0) {
        res.push_back(curr);
        return;
    }
    for (size_t i = start; i < candidates.size(); ++i) {
        if (candidates[i] > target) break; // Prune branch
        if (i > static_cast<size_t>(start) && candidates[i] == candidates[i - 1]) continue; // Skip duplicates
        curr.push_back(candidates[i]);
        backtrack(i + 1, target - candidates[i], candidates, curr, res);
        curr.pop_back(); // Backtrack
    }
}
```

### Pattern C: Permutations
```cpp
void generatePermutations(vector<int>& nums, vector<bool>& used, vector<int>& curr, vector<vector<int>>& res) {
    if (curr.size() == nums.size()) {
        res.push_back(curr);
        return;
    }
    for (size_t i = 0; i < nums.size(); ++i) {
        if (used[i]) continue;
        used[i] = true;
        curr.push_back(nums[i]);
        generatePermutations(nums, used, curr, res);
        curr.pop_back();
        used[i] = false;
    }
}
```

### Pattern D: Constraint Satisfaction with MRV & Bitmasks (Sudoku Solver)
When solving exact constraint grid problems:
1. **Bitmask Lookup**: Maintain bitmasks for each row, column, and subgrid to query candidate validity in $\mathcal{O}(1)$.
2. **Minimum Remaining Values (MRV)**: At each step, select the unassigned cell with the fewest available candidate options (`__builtin_popcount`). This drastically reduces the branching factor.
3. **Fail-Fast Pruning**: If any empty cell has 0 available candidates, immediately backtrack.

```cpp
bool solveSudoku(vector<vector<char>>& board, int rowMask[9], int colMask[9], int boxMask[9]) {
    int minChoices = 10, bestR = -1, bestC = -1, bestCand = 0;

    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] == '.') {
                int used = rowMask[r] | colMask[c] | boxMask[(r / 3) * 3 + (c / 3)];
                int cand = (~used) & 0x1FF;
                int count = __builtin_popcount(cand);
                if (count == 0) return false;
                if (count < minChoices) {
                    minChoices = count;
                    bestR = r; bestC = c; bestCand = cand;
                    if (count == 1) break;
                }
            }
        }
        if (minChoices == 1) break;
    }
    if (bestR == -1) return true; // Solved

    int b = (bestR / 3) * 3 + (bestC / 3);
    int cand = bestCand;
    while (cand > 0) {
        int lsb = cand & -cand;
        int digit = __builtin_ctz(lsb);
        board[bestR][bestC] = '1' + digit;
        rowMask[bestR] |= lsb; colMask[bestC] |= lsb; boxMask[b] |= lsb;

        if (solveSudoku(board, rowMask, colMask, boxMask)) return true;

        board[bestR][bestC] = '.';
        rowMask[bestR] ^= lsb; colMask[bestC] ^= lsb; boxMask[b] ^= lsb;
        cand -= lsb;
    }
    return false;
}
```

### Pattern E: Diagonal Bitmask Tracking (N-Queens)
Track safe queen placements across columns, main diagonals ($r - c + n - 1$), and anti-diagonals ($r + c$) via integer bitmasks in $\mathcal{O}(1)$ time:
```cpp
void solveNQueens(int r, int n, int cols, int diag1, int diag2, vector<string>& board, vector<vector<string>>& res) {
    if (r == n) {
        res.push_back(board);
        return;
    }
    for (int c = 0; c < n; ++c) {
        int d1 = r - c + n - 1;
        int d2 = r + c;
        if (!(cols & (1 << c)) && !(diag1 & (1 << d1)) && !(diag2 & (1 << d2))) {
            board[r][c] = 'Q';
            solveNQueens(r + 1, n, cols | (1 << c), diag1 | (1 << d1), diag2 | (1 << d2), board, res);
            board[r][c] = '.';
        }
    }
}
```

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **State Mutation Without Restoration**: Always ensure every `push_back()` is symmetrically matched with a `pop_back()`.
2. **Duplicate Combinations**: When the input contains duplicates, **always sort the input array first** and use `if (i > start && nums[i] == nums[i-1]) continue;`.
3. **Deep Recursion Limit**: Ensure base cases terminate recursion to prevent stack overflows.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 37 | [Sudoku Solver](../solutions/0037-sudoku-solver/README.md) | `Hard` | $\mathcal{O}(9^M)$ (MRV pruned) | $\mathcal{O}(1)$ | [C++](../solutions/0037-sudoku-solver/solution.cpp) |
| 51 | [N-Queens](../solutions/0051-n-queens/README.md) | `Hard` | $\mathcal{O}(N!)$ | $\mathcal{O}(N^2)$ | [C++](../solutions/0051-n-queens/solution.cpp) |


