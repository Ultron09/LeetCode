# [262. Trips and Users](https://leetcode.com/problems/trips-and-users/)

**Difficulty:** `Hard`  
**Topics:** [Database / SQL](../../topics/arrays-and-hashing.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Table: `Trips`
```
+-------------+----------+
| Column Name | Type     |
+-------------+----------+
| id          | int      |
| client_id   | int      |
| driver_id   | int      |
| city_id     | int      |
| status      | enum     |
| request_at  | varchar  |     
+-------------+----------+
id is the primary key for this table.
Status is an ENUM type of ('completed', 'cancelled_by_driver', 'cancelled_by_client').
```

Table: `Users`
```
+-------------+----------+
| Column Name | Type     |
+-------------+----------+
| users_id    | int      |
| banned      | enum     |
| role        | enum     |
+-------------+----------+
users_id is the primary key for this table.
role is an ENUM type of ('client', 'driver', 'partner').
banned is an ENUM type of ('Yes', 'No').
```

The **cancellation rate** is computed by dividing the number of canceled (by client or driver) requests with **unbanned users** by the total number of requests with **unbanned users** on that day.

Write a solution to find the cancellation rate of requests with unbanned users (both client and driver must not be banned) each day between `"2013-10-01"` and `"2013-10-03"` with at least one trip. Round `Cancellation Rate` to two decimal points.

### Example 1:
```
Output: 
+------------+-------------------+
| Day        | Cancellation Rate |
+------------+-------------------+
| 2013-10-01 | 0.33              |
| 2013-10-02 | 0.00              |
| 2013-10-03 | 0.50              |
+------------+-------------------+
```

---

## 💡 Intuition & Approach

### 1. High-Performance SQL Strategy
To achieve the absolute fastest execution plan in MySQL and PostgreSQL:
1. **Direct `JOIN` with Predicate Pushdown**:
   - `JOIN Users c ON t.client_id = c.users_id AND c.banned = 'No'`
   - `JOIN Users d ON t.driver_id = d.users_id AND d.banned = 'No'`
   - Avoid slow `NOT IN (SELECT users_id FROM Users WHERE banned = 'Yes')` subqueries which can degrade to full table scans.
2. **Single-Pass Boolean Aggregation (`AVG`)**:
   - Rather than computing `SUM(cancelled) / COUNT(*)`, calculate `AVG(t.status != 'completed')` directly.
   - For universal SQL engine compatibility, `AVG(CASE WHEN t.status != 'completed' THEN 1.0 ELSE 0.0 END)` handles boolean coercion seamlessly.
3. **Date Range Index Range Scan**:
   - `WHERE t.request_at BETWEEN '2013-10-01' AND '2013-10-03'` allows immediate B-Tree index range scans on `request_at`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(T + U)$ where $T$ is the number of Trips and $U$ is the number of Users (Hash Join + single aggregation pass).
- **Space Complexity:** $\mathcal{O}(U + D)$ auxiliary memory for index lookups and daily grouping bins.

---

## 💻 Source Code

- [SQL Solution](solution.sql)
- [C++ Simulation](solution.cpp)
