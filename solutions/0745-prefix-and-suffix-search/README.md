# [745. Prefix and Suffix Search](https://leetcode.com/problems/prefix-and-suffix-search/)

**Difficulty:** `Hard`  
**Topics:** [Trees](../../topics/trees.md), Trie, String

---

## 📌 Problem Statement

Design a special dictionary that searches the words in it by a prefix and a suffix.

Implement the `WordFilter` class:
- `WordFilter(string[] words)` Initializes the object with the words in the dictionary.
- `f(string pref, string suff)` Returns the index of the word in the dictionary, which has the prefix `pref` and the suffix `suff`. If there is more than one valid index, return the **largest** of them. If there is no such word in the dictionary, return `-1`.

### Example 1:
```
Input
["WordFilter", "f"]
[[["apple"]], ["a", "e"]]
Output
[null, 0]

Explanation
WordFilter wordFilter = new WordFilter(["apple"]);
wordFilter.f("a", "e"); // return 0, because the word at index 0 has prefix = "a" and suffix = "e".
```

### Constraints:
- `1 <= words.length <= 10^4`
- `1 <= words[i].length <= 7`
- `1 <= pref.length, suff.length <= 7`
- `words[i]`, `pref` and `suff` consist of lowercase English letters only.
- At most `10^4` calls will be made to the function `f`.

---

## 💡 Intuition & Approach

1. **Brute Force Idea**: We could keep a list of words, and for every query `f(pref, suff)`, check all words from right to left (largest index first) to see if they match the given prefix and suffix. This would take $\mathcal{O}(N \cdot L)$ per query, which is too slow for $10^4$ queries.
2. **Optimal Strategy (Wrapped Suffix Trie)**: We can use a single Trie to encode both prefix and suffix information.
   - For a word like `"apple"`, we generate all its suffixes and prepend each to the original word with a special delimiter, e.g., `{`.
   - The combinations to insert are:
     - `apple{apple`
     - `pple{apple`
     - `ple{apple`
     - `le{apple`
     - `e{apple`
     - `{apple`
   - When we insert these into the Trie, we update the `weight` (index) at each node. Since we iterate through the words array from start to end, the weight at any node will automatically hold the largest index of any word passing through it.
   - For a query like `pref = "a"`, `suff = "e"`, we simply format the query as `e{a` and traverse the Trie. The weight at the terminal node is our answer.

---

## ⚡ Complexity Analysis

- **Time Complexity:** 
  - **Initialization:** $\mathcal{O}(N \cdot L^2)$ — For each of the $N$ words, there are $L+1$ suffixes. We insert a string of length up to $2L+1$ into the Trie. Since $L \le 7$, this is extremely fast and takes around $15 \cdot 8 \cdot 10^4 \approx 1.2 \times 10^6$ operations.
  - **Query:** $\mathcal{O}(L)$ — Formatting the query and traversing the Trie takes time proportional to the length of the query, which is at most $15$ characters.
- **Space Complexity:** $\mathcal{O}(N \cdot L^2)$ — Maximum number of nodes in the Trie bounded by the total length of all inserted strings. 

---

## 🔍 Edge Cases Considered

- Missing prefix/suffix matching: Traversal ends prematurely and returns `-1`.
- Multiple words matching the prefix/suffix: Because we process the dictionary in index order, later indices naturally overwrite earlier ones in the `weight` property of each `TrieNode`.
- Word length is up to 7, preventing memory explosion of generating $O(L^2)$ insertions per word.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
