# [895. Maximum Frequency Stack](https://leetcode.com/problems/maximum-frequency-stack/)

**Difficulty:** `Hard`  
**Topics:** [Hash Table](../../topics/arrays-and-hashing.md), [Stack](../../topics/stack-and-queue.md), [Design](../../topics/stack-and-queue.md)

---

## 📌 Problem Statement

Design a stack-like data structure to push elements to the stack and pop the most frequent element from the stack.

Implement the `FreqStack` class:
- `FreqStack()` constructs an empty frequency stack.
- `void push(int val)` pushes an integer `val` onto the top of the stack.
- `int pop()` removes and returns the most frequent element in the stack.
- If there is a tie for the most frequent element, the element closest to the stack's top is removed and returned.

### Example 1:
```
Input
["FreqStack", "push", "push", "push", "push", "push", "push", "pop", "pop", "pop", "pop"]
[[], [5], [7], [5], [7], [4], [5], [], [], [], []]
Output
[null, null, null, null, null, null, null, 5, 7, 5, 4]

Explanation
FreqStack freqStack = new FreqStack();
freqStack.push(5); // The stack is [5]
freqStack.push(7); // The stack is [5,7]
freqStack.push(5); // The stack is [5,7,5]
freqStack.push(7); // The stack is [5,7,5,7]
freqStack.push(4); // The stack is [5,7,5,7,4]
freqStack.push(5); // The stack is [5,7,5,7,4,5]
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,5,7,4].
freqStack.pop();   // return 7, as 5 and 7 is the most frequent, but 7 is closest to the top. The stack becomes [5,7,5,4].
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,4].
freqStack.pop();   // return 4, as 4, 5 and 7 is the most frequent, but 4 is closest to the top. The stack becomes [5,7].
```

### Constraints:
- `0 <= val <= 10^9`
- At most `2 * 10^4` calls will be made to `push` and `pop`.
- It is guaranteed that there will be at least one element in the stack before calling `pop`.

---

## 💡 Intuition & Approach

The goal is to perform `push` and `pop` in $\mathcal{O}(1)$ time. Since we need to know the most frequent element, we must track the frequency of each element. Furthermore, to resolve ties, we need to know the order of elements that have the *same* frequency.

Instead of keeping one big stack, we can keep multiple stacks, one for each frequency tier!

1. **Hash Maps for Tracking:**
   - `freq` Map: Tracks the current frequency of each element `val`.
   - `group` Map of Stacks: Maps a frequency count `f` to a stack of elements that have reached this frequency `f`.

2. **Push Operation:**
   - When we push an element `val`, its frequency `f` increases by 1.
   - We update `freq[val] = f`.
   - We then push `val` onto `group[f]`.
   - Note: If `val` previously had frequency `f-1`, it remains in `group[f-1]`! This is the key insight. The stack `group[f]` simply stores elements that appeared at least `f` times. If `val` appeared 3 times, it exists in `group[1]`, `group[2]`, and `group[3]`.
   - We update a global `maxFreq` variable if `f > maxFreq`.

3. **Pop Operation:**
   - The element we want to pop is always at the top of `group[maxFreq]`.
   - We pop this element `x`.
   - We decrement `freq[x]` by 1.
   - If `group[maxFreq]` becomes empty after this pop, it means no elements currently have this maximum frequency. Thus, we decrement `maxFreq` by 1. Since `x` is still present in `group[maxFreq - 1]`, the system remains perfectly consistent.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(1)$ for both `push` and `pop` operations. Hash map lookups/updates and stack operations all take $\mathcal{O}(1)$ average time.
- **Space Complexity:** $\mathcal{O}(N)$, where $N$ is the number of elements pushed into the stack. Each element pushed adds exactly one entry to some stack inside `group`, so the total number of items stored across all stacks is $N$.

---

## 🔍 Edge Cases Considered

- Frequent pops of the most common element: Handled correctly as popping simply pulls from the highest frequency group and drops the `maxFreq` pointer gracefully when empty.
- Tie-breaking: By pushing elements onto the `group[f]` stack in the order they arrive, the stack's LIFO property inherently resolves ties by keeping the most recently added element at the top.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
