# LeetCode Problem Solving & Knowledge Base Agent Guidelines

This repository is dedicated to solving LeetCode problems systematically, maintaining high-performance C++ solutions, compiling in-depth topic theory and algorithmic notes, and maintaining a cross-linked master index.

---

## 🎯 Primary Responsibilities

Whenever a new LeetCode question or request is received:
1. **Develop Solution**: Write an optimal, production-grade C++ solution in a dedicated problem folder with a comprehensive companion explanation.
2. **Update Topic Theory**: Review and expand the relevant topic documentation in `topics/` with deep algorithmic theory, pattern templates, and problem references.
3. **Synchronize Master Index**: Update both `INDEX.md` and `README.md` with links to the new solution, difficulty, complexities, and topic notes.

---

## 📁 Repository Structure Convention

```
LeetCode/
├── AGENTS.md                   # Operational guidelines & coding rules (this file)
├── .agents/
│   └── AGENTS.md               # Workspace-level agent instructions
├── README.md                   # Repository overview, dashboard, stats, and topic catalog
├── INDEX.md                    # Master problem table with clickable links
├── solutions/                  # Problem solutions organized by ID and slug
│   └── <id>-<slug>/
│       ├── solution.cpp        # Full C++ solution with optimal logic, comments & test runner
│       └── README.md           # Problem details, intuition, approach, complexity, edge cases
└── topics/                     # In-depth algorithmic theory and pattern guides
    ├── arrays-and-hashing.md
    ├── two-pointers.md
    ├── sliding-window.md
    ├── stack-and-queue.md
    ├── binary-search.md
    ├── linked-list.md
    ├── trees.md
    ├── heaps-and-priority-queues.md
    ├── backtracking.md
    ├── graphs.md
    ├── dynamic-programming.md
    ├── greedy.md
    ├── intervals.md
    ├── bit-manipulation.md
    └── math-and-geometry.md
```

---

## 🔄 Step-by-Step Workflow for Handling a Problem

### Step 1: Analyze the Problem
- Extract: Problem Number (`<id>`), Title, Difficulty (`Easy` / `Medium` / `Hard`), Category/Tags, Constraints, and Edge Cases.
- Determine the slug: e.g., `1` + `Two Sum` -> `0001-two-sum` (use 4-digit zero-padded number for consistent sorting).

### Step 2: Create Problem Directory & Solution File
- Create folder: `solutions/<id>-<slug>/` (e.g. `solutions/0001-two-sum/`).
- Create `solutions/<id>-<slug>/solution.cpp` following the [C++ Solution Template](#-c-solution-template).
- Create `solutions/<id>-<slug>/README.md` following the [Problem README Template](#-problem-readme-template).

### Step 3: Update Topic Theory (`topics/<topic>.md`)
- Identify primary topic (and secondary topics if applicable).
- Open the corresponding `topics/<topic>.md` file.
- Add the problem link to the **"Solved Problems"** table in that topic note.
- If the problem introduces a unique pattern, optimization trick, or algorithmic template, document it in the **"Key Patterns & Templates"** section.

### Step 4: Update Master Index (`INDEX.md` & `README.md`)
- Append or update the entry in `INDEX.md` in numerical order:
  `| <id> | [<Title>](solutions/<id>-<slug>/README.md) | <Difficulty> | [<Topic>](topics/<topic>.md) | O(T) | O(S) | [C++](solutions/<id>-<slug>/solution.cpp) |`
- Update the solved statistics counter in `README.md`.

---

## 💻 C++ Solution Template

Each `solution.cpp` must be self-contained, compile cleanly with standard C++17/20, and include a runnable `main()` test harness:

```cpp
/**
 * Problem: <Problem Number>. <Problem Title>
 * Difficulty: <Easy | Medium | Hard>
 * Topics: <Topic 1>, <Topic 2>
 * LeetCode Link: https://leetcode.com/problems/<slug>/
 * 
 * Time Complexity:  O(...) - <Brief reason>
 * Space Complexity: O(...) - <Brief reason>
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    // Implementation with clear variable names and comments
    vector<int> solutionMethod(...) {
        // Core algorithmic logic
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    {
        // Setup inputs
        // auto result = solver.solutionMethod(...);
        // assert(result == expected);
        // cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2 (Edge cases)
    {
        // ...
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
```

---

## 📝 Problem README Template

Each `solutions/<id>-<slug>/README.md` must follow this structure:

```markdown
# [<id>. <Problem Title>](https://leetcode.com/problems/<slug>/)

**Difficulty:** `Easy` | `Medium` | `Hard`  
**Topics:** [Topic 1](../../topics/<topic-1>.md), [Topic 2](../../topics/<topic-2>.md)

---

## 📌 Problem Statement

[Detailed problem description with constraints and examples]

### Example 1:
```
Input: ...
Output: ...
Explanation: ...
```

### Constraints:
- `...`

---

## 💡 Intuition & Approach

1. **Brute Force Idea**: What is the naive approach and why is it suboptimal?
2. **Optimal Strategy**: How does the optimal algorithm work? (e.g. Hash Map, Two Pointers, DP state transitions).
3. **Step-by-step Execution**: Clear logical breakdown.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(...)$ — [Explanation]
- **Space Complexity:** $\mathcal{O}(...)$ — [Explanation]

---

## 🔍 Edge Cases Considered

- Empty / single element inputs.
- Minimum / maximum boundary values.
- Duplicates / negative numbers.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
```

---

## 📚 Topic Notes Standard (`topics/<topic>.md`)

Each topic note must be comprehensive and contain:
1. **Core Theory & Intuition**: Fundamental definitions, memory/time tradeoffs, visualization.
2. **Standard Templates & Code Snippets**: Generic implementations of key algorithms (e.g., binary search template, DFS/BFS framework, sliding window boilerplates).
3. **Pattern Identification**: "How to know when to use this topic" cues in problem statements.
4. **Common Pitfalls & Edge Cases**: Integer overflow, off-by-one errors, cycle detection, iterator invalidation.
5. **Categorized Solved Problems Table**: Links to all solved problems belonging to this topic with difficulty and complexities.

---

## ⚙️ Compilation & Testing Guidelines

To verify and run solutions locally:
```bash
# Compile with C++17, LOCAL_TEST macro, and warnings enabled
g++ -std=c++17 -DLOCAL_TEST -O2 -Wall solutions/<id>-<slug>/solution.cpp -o run_solution.exe

# Run test cases
./run_solution.exe
```
