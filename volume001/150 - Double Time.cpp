#include <stdio.h> 
#include <algorithm>
#include <iostream>
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

int main() {
	string str;
	while(cin >> str) {
		if(str == "#")	break;
		int day, d, m, y;
		day = find(dayName, dayName + 7, str) - dayName;
		cin >> d >> str >> y;
		m = find(monthName, monthName + 12, str) - monthName + 1;
		int days = toDays(y, m, d, 1), old;
		if(day == (days + 1)%7) {
			// old -> new
			y = days / (400 * 365 + 100 - 3) * 400;
			days %= 400 * 365 + 100 - 3;
			if(days == 100 * 365 + 25 - 1) {
				y += 300;
				days -= (100 * 365 + 25 - 1) * 3;
			} else {
				y += days / (100 * 365 + 25 - 1) * 100;
				days %= 100 * 365 + 25 - 1;
			}
			old = 0;
		} else {
			// new -> old
			days = toDays(y, m, d, 0) + 2;
			y = 0;
			old = 1;
		}
		y += days / (4 * 365 + 1) * 4;
		days %= (4 * 365 + 1);
		if(days == 365 * 4) {
			y += 3;
			days -= 365 * 3;
		} else {
			y += days / 365;
			days %= 365;
		}
		y++;
		int *pDays = isLeapYear(y, old) ? aLeapDays : aDays;
		
		for(m = 0; m < 12 && pDays[m] <= days; m++);
		
		d = days - pDays[m - 1] + 1;
		day = (toDays(y, m, d, old) + 1) %7;
		printf("%s %d%s %s %d\n", dayName[day].c_str(), d, old ? "*" : "", monthName[m-1].c_str(), y);
	}
	return 0;
}
