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

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **State Mutation Without Restoration**: Always ensure every `push_back()` is symmetrically matched with a `pop_back()`.
2. **Duplicate Combinations**: When the input contains duplicates, **always sort the input array first** and use `if (i > start && nums[i] == nums[i-1]) continue;`.
3. **Deep Recursion Limit**: Ensure base cases terminate recursion to prevent stack overflows.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
<!-- Problems will be added here -->
