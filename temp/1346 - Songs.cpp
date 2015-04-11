#include <stdio.h> 
#include <algorithm>
using namespace std;
const int MAXN = 65536;
struct Song {
	int id;
	double length, freq;
	void read() {
		scanf("%d %lf %lf", &id, &length, &freq);
	}
} songs[MAXN];
// like UVa 12589 - Learning Vector, greedy
// if a-th song early than b-th song early, then sat. b.freq * a.length < a.freq * b.length,
// otherwise, b-th song early then a-th song.
bool cmp(Song a, Song b) { // a.length / a.freq < b.length / b.freq 
	return b.freq * a.length < a.freq * b.length;
}
int main() {
	int N, Idx;
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			songs[i].read();
		scanf("%d", &Idx);
		sort(songs, songs + N, cmp);
		printf("%d\n", songs[Idx-1].id);
	}
	return 0;
}
