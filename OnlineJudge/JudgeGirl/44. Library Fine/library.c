#include <stdio.h>
#include "book.h"
#include "date.h"

static int addDay[] = {0, 0, 31, 59, 90, 120, 151,
                181, 212, 243, 273, 304,
                334, 365};
static int mDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int cntDay(int y, int m, int d) {
    int sum, leap, isleap;
    isleap = (y%4 == 0 && y%100 != 0) || y%400 == 0;
    y--;
    leap = y/4 - y/100 + y/400;
    sum = y*365 + leap + addDay[m] + (m > 2)*isleap + d;
    return sum;
}
// enum Type {NOVEL, COMICS, MANUAL, TEXTBOOK};
static int rental_time(enum Type t) {
	switch(t) {
		case NOVEL: 	return 90;
		case COMICS: 	return 10;
		case MANUAL: 	return 100;
		case TEXTBOOK: 	return 5;
	}
	return -1;
}
static int compute_dist(unsigned int n) {
	int a = __builtin_ffs(n) - 1;
	int b = __builtin_ffs(n ^ (1LU<<a)) - 1;
	return b - a - 1;
}
unsigned int library_fine(struct Book book, struct Date date_borrowed, struct Date date_returned) {
	int days = - cntDay(date_borrowed.year, date_borrowed.month, date_borrowed.day) 
			 + cntDay(date_returned.year, date_returned.month, date_returned.day) + 1;
	int mx = rental_time(book.type);
	if (days <= mx)	return 0;
	int cost = compute_dist(book.importance);
	return (days - mx) * cost;
}
