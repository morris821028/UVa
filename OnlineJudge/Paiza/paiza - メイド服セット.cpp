#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
	int N, M;
	scanf("%d", &N);
	while (N--) {
		scanf("%d", &M);
		int time = 60;
		time -= M / 3;
		if (time < 0)	time += 60 * 24;
		printf("%02d:%02d\n", time/60, time%60);
	}
	return 0;
}

