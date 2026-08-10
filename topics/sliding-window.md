# 🪟 Sliding Window

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Sliding Window techniques.

---

## 📖 1. Core Theory & Fundamentals

The Sliding Window algorithm operates on contiguous subarrays/substrings. Instead of recalculating properties across every subsegment in $\mathcal{O}(N \cdot K)$ or $\mathcal{O}(N^2)$ time, it slides a window over the array, adding the incoming element at the right end and removing the outgoing element from the left end in $\mathcal{O}(1)$ amortized time.

### Window Categories
1. **Fixed Size Window ($K$)**: Window length remains exactly $K$ throughout the traversal (e.g., Maximum Average Subarray, Number of Sub-arrays of Size K).
2. **Dynamic / Flexible Size Window**: Window expands (`right++`) until a condition is met or violated, then contracts (`left++`) to restore the invariant (e.g., Longest Substring Without Repeating Characters, Minimum Window Substring).
3. **Monotonic Queue / Deque Sliding Window**: Finding the sliding window minimum/maximum in $\mathcal{O}(N)$ total time.

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Dynamic Window (Longest Valid Substring)
```cpp
// Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(const string& s) {
    unordered_map<char, int> lastSeen;
    int maxLen = 0;
    int left = 0;

    for (int right = 0; right < static_cast<int>(s.length()); ++right) {
        char c = s[right];
        if (lastSeen.find(c) != lastSeen.end() && lastSeen[c] >= left) {
            left = lastSeen[c] + 1; // Contract window past the previous duplicate
        }
        lastSeen[c] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}
```

### Pattern B: Dynamic Window (Minimum Window Substring / Exact Match)
```cpp
// Minimum Window Substring
string minWindow(string s, string t) {
    if (s.empty() || t.empty()) return "";
    vector<int> targetCount(128, 0);
    for (char c : t) targetCount[c]++;

    int required = 0;
    for (int cnt : targetCount) if (cnt > 0) required++;

    vector<int> windowCount(128, 0);
    int formed = 0;
    int left = 0;
    int minLen = INT_MAX, minStart = 0;

    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        char c = s[right];
        windowCount[c]++;
        if (targetCount[c] > 0 && windowCount[c] == targetCount[c]) {
            formed++;
        }

        // Try to shrink window from left
        while (left <= right && formed == required) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }
            char leftChar = s[left];
            windowCount[leftChar]--;
            if (targetCount[leftChar] > 0 && windowCount[leftChar] < targetCount[leftChar]) {
                formed--;
            }
            left++;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}
```

### Pattern C: Monotonic Deque (Sliding Window Maximum)
```cpp
#include <deque>

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; // Stores indices of elements in monotonically decreasing order
    vector<int> result;

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        // Remove indices outside the current window [i - k + 1, i]
        if (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        // Maintain monotonic decreasing order
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);

        // Window reaches size k
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}
### Pattern D: Multi-Offset Phased Sliding Window (Word Concatenation)
When searching for permutations of fixed-length $L$ words:
1. Run $L$ separate sliding windows starting at offsets $0, 1, \dots, L - 1$.
2. Step forward in increments of $L$, parsing string tokens in $\mathcal{O}(1)$ via `std::string_view`.
3. Track current word frequency in `windowCount`, shrinking `left += L` whenever frequency exceeds target `wordCount`.

```cpp
vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> result;
    if (s.empty() || words.empty()) return result;
    int wordLen = words[0].size(), numWords = words.size();
    int sLen = s.size(), totalLen = wordLen * numWords;
    if (sLen < totalLen) return result;

    unordered_map<string_view, int> wordCount;
    for (const string& w : words) wordCount[w]++;
    string_view sv(s);

    for (int i = 0; i < wordLen; ++i) {
        int left = i, count = 0;
        unordered_map<string_view, int> windowCount;
        for (int right = i; right <= sLen - wordLen; right += wordLen) {
            string_view sub = sv.substr(right, wordLen);
            auto it = wordCount.find(sub);
            if (it != wordCount.end()) {
                windowCount[sub]++;
                count++;
                while (windowCount[sub] > it->second) {
                    windowCount[sv.substr(left, wordLen)]--;
                    count--;
                    left += wordLen;
                }
                if (count == numWords) result.push_back(left);
            } else {
                windowCount.clear();
                count = 0;
                left = right + wordLen;
            }
        }
    }
    return result;
}
```

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Off-by-One in Window Length**: The length of a window bounded by `left` and `right` is `right - left + 1`.
2. **Negative Numbers**: Sliding window properties (monotonicity) typically assume positive elements when tracking sums. For arrays with negative numbers and target sums, use **Prefix Sum + Hash Map** instead of standard sliding window.
3. **Empty String or $K > N$**: Always check boundary conditions where $k$ exceeds array length.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 30 | [Substring with Concatenation of All Words](../solutions/0030-substring-with-concatenation-of-all-words/README.md) | `Hard` | $\mathcal{O}(N \cdot L)$ | $\mathcal{O}(K \cdot L)$ | [C++](../solutions/0030-substring-with-concatenation-of-all-words/solution.cpp) |

