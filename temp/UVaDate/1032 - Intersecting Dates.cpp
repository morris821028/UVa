#include <stdio.h> 
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 128;
map<int, int> R;
int prevDay(int x) {
	int mday[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int yy = x/10000, mm = x%10000/100, dd = x%100;
	if ((yy%4 == 0 && yy%100 != 0) || yy%400 == 0)
		mday[2] = 29;
	if (mm == 1 && dd == 1) {
		yy--, mm = 12, dd = 31;
	} else {
		dd--;
		if (dd < 1)			mm--, dd = mday[mm];
	}
	return yy * 10000 + mm * 100 + dd;
}
int nextDay(int x) {
	int mday[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int yy = x/10000, mm = x%10000/100, dd = x%100;
	if ((yy%4 == 0 && yy%100 != 0) || yy%400 == 0)
		mday[2] = 29;
	dd++;
	if (dd > mday[mm])	dd = 1, mm++;
	if (mm == 13)		mm = 1, yy++;
	return yy * 10000 + mm * 100 + dd;
}
void record(int x) {
	R[x] = 0, R[nextDay(x)] = 0, R[prevDay(x)] = 0;
//	printf("-- %d %d %d\n", prevDay(x), x, nextDay(x));
}
void printDate(int x) {
	int yy = x/10000, mm = x%10000/100, dd = x%100;
	printf("%d/%d/%d", mm, dd, yy);
}
int main() {
	int cases = 0;
	int N, M;
	int aSt[MAXN], aEd[MAXN];
	int bSt[MAXN], bEd[MAXN];
	while (scanf("%d %d", &N, &M) == 2) {
		if (N == 0 && M == 0)
			break;
			
		R.clear();
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &aSt[i], &aEd[i]);
			record(aSt[i]);
			record(aEd[i]);
		}
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &bSt[i], &bEd[i]);
			record(bSt[i]);
			record(bEd[i]);
		}
		
		int size = 0;
		vector<int> date;
		for (map<int, int>::iterator it = R.begin();
			it != R.end(); it++)
			it->second = size++, date.push_back(it->first);
			
		vector<int> mark(size, 0);
		for (int i = 0; i < M; i++) {
			int l = R[bSt[i]], r = R[bEd[i]];
			for (int j = l; j <= r; j++)
				mark[j] = 1;
		}
		for (int i = 0; i < N; i++) {
			int l = R[aSt[i]], r = R[aEd[i]];
			for (int j = l; j <= r; j++)
				mark[j] = 0;
		}
		
		if (cases)
			puts("");
		printf("Case %d:\n", ++cases);
		int has = 0;
		for (int i = 0; i < mark.size(); i++) {
			if (mark[i] == 1) {
				has = 1;
				printf("    ");
				printDate(date[i]);
				if (i+1 < mark.size() && mark[i+1] == 1) {
					printf(" to ");
					while (i+1 < mark.size() && mark[i+1] == 1)
						i++;
					printDate(date[i]);
					printf("\n");
				} else {
					printf("\n");
				}
			} 
		}
		
		if (!has)
			puts("    No additional quotes are required.");
	}
	return 0;
}
