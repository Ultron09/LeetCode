# 🚀 LeetCode Mastery & Data Structures Repository

Welcome to the **LeetCode Solutions & Algorithm Knowledge Base**. This repository serves as a systematic, high-performance vault of solved LeetCode problems (primarily in modern C++), paired with comprehensive theory notes, pattern guides, complexity breakdowns, and an automated master index.

---

## 🧭 Repository Navigation

- **[📑 Master Problem Index](INDEX.md)**: Searchable table of all solved problems with complexity stats, direct links to solutions, and topic notes.
- **[🤖 Agent Guidelines (AGENTS.md)](AGENTS.md)**: Complete automation rules, C++ template specifications, and update procedures for AI assistants.
- **[📂 Solutions Directory](solutions/)**: Organized by `<problem_id>-<slug>` containing code (`solution.cpp`) and intuition (`README.md`).
- **[📚 Topics Directory](topics/)**: Curated theory, algorithms, patterns, and cheat-sheets for all major DSA categories.

---

## 📊 Solved Problems Tracker

| Total Solved | 🟢 Easy | 🟡 Medium | 🔴 Hard |
| :---: | :---: | :---: | :---: |
| **93** | 0 | 0 | 93 |

---

## 📚 DSA Topic Guides

| Topic | Key Concepts | Solved Count | Link |
| :--- | :--- | :---: | :---: |
| **Arrays & Hashing** | Hash Maps, Hash Sets, Prefix Sums, Kadane's | 8 | [Explore Notes](topics/arrays-and-hashing.md) |
| **Two Pointers** | Opposite Ends, Same Direction, Partitioning | 2 | [Explore Notes](topics/two-pointers.md) |
| **Sliding Window** | Fixed Window, Dynamic Window, Monotonic Queue | 5 | [Explore Notes](topics/sliding-window.md) |
| **Stack & Queue** | Monotonic Stack, Parentheses, Min-Stack, Queues | 7 | [Explore Notes](topics/stack-and-queue.md) |
| **Binary Search** | Classic BS, Search on Answer, Rotated Arrays | 9 | [Explore Notes](topics/binary-search.md) |
| **Linked List** | Fast & Slow Pointers, Reversals, Dummy Nodes | 2 | [Explore Notes](topics/linked-list.md) |
| **Trees & BST** | DFS/BFS Traversals, Lowest Common Ancestor, Tree DP | 4 | [Explore Notes](topics/trees.md) |
| **Heaps / Priority Queue**| Top-K Elements, Two Heaps Pattern, Merge K Lists | 4 | [Explore Notes](topics/heaps-and-priority-queues.md) |
| **Backtracking** | Permutations, Combinations, Subsets, Pruning | 7 | [Explore Notes](topics/backtracking.md) |
| **Graphs** | BFS/DFS, Dijkstra, Topo Sort, Union-Find, Bellman-Ford | 6 | [Explore Notes](topics/graphs.md) |
| **Dynamic Programming** | 1D/2D DP, Knapsack, LCS/LIS, Interval DP, Bitmask DP | 24 | [Explore Notes](topics/dynamic-programming.md) |
| **Greedy** | Activity Selection, Jump Game, Huffman Coding | 7 | [Explore Notes](topics/greedy.md) |
| **Intervals** | Merging Intervals, Insert Intervals, Overlap Checks | 2 | [Explore Notes](topics/intervals.md) |
| **Bit Manipulation** | XOR properties, Bitmasks, Power of 2 checks | 0 | [Explore Notes](topics/bit-manipulation.md) |
| **Math & Geometry** | Sieve of Eratosthenes, GCD/LCM, Fast Exponentiation | 15 | [Explore Notes](topics/math-and-geometry.md) |

---

## 🛠️ How to Compile & Run Solutions Locally

All solutions are written in standard C++17/20 and include built-in test runners in `main()` with assertions guarded by `#ifdef LOCAL_TEST`:

```bash
# Compile locally with g++
g++ -std=c++17 -DLOCAL_TEST -O2 -Wall solutions/<id>-<slug>/solution.cpp -o solution.exe

# Run test cases
./solution.exe
```

Or on Linux / macOS / WSL:
```bash
clang++ -std=c++20 -DLOCAL_TEST -O2 -Wall solutions/<id>-<slug>/solution.cpp -o solution.out
./solution.out
```

> [!TIP]
> You can safely copy and paste the entire `solution.cpp` file directly into LeetCode. Because `main()` is wrapped in `#ifdef LOCAL_TEST`, LeetCode's compiler will only execute `class Solution` without conflicting with LeetCode's internal test runner.
