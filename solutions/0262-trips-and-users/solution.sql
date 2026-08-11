-- ============================================================================
-- Problem: 262. Trips and Users
-- Difficulty: Hard
-- Category: Database (SQL)
-- LeetCode Link: https://leetcode.com/problems/trips-and-users/
-- ============================================================================

-- Optimal & Fastest Query using Direct JOIN Filtering and AVG Aggregation
SELECT 
    t.request_at AS Day,
    ROUND(
        AVG(CASE WHEN t.status != 'completed' THEN 1.0 ELSE 0.0 END), 
        2
    ) AS "Cancellation Rate"
FROM Trips t
JOIN Users c ON t.client_id = c.users_id AND c.banned = 'No'
JOIN Users d ON t.driver_id = d.users_id AND d.banned = 'No'
WHERE t.request_at BETWEEN '2013-10-01' AND '2013-10-03'
GROUP BY t.request_at;
