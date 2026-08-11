# [601. Human Traffic of Stadium](https://leetcode.com/problems/human-traffic-of-stadium/)

**Difficulty:** `Hard`  
**Topics:** [Database / SQL](../../topics/arrays-and-hashing.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Table: `Stadium`

```
+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| id            | int     |
| visit_date    | date    |
| people        | int     |
+---------------+---------+
visit_date is the column with unique values for this table.
Each row of this table contains the visit date and visit id to the stadium with the number of people during the visit.
As the id increases, the date increases as well.
```

Write a solution to display the records with **three or more rows with consecutive `id`'s**, and the number of people is **greater than or equal to 100** for each.

Return the result table ordered by `visit_date` in **ascending order**.

### Example 1:

**Input:** 
```
Stadium table:
+------+------------+-----------+
| id   | visit_date | people    |
+------+------------+-----------+
| 1    | 2017-01-01 | 10        |
| 2    | 2017-01-02 | 109       |
| 3    | 2017-01-03 | 150       |
| 4    | 2017-01-04 | 99        |
| 5    | 2017-01-05 | 145       |
| 6    | 2017-01-06 | 1455      |
| 7    | 2017-01-07 | 199       |
| 8    | 2017-01-09 | 188       |
+------+------------+-----------+
```

**Output:** 
```
+------+------------+-----------+
| id   | visit_date | people    |
+------+------------+-----------+
| 5    | 2017-01-05 | 145       |
| 6    | 2017-01-06 | 1455      |
| 7    | 2017-01-07 | 199       |
| 8    | 2017-01-09 | 188       |
+------+------------+-----------+
```

**Explanation:** 
The four rows with ids `5, 6, 7, and 8` have consecutive ids and each of them has $\ge 100$ people attended. Row 8 is included even though the `visit_date` skipped a day because the `id` values are consecutive. The rows with ids `2` and `3` are excluded because they do not form a sequence of at least 3 consecutive ids.

---

## 💡 Intuition & Approach

### 1. The Island-and-Gap Technique (Optimal SQL)
When identifying contiguous streaks of qualifying rows:
1. Filter the dataset to rows with `people >= 100`.
2. Compute `id - ROW_NUMBER() OVER (ORDER BY id) AS island_id`.
   - For consecutive IDs (e.g. $5, 6, 7, 8$), both `id` and `ROW_NUMBER()` increase by $1$ simultaneously.
   - Therefore, the difference `id - row_number` remains **strictly constant** across each contiguous island.
3. Count rows in each island using `COUNT(*) OVER (PARTITION BY island_id)`.
4. Retain all records belonging to islands of size $\ge 3$.

```sql
WITH Filtered AS (
    SELECT 
        id, 
        visit_date, 
        people,
        id - ROW_NUMBER() OVER (ORDER BY id) AS island_id
    FROM Stadium
    WHERE people >= 100
),
IslandCounts AS (
    SELECT 
        id, 
        visit_date, 
        people,
        COUNT(*) OVER (PARTITION BY island_id) AS island_size
    FROM Filtered
)
SELECT id, visit_date, people
FROM IslandCounts
WHERE island_size >= 3
ORDER BY visit_date ASC;
```

### 2. In-Memory C++ Two-Pointer Algorithm
1. Filter `stadium` records where `people >= 100`.
2. Scan the filtered list using two pointers `[i, j]` to identify contiguous runs where `id[k + 1] == id[k] + 1`.
3. Whenever `streakLength = j - i + 1 >= 3`, append all records in the interval $[i, j]$ to the output list.

---

## ⚡ Complexity Analysis

- **Time Complexity:**
  - **SQL Query:** $\mathcal{O}(N \log N)$ (or $\mathcal{O}(N)$ with index-ordered scan) to partition and sort rows.
  - **C++ Engine:** $\mathcal{O}(N)$ single-pass linear scan.
- **Space Complexity:**
  - **SQL Query:** $\mathcal{O}(N)$ for window function state frames.
  - **C++ Engine:** $\mathcal{O}(N)$ auxiliary space for filtered and output structures.

---

## 🔍 Edge Cases Considered

- **Islands of size 1 or 2**: Properly filtered out (must have $\ge 3$ consecutive IDs).
- **Multiple Disjoint Islands**: Handled independently by unique `island_id` partitions.
- **Non-consecutive Dates with Consecutive IDs**: Explicitly tested; IDs govern continuity as per problem specification.

---

## 💻 Source Code

- [SQL Solution](solution.sql)
- [C++ Solution](solution.cpp)
