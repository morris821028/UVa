#include <stdio.h>
#include "time.h"

void initTime(Time *t) {
	t->hour = t->minute = t->second = 0;
}

void setTime(Time *time, int hour, int minute, int second) {
	time->hour = hour;
	time->minute = minute;
	time->second = second;
}

void addTime(Time *time, int hour, int minute, int second) {
	time->second += second;
	time->minute += time->second/60 + minute;
	time->hour += time->minute/60 + hour;

	time->second %= 60;
	time->minute %= 60;
	time->hour %= 24;
}

void printTime(Time *time) {
#ifdef H24
	printf("%02d:%02d:%02d\n", time->hour, time->minute, time->second);
#else
	if (0 == time->hour) {
		printf("12am:%02d:%02d\n", time->minute, time->second);
	} else if (0 < time->hour && time->hour < 12) {
		printf("%02dam:%02d:%02d\n", time->hour, time->minute, time->second);
	} else if (12 == time->hour) {
		printf("12pm:%02d:%02d\n", time->minute, time->second);
	} else {
		printf("%02dpm:%02d:%02d\n", time->hour%12, time->minute, time->second);
	}
#endif
}
