#include <iostream>
#include <sstream>
#include <string.h>
#include <cstdio>
#include <map>
using namespace std;

int main() {
	int p, q, num, sum, a, b;
	scanf("%d %d", &p, &q);
	char str[1000];
	map<string, int> record;
	while(p--) {
		scanf("%s %d.%d", str, &a, &b);
		record[str] = a*10+b;
	}
	getchar();
	int Case = 0;
	stringstream line;
	while(q--) {
		gets(str);
		stringstream line(str);
		printf("Guess #%d was ", ++Case);
		sum = 0;
		while(line >> str) {
			if(strcmp(str ,"+") == 0)
				continue;
			if(strcmp(str ,"<") == 0) {
				line >> num;
				if(sum < num*10) {
					puts("correct.");
				} else {
					puts("incorrect.");
				}
				break;
			}
			if(strcmp(str ,">") == 0) {
				line >> num;
				if(sum > num*10) {
					puts("correct.");
				} else {
					puts("incorrect.");
				}
				break;
			}
			if(strcmp(str ,"<=") == 0) {
				line >> num;
				if(sum <= num*10) {
					puts("correct.");
				} else {
					puts("incorrect.");
				}
				break;
			}
			if(strcmp(str ,">=") == 0) {
				line >> num;
				if(sum >= num*10) {
					puts("correct.");
				} else {
					puts("incorrect.");
				}
				break;
			}
			if(strcmp(str ,"=") == 0) {
				line >> num;
				if(sum == num*10) {
					puts("correct.");
				} else {
					puts("incorrect.");
				}
				break;
			}
			sum += record[str];
		}
	}
    return 0;
}
