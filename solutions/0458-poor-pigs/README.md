# [458. Poor Pigs](https://leetcode.com/problems/poor-pigs/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

There are `buckets` buckets of liquid, where exactly one of the buckets is poisonous. To figure out which one is poisonous, you feed some number of (poor) pigs the liquid to see whether they will die or not. Unfortunately, you only have `minutesToTest` minutes to determine which bucket is poisonous.

You can feed the pigs according to these steps:
1. Choose some live pigs to feed.
2. For each pig, choose which buckets to feed it. The pig will consume all the chosen buckets simultaneously and will take no time. Each pig can feed from any number of buckets, and each bucket can be fed from by any number of pigs.
3. Wait for `minutesToDie` minutes. You may not feed any other pigs during this time.
4. After `minutesToDie` minutes have passed, any pigs that have been fed the poisonous bucket will die, and all others will survive.
5. Repeat this process until you run out of time.

Given `buckets`, `minutesToDie`, and `minutesToTest`, return the minimum number of pigs needed to figure out which bucket is poisonous within the allotted time.

### Example 1:
```
Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
Output: 2
Explanation: We can determine the poisonous bucket as follows:
At time 0, feed the first pig buckets 1 and 2, and feed the second pig buckets 2 and 3.
At time 15, there are 4 possible outcomes:
- If only the first pig dies, bucket 1 is poisonous.
- If only the second pig dies, bucket 3 is poisonous.
- If both pigs die, bucket 2 is poisonous.
- If neither pig dies, bucket 4 is poisonous.
```

### Example 2:
```
Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
Output: 2
```

### Constraints:
- $1 \le \text{buckets} \le 1000$
- $1 \le \text{minutesToDie} \le \text{minutesToTest} \le 100$

---

## 💡 Intuition & Approach

### 1. Information Theory & State Encoding
Let $T = \lfloor \frac{\text{minutesToTest}}{\text{minutesToDie}} \rfloor$ be the total number of test rounds available.

Over $T$ testing rounds, a single pig can end up in one of $T + 1$ mutually exclusive states:
1. Dies in round 1.
2. Dies in round 2.
   $$\vdots$$
$T$. Dies in round $T$.  
$T + 1$. Survives all $T$ rounds (never dies).

Each pig represents a single **base-$(T + 1)$ digit** of information.

### 2. Multi-Dimensional Hypercube Encoding
With $P$ pigs, each pig independently tracks one coordinate dimension in a $P$-dimensional hypercube where each dimension has length $T + 1$.

The total number of distinct bucket states that can be uniquely encoded and distinguished by $P$ pigs is:
$$\text{capacity} = (T + 1)^P$$

To identify the unique poisonous bucket among `buckets`:
$$(T + 1)^P \ge \text{buckets}$$

Solving for the minimum non-negative integer $P$:
$$P = \left\lceil \log_{T + 1}(\text{buckets}) \right\rceil = \left\lceil \frac{\log(\text{buckets})}{\log(T + 1)} \right\rceil$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\log_{T+1}(\text{buckets}))$
  - Multiplying `maxBuckets *= states` until reaching `buckets` takes at most $\lceil \log_2(1000) \rceil \le 10$ loop iterations.
  - Overall time complexity is $\mathcal{O}(1)$ practically ($\le 10$ operations).
- **Space Complexity:** $\mathcal{O}(1)$
  - Uses only a few scalar 32-bit/64-bit integer counters.

---

## 🔍 Edge Cases Considered

- **$\text{buckets} = 1$**: With only 1 bucket, it is known to be poisonous with certainty without running any tests $\implies$ returns $0$ pigs.
- **$\text{minutesToDie} = \text{minutesToTest}$**: Exactly 1 round available $\implies \text{states} = 2$ (binary encoding: $(2)^P \ge \text{buckets}$).
- **$\text{minutesToTest} < \text{minutesToDie}$**: $T = 0 \implies \text{states} = 1$, handles zero rounds.
- **Exact Power Match**: e.g., $\text{buckets} = 125, \text{states} = 5 \implies 5^3 = 125$, returns $3$ pigs without overestimating.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
