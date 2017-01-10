#ifndef _CITY_H
#define _CITY_H
typedef struct City {
    int label;
    struct City *east, *north;
} City; 
 
int City_Grid(City *capital);
#endif
