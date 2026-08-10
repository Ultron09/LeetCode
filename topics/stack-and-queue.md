# 🥞 Stack & Queue

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Stacks, Queues, and Monotonic Stacks.

---

## 📖 1. Core Theory & Fundamentals

### Stack (LIFO - Last In First Out)
- **C++ Container**: `std::stack<T>` (adapter over `std::deque` or `std::vector`).
- **Core Operations**: `push()`, `pop()`, `top()`, `empty()`, all $\mathcal{O}(1)$.
- **Use Cases**: Expression parsing, undo/redo, recursive backtracking elimination, matching brackets, monotonic stack queries.

### Queue (FIFO - First In First Out) & Deque (Double Ended Queue)
- **C++ Containers**: `std::queue<T>`, `std::deque<T>`.
- **Core Operations**: `push()`, `pop()`, `front()`, `back()`, all $\mathcal{O}(1)$.
- **Use Cases**: Breadth-First Search (BFS), task scheduling, sliding window maximums.

### Monotonic Stack
A stack where elements are strictly increasing or strictly decreasing from bottom to top.
- Used to solve **"Next Greater Element"**, **"Previous Smaller Element"**, **"Largest Rectangle in Histogram"**, and **"Daily Temperatures"** in linear $\mathcal{O}(N)$ time.

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Valid Parentheses / Bracket Matching
```cpp
#include <stack>
#include <unordered_map>

bool isValid(const string& s) {
    stack<char> st;
    unordered_map<char, char> matching = {{')', '('}, {'}', '{'}, {']', '['}};

    for (char c : s) {
        if (matching.count(c)) { // Closing bracket
            if (st.empty() || st.top() != matching[c]) return false;
            st.pop();
        } else { // Opening bracket
            st.push(c);
        }
    }
    return st.empty();
}
```

### Pattern B: Monotonic Decreasing Stack (Next Greater Element / Daily Temperatures)
```cpp
// Returns array of distances to the next warmer day
vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> st; // Stores indices with decreasing temperature

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
            int prevIndex = st.top();
            st.pop();
            result[prevIndex] = i - prevIndex;
        }
        st.push(i);
    }
    return result;
}
```

### Pattern C: Largest Rectangle in Histogram
```cpp
int largestRectangleArea(vector<int>& heights) {
    heights.push_back(0); // Dummy sentinel to pop remaining heights
    int n = heights.size();
    stack<int> st;
    int maxArea = 0;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : (i - st.top() - 1);
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }
    heights.pop_back(); // Restore original array
    return maxArea;
}
```

### Pattern E: Collision Resolution Simulation with Stack & Original Index Mapping
When simulating pairwise interactions/collisions on a 1D line:
1. **Spatial Sorting**: Sort object indices by their 1D spatial coordinates while preserving original index access.
2. **Directional Stack**: Maintain a stack of objects moving in the forward/rightward direction.
3. **Collision Loop**: When encountering an object moving backward/leftward, iteratively resolve collisions against the stack top based on comparison rules (health, mass, momentum) until the incoming object is destroyed, eliminates the top, or eliminates both.
4. **Order Preservation**: Mutate the original properties (health/status) in-place and extract survivors in the original $0..N-1$ sequence.

### Pattern F: Index-Boundary Stack for Longest Valid Substrings
```cpp
int longestValidParentheses(const string& s) {
    stack<int> st;
    st.push(-1); // Sentinel boundary
    int maxLen = 0;

    for (int i = 0; i < static_cast<int>(s.length()); ++i) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            if (st.empty()) {
                st.push(i); // Reset base boundary
            } else {
                maxLen = max(maxLen, i - st.top());
            }
        }
    }
    return maxLen;
}
```

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Calling `st.top()` or `st.pop()` on Empty Stack**: Always check `!st.empty()` before reading `top()` or popping to prevent runtime segmentation faults.
2. **Sentinel / Dummy Values**: In monotonic stack problems (e.g. histogram), adding a sentinel value `0` at the end ensures all elements are flushed from the stack.
3. **Duplicate Values in Monotonic Stack**: Pay close attention to whether the condition requires strict inequality (`>`) or non-strict (`>=`) based on how duplicates must be handled.
4. **Coordinate Overflow**: When lengths grow up to $10^{15}$, always use `long long` for all index and length operations.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 32 | [Longest Valid Parentheses](../solutions/0032-longest-valid-parentheses/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0032-longest-valid-parentheses/solution.cpp) |
| 2751 | [Robot Collisions](../solutions/2751-robot-collisions/README.md) | `Hard` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N)$ | [C++](../solutions/2751-robot-collisions/solution.cpp) |
| 3614 | [Process String with Special Operations II](../solutions/3614-process-string-with-special-operations-ii/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/3614-process-string-with-special-operations-ii/solution.cpp) |



