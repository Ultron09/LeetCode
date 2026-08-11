# [630. Course Schedule III](https://leetcode.com/problems/course-schedule-iii/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Heaps / Priority Queue](../../topics/heaps-and-priority-queues.md)

---

## 📌 Problem Statement

There are `n` different online courses numbered from `1` to `n`. You are given an array `courses` where `courses[i] = [durationi, lastDayi]` indicate that the $i^{\text{th}}$ course should be taken continuously for `durationi` days and must be finished before or on `lastDayi`.

You will start on the $1^{\text{st}}$ day and you cannot take two or more courses simultaneously.

Return the **maximum number of courses** that you can take.

### Example 1:
```
Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
Output: 3
Explanation: 
There are totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
```

### Example 2:
```
Input: courses = [[1,2]]
Output: 1
```

### Example 3:
```
Input: courses = [[3,2],[4,3]]
Output: 0
```

### Constraints:
- $1 \le \text{courses.length} \le 10^4$
- $1 \le \text{duration}_i, \text{lastDay}_i \le 10^4$

---

## 💡 Intuition & Approach

### 1. Earliest Deadline First (EDF) Sorting
If two courses $A$ and $B$ are both scheduled, and $\text{lastDay}_A \le \text{lastDay}_B$, scheduling $A$ before $B$ is always as feasible or more feasible than scheduling $B$ before $A$. Thus, we sort all courses by ascending `lastDay`.

### 2. Regret-Based Greedy Replacement via Max-Heap
As we iterate through the deadline-sorted courses with a running `currentTime` and a max-heap of scheduled course durations:
1. **Direct Inclusion**: If `currentTime + duration <= lastDay`, take the course, update `currentTime += duration`, and push `duration` into the max-heap.
2. **Greedy Regret**: If the course cannot fit before its deadline, check if `maxHeap.top() > duration`.
   - Replacing the longest course previously taken with the current course keeps the total count of completed courses invariant.
   - Crucially, it reduces `currentTime` by `maxHeap.top() - duration > 0`, freeing up additional scheduling capacity for subsequent courses.
   - We pop `maxHeap.top()`, push `duration`, and adjust `currentTime += duration - maxHeap.top()`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$
  - Sorting $N$ courses takes $\mathcal{O}(N \log N)$.
  - Each course duration is pushed and popped from the max-heap at most once ($\mathcal{O}(N \log N)$ total heap operations).
- **Space Complexity:** $\mathcal{O}(N)$
  - Max-heap storage for at most $N$ scheduled courses.

---

## 🔍 Edge Cases Considered

- **Courses with `duration > lastDay`**: Automatically skipped as they can never fit.
- **Courses with Identical Deadlines**: Handled naturally by heap duration priority.
- **Single Course ($N = 1$)**: Handled in $\mathcal{O}(1)$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
