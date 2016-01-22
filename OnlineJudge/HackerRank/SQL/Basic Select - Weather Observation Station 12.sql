SELECT DISTINCT CITY FROM STATION 
    WHERE upper(right(CITY, 1)) not in ('A', 'E', 'I', 'O', 'U') 
        AND upper(left(CITY, 1)) not in ('A', 'E', 'I', 'O', 'U');