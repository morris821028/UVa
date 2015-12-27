#ifndef MWTIME
#define MWTIME

typedef struct Time {
	int hour;
	int minute;
	int second;
} Time;

void initTime(Time *time);
void setTime(Time *time, int hour, int minute, int second);
void addTime(Time *time, int hour, int minute, int second);
void printTime(Time *time);
#endif
