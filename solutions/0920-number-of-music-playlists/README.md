# [920. Number of Music Playlists](https://leetcode.com/problems/number-of-music-playlists/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Math](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

Your music player contains `n` different songs. You want to listen to `goal` songs (not necessarily different) during your trip. To avoid boredom, you will create a playlist so that:

1. Every song is played at least once.
2. A song can only be played again only if `k` other songs have been played.

Given `n`, `goal`, and `k`, return the number of possible playlists that you can create. Since the answer can be very large, return it modulo `10^9 + 7`.

### Example 1:
```
Input: n = 3, goal = 3, k = 1
Output: 6
Explanation: There are 6 possible playlists: [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], and [3, 2, 1].
```

### Example 2:
```
Input: n = 2, goal = 3, k = 0
Output: 6
Explanation: There are 6 possible playlists: [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2, 1], [2, 1, 2], and [1, 2, 2].
```

### Constraints:
- `0 <= k < n <= goal <= 100`

---

## 💡 Intuition & Approach

This problem asks for the number of valid sequences (playlists), which strongly hints at Combinatorics or Dynamic Programming. The state transitions cleanly in DP.

1. **State Definition**:
   Let `dp[i][j]` be the number of valid playlists of length `i` that contain exactly `j` unique songs.

2. **Base Case**:
   - `dp[0][0] = 1`: An empty playlist with 0 unique songs has 1 combination.
   - All other `dp[i][j]` are initially `0`.

3. **State Transitions**:
   Suppose we are forming a playlist of length `i` with `j` unique songs. The $i$-th song added can either be:
   - **A brand new song**: 
     We transitioned from a playlist of length `i-1` having `j-1` unique songs. How many new songs can we pick? Since there are `n` total songs and we have already used `j-1` of them, there are exactly `n - (j - 1)` available choices for the new song.
     `dp[i][j] += dp[i-1][j-1] * (n - j + 1)`
     
   - **A previously played song**:
     We transitioned from a playlist of length `i-1` that *already had* `j` unique songs. We are re-using one of those `j` songs. However, the constraints state that a song can only be re-played if `k` *other* songs were played in between. Thus, the last `k` songs in the playlist must all be distinct. We can choose any of the `j` unique songs *except* the `k` most recently played ones. Therefore, there are `max(0, j - k)` available choices.
     `dp[i][j] += dp[i-1][j] * max(0, j - k)`

4. **Space Optimization**:
   Notice that `dp[i][...]` only depends on `dp[i-1][...]`. We can reduce the space complexity to $\mathcal{O}(N)$ by only keeping the previous row.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\text{goal} \times n)$ — We iterate through a DP table of dimensions `goal` by `n`. Each transition is calculated in $\mathcal{O}(1)$ time.
- **Space Complexity:** $\mathcal{O}(n)$ — With space optimization, we only need a 1D array of size `n + 1` to store the states for the previous sequence length.

---

## 🔍 Edge Cases Considered

- $k = 0$: Replaying any song immediately is allowed. The math handles this correctly (`max(0, j - 0)`).
- $n = \text{goal}$: Only playlists containing no duplicates are valid (exact permutations).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
