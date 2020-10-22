#include <bits/stdc++.h>
using namespace std;

// Algorithm Design and Analysis (NTU CSIE, Fall 2020)
// Problem 2. Bomb Game

const int MAXN = 200005;
struct BIT {
	int64_t a[MAXN];
	int l[MAXN];
	int cases = 0;

	void add(int x, int val, int n) {
		while (x <= n) {
			if (l[x] != cases)
				l[x] = cases, a[x] = 0;
			a[x] += val, x += x&(-x);
		}
	}

	int64_t sum(int x) {
		int64_t ret = 0;
		while (x) {
			if (l[x] != cases)
				l[x] = cases, a[x] = 0;
			ret += a[x], x -= x&(-x);
		}
		return ret;
	}

	void reset(int n) {
		cases++;
	}

	void add(int l, int r, int k, int n) {
		add(l, k, n);
		add(r+1, -k, n);
	}
} bit;

int n;
struct PEvent {
	int c, d, i;
};
struct AEvent {
	int l, r, p, k;
};

struct Event {
	int type; // 'P' 0 or 'A' 1
	int time; // input order
	union {
		PEvent p;
		AEvent a;
	} data;

	int power() {
		if (type == 0)
			return data.p.d;
		else
			return data.a.p;
	}

	void println() {
		if (type == 0)
			printf("P %d %d\n", data.p.c, data.p.d);
		else
			printf("A %d %d %d %d\n", data.a.l, data.a.r, data.a.p, data.a.k);
	}
} events[MAXN];

static bool cmp_p(Event &a, Event &b) {
	int pa = a.power();
	int pb = b.power();
	if (pa != pb)
		return pa < pb;
	return a.time < b.time;
}
static bool cmp_t(Event &a, Event &b) {
	return a.time > b.time;
}

int ret[MAXN];
void resolve(int l, int m, int r) {
	sort(events+l, events+m+1, cmp_t);
	sort(events+m+1, events+r+1, cmp_t);

	//	printf("resolve %d %d =========\n", l, r);
	//	for (int i = l; i <= m; i++)
	//		events[i].println();
	//	puts("---");
	//	for (int i = m+1; i <= r; i++)
	//		events[i].println();
	bit.reset(n);
	int j = m+1;
	for (int i = l; i <= m; i++) {
		if (events[i].type)
			continue;
		int qtime = events[i].time;
		while (j <= r && events[j].time > qtime) {
			if (events[j].type) {
				bit.add(events[j].data.a.l,
						events[j].data.a.r,
						events[j].data.a.k,
						n);
				//				printf("add %d %d %d %d\n", events[j].data.a.l,
				//						events[j].data.a.r,
				//						events[j].data.a.p,
				//						events[j].data.a.k);
			}
			j++;
		}

		//		printf("%d --- %d\n", events[i].data.p.i, bit.sum(events[i].data.p.c));
		ret[events[i].data.p.i] += bit.sum(events[i].data.p.c);
	}
}
void divide(int l, int r) {
	if (l >= r)
		return;
	int m = (l+r)/2;
	divide(l, m);
	divide(m+1, r);

	resolve(l, m, r);
}

int main() {
	int m;
	char s[2];
	scanf("%d %d", &n, &m);

	int id = 0;
	for (int i = 0; i < m; i++) {
		scanf("%s", s);
		events[i].time = i;
		if (s[0] == 'P') {
			events[i].type = 0;
			events[i].data.p.i = id++;
			scanf("%d %d",
					&events[i].data.p.c,
					&events[i].data.p.d);
		} else {
			events[i].type = 1;
			scanf("%d %d %d %d",
					&events[i].data.a.l, 
					&events[i].data.a.r,
					&events[i].data.a.p,
					&events[i].data.a.k);
		}
	}

	sort(events, events+m, cmp_p);
	divide(0, m-1);

	for (int i = 0; i < id; i++)	
		printf("%d\n", ret[i]);
	return 0;
}
/*
   10 10
   P 3 5
   A 2 8 15 5
   P 7 10
   A 4 10 5 3
   A 1 9 10 7
   P 6 20
   P 5 1
   A 4 9 17 2
   A 1 2 20 4
   P 9 5

   10 6
   P 5 1
   P 2 1
   A 3 8 1 3
   P 6 1
   A 2 6 1 6
   A 2 4 1 4
 */
