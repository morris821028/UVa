# Write your MySQL query statement below

SELECT t.* FROM stadium t
    LEFT JOIN stadium p1 ON t.id - 1 = p1.id
    LEFT JOIN stadium p2 ON t.id - 2 = p2.id
    LEFT JOIN stadium n1 ON t.id + 1 = n1.id
    LEFT JOIN stadium n2 ON t.id + 2 = n2.id
WHERE (t.people >= 100 AND p1.people >= 100 AND p2.people >= 100)
     OR (t.people >= 100 AND n1.people >= 100 AND n2.people >= 100)
     OR (t.people >= 100 AND n1.people >= 100 AND p1.people >= 100)
ORDER BY id;
