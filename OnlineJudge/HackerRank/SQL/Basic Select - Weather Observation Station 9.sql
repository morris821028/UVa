SELECT DISTINCT CITY FROM STATION 
    WHERE upper(left(CITY, 1)) not in ('A', 'E', 'I', 'O', 'U');