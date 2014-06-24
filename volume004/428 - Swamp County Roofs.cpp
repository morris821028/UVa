#include <stdio.h>
#include <sstream>
#include <iostream>
#include <math.h>
using namespace std;
const double pi = acos(-1);
double A, B, C, N;
char* getLot() {
	char line[1024], *v;
	string ret = "", token;
	int tokenCnt = 0;
	while(tokenCnt%4 != 1) {
		while((v = gets(line)) && line[0] != '\0') {
			ret += " ", ret += line;
			stringstream ss(line);
			while(ss >> token)
				tokenCnt++;
		}
		if(!v)
			return v;
	}
	stringstream sin(ret);
	double lotsize, baseline, ridgeline, dist, theta;
	double a = 0, b = 0;
	sin >> lotsize;
	while(sin >> baseline >> ridgeline >> dist >> theta) {
		a += (baseline + ridgeline) * dist/2.0;
		b += (baseline + ridgeline) * dist/2.0 * cos(theta / 180.0 * pi);	
	}
	printf("%9.2lf     %10.2lf     %8.2lf%%\n", a, b, b * 100 /lotsize);
	A += a, B += b, C += lotsize, N++;
	return v;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout);
	
	puts("Roof Area     Floor Area     % Covered");
	puts("---------     ----------     ---------");
	char line[1024];
	while(true) {
		if(getLot()) {
		} else {
			break;
		}
	}
	puts("");
	printf("Total surface area of roofs  %10.2lf\n", A);
	printf("Total area covered by roofs  %10.2lf\n", B);
	printf("Percentage of total area covered by roofs  %6.2lf%%\n", B*100/C);
	printf("Average roof surface area per lot      %10.2lf\n", A/N);
	printf("Average floor space covered per lot    %10.2lf\n", B/N);
	return 0;
}
