#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctype.h>
#include <string.h>
using namespace std;

int aDays[] =  {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
int aLeapDays[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
const string dayName[] = {"Sunday", "Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday", "Saturday"};
const string monthName[] = {"January", "February", "March",
        "April", "May", "June", "July", "August", "September",
        "October", "November", "December"};
int isLeapYear(int y, int old) {
	if(old)	return y%4 == 0;
	return (y%4 == 0 && y%100 != 0) || y%400 == 0;
}
int toDays(int y, int m, int d, int old) {
	y--;
	int days = y * 365 + y / 4 + (old ? 0 : (y / 400 - y/100));
	days += m > 2 ? isLeapYear(y+1, old) : 0;
	return days + aDays[m - 1] + d - 1 - (old * 2);
}

struct Event {
	int y, m, d, p, in;
	string title;
	Event(int a = 0, int b = 0, int c = 0, int e = 0):
		y(a), m(b), d(c), p(e) {
	}
	bool operator<(const Event &x) const {
		if(toDays(y, m, d, 0) != toDays(x.y, x.m, x.d, 0))
			return toDays(y, m, d, 0) < toDays(x.y, x.m, x.d, 0) ;
		if(p != x.p)
			return p > x.p;
		return in < x.in;
	}
};
bool orderCmp(Event a, Event b) {
	if(toDays(a.y, a.m, a.d, 0) != toDays(b.y, b.m, b.d, 0))
		return toDays(a.y, a.m, a.d, 0) < toDays(b.y, b.m, b.d, 0);
	return a.in < b.in;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	char line[1024];
	int year, d, m, y, p, cases = 0, in = 0;
	vector<Event> events;
	gets(line);
	sscanf(line, "%d", &year), y = year;
	while(gets(line) && strcmp(line, "#")) {
		if(line[0] == 'A') {
			sscanf(line+1, "%d %d %d", &d, &m, &p);
			in++;
			int j = 1;
			for(int i = 0; i < 3; i++) {
				while(isspace(line[j]))
					j++;
				while(isdigit(line[j]))
					j++;
			}
			while(isspace(line[j]))	j++;
			Event e(y, m, d, p);
			e.in = in;
			e.title = line + j;
			events.push_back(e);
			e.y++;
			events.push_back(e);
		} else {
			sscanf(line+1, "%d %d", &d, &m);
			if(cases++)	puts("");
			printf("Today is:%3d%3d\n", d, m);
			
			sort(events.begin(), events.end(), orderCmp);
			for(int i = 0; i < events.size(); i++) {
				if(toDays(year, m, d, 0) >= toDays(events[i].y, events[i].m, events[i].d, 0) - events[i].p &&
					toDays(year, m, d, 0) == toDays(events[i].y, events[i].m, events[i].d, 0)) {
					printf("%3d%3d *TODAY* %s\n", d, m, events[i].title.c_str());
				}
			}
			sort(events.begin(), events.end());
			for(int i = 0; i < events.size(); i++) {
				if(toDays(year, m, d, 0) >= toDays(events[i].y, events[i].m, events[i].d, 0) - events[i].p &&
					toDays(year, m, d, 0) < toDays(events[i].y, events[i].m, events[i].d, 0)) {
					string stars(toDays(year, m, d, 0) - toDays(events[i].y, events[i].m, events[i].d, 0) + events[i].p + 1, '*');
					printf("%3d%3d %-7s %s\n", events[i].d, events[i].m, stars.c_str(), events[i].title.c_str());						
				}
			}
		}
	}
	return 0;
}
/*
1999
A 23 12 5 Partner's birthday
A 25 12 7 Christmas
A 20 12 1 Unspecified Anniversary
A 25 12 7 Christmas So Important
A 26 12 6 Boxing Day
A 26 12 6 Christmas Eve + 2
A 1 1 6 New Year
A 31 12 6 New Year Eve
A 1 1 7 New Year Again
A 2 1 4 Nothing
A 1 3 4 First Day of March
A 28 2 4 Feb Regular
D 31 12
#

Today is: 31 12
 31 12 *TODAY* New Year Eve
  1  1 ******* New Year Again
  1  1 ******  New Year
  2  1 ***     Nothing
*/
