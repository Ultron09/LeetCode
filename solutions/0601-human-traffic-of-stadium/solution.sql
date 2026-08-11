-- ============================================================================
-- Problem: 601. Human Traffic of Stadium
-- Difficulty: Hard
-- Category: Database (SQL) / MySQL, PostgreSQL, Oracle, MS SQL Server
-- LeetCode Link: https://leetcode.com/problems/human-traffic-of-stadium/
-- ============================================================================

-- ----------------------------------------------------------------------------
-- Approach 1: Island-and-Gap Technique with ROW_NUMBER() (Optimal & Cleanest)
-- ----------------------------------------------------------------------------
-- For consecutive matching IDs, the difference (id - ROW_NUMBER()) is constant.
-- Grouping by this invariant forms contiguous "islands" of high-traffic days.
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
SELECT 
    id, 
    visit_date, 
    people
FROM IslandCounts
WHERE island_size >= 3
ORDER BY visit_date ASC;

-- ----------------------------------------------------------------------------
-- Approach 2: Window Functions LEAD() & LAG()
-- ----------------------------------------------------------------------------
-- Check if the current row is the first, middle, or last in a 3-consecutive streak.
/*
WITH Evaluated AS (
    SELECT 
        id, 
        visit_date, 
        people,
        LAG(people, 2) OVER (ORDER BY id) AS p_lag2,
        LAG(people, 1) OVER (ORDER BY id) AS p_lag1,
        LEAD(people, 1) OVER (ORDER BY id) AS p_lead1,
        LEAD(people, 2) OVER (ORDER BY id) AS p_lead2,
        LAG(id, 2) OVER (ORDER BY id) AS id_lag2,
        LAG(id, 1) OVER (ORDER BY id) AS id_lag1,
        LEAD(id, 1) OVER (ORDER BY id) AS id_lead1,
        LEAD(id, 2) OVER (ORDER BY id) AS id_lead2
    FROM Stadium
)
SELECT id, visit_date, people
FROM Evaluated
WHERE people >= 100 AND (
    (p_lag2 >= 100 AND p_lag1 >= 100 AND id_lag2 = id - 2 AND id_lag1 = id - 1) OR
    (p_lag1 >= 100 AND p_lead1 >= 100 AND id_lag1 = id - 1 AND id_lead1 = id + 1) OR
    (p_lead1 >= 100 AND p_lead2 >= 100 AND id_lead1 = id + 1 AND id_lead2 = id + 2)
)
ORDER BY visit_date ASC;
*/
