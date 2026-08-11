# [185. Department Top Three Salaries](https://leetcode.com/problems/department-top-three-salaries/)

**Difficulty:** `Hard`  
**Topics:** [Database / SQL](../../topics/arrays-and-hashing.md), [Window Functions](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Table: `Employee`
```
+--------------+---------+
| Column Name  | Type    |
+--------------+---------+
| id           | int     |
| name         | varchar |
| salary       | int     |
| departmentId | int     |
+--------------+---------+
id is the primary key for this table.
departmentId is a foreign key of the ID from the Department table.
```

Table: `Department`
```
+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| id          | int     |
| name        | varchar |
+-------------+---------+
id is the primary key for this table.
```

A high earner in a department is an employee who has a salary in the **top three unique salaries** for that department.

Write a solution to find the employees who are high earners in each of the departments. Return the result table in any order.

### Example 1:
```
Input: 
Employee table:
+----+-------+--------+--------------+
| id | name  | salary | departmentId |
+----+-------+--------+--------------+
| 1  | Joe   | 85000  | 1            |
| 2  | Henry | 80000  | 2            |
| 3  | Sam   | 60000  | 2            |
| 4  | Max   | 90000  | 1            |
| 5  | Janet | 69000  | 1            |
| 6  | Randy | 85000  | 1            |
| 7  | Will  | 70000  | 1            |
+----+-------+--------+--------------+
Department table:
+----+-------+
| id | name  |
+----+-------+
| 1  | IT    |
| 2  | Sales |
+----+-------+
Output: 
+------------+----------+--------+
| Department | Employee | Salary |
+------------+----------+--------+
| IT         | Max      | 90000  |
| IT         | Joe      | 85000  |
| IT         | Randy    | 85000  |
| IT         | Will     | 70000  |
| Sales      | Henry    | 80000  |
| Sales      | Sam      | 60000  |
+------------+----------+--------+
```

---

## 💡 Intuition & Approaches

### Approach 1: Window Function (`DENSE_RANK()`)
- `DENSE_RANK()` assigns consecutive ranking integers to distinct values without skipping ranks for ties (unlike `RANK()`).
- Partitioning by `e.departmentId` and ordering by `e.salary DESC` ensures that employees with the same salary in the same department receive the identical rank.
- Filter records with `rnk <= 3`.

```sql
WITH RankedSalaries AS (
    SELECT 
        d.name AS Department,
        e.name AS Employee,
        e.salary AS Salary,
        DENSE_RANK() OVER (
            PARTITION BY e.departmentId 
            ORDER BY e.salary DESC
        ) AS rnk
    FROM Employee e
    JOIN Department d ON e.departmentId = d.id
)
SELECT 
    Department,
    Employee,
    Salary
FROM RankedSalaries
WHERE rnk <= 3;
```

### Approach 2: Correlated Subquery
Count how many unique salaries in the same department strictly exceed the current employee's salary:
```sql
SELECT 
    d.name AS Department,
    e1.name AS Employee,
    e1.salary AS Salary
FROM Employee e1
JOIN Department d ON e1.departmentId = d.id
WHERE 3 > (
    SELECT COUNT(DISTINCT e2.salary)
    FROM Employee e2
    WHERE e2.departmentId = e1.departmentId
      AND e2.salary > e1.salary
);
```

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$ where $N$ is the number of rows in `Employee` (sorting within partitions).
- **Space Complexity:** $\mathcal{O}(N)$ for window buffer / result set.

---

## 💻 Source Code

- [SQL Solution](solution.sql)
- [C++ In-Memory Solution](solution.cpp)
