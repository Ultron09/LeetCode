# Workspace Agent Rules for LeetCode Solving

> This file is located in `.agents/` as the workspace-level customization anchor for Antigravity and pair-programming agents. See [AGENTS.md](../AGENTS.md) for full detailed documentation.

## Core Directives

1. **Solution Structure**: Whenever the user sends a LeetCode problem, create a folder under `solutions/<id>-<slug>/` containing `solution.cpp` (with modern C++17/20, clean comments, complexity metrics, and a runnable test harness in `main()`) and a companion `README.md` (with intuition, approach, complexity, and edge cases).
2. **Topic Notes Maintenance**: Always maintain and enrich the topic theory files under `topics/<topic>.md`. Add newly solved problems to the topic's problem list and document new patterns/templates.
3. **Master Index Synchronization**: Keep `INDEX.md` and `README.md` updated with the newly solved problem, its difficulty, topic, time complexity, space complexity, and clickable relative links to the solution and topic notes.
