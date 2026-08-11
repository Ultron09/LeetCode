-- Problem: 185. Department Top Three Salaries
-- Difficulty: Hard
-- Topics: Database, SQL (MySQL, PostgreSQL, Oracle, MS SQL Server)
-- LeetCode Link: https://leetcode.com/problems/department-top-three-salaries/

-- Approach 1: Window Function DENSE_RANK() (Modern Standard SQL)
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
